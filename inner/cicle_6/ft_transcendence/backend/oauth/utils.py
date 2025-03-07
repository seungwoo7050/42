import logging
from datetime import datetime, timedelta
from functools import wraps
from typing import Optional, Dict, List


import jwt
import redis
from django.conf import settings
from django.http import JsonResponse
from django.utils import timezone
from redis.exceptions import RedisError

import imghdr
from PIL import Image
import io
from django.core.exceptions import ValidationError


from .models import CustomUser, TokenBlacklist


# 로깅 설정
logger = logging.getLogger(__name__)


# Redis 연결
try:
    redis_client = redis.StrictRedis(
        host=settings.REDIS_HOST,
        port=settings.REDIS_PORT,
        db=settings.REDIS_DB,
        decode_responses=True,  # 자동 디코딩 설정
        socket_timeout=5,
        socket_keepalive=True
    )
except RedisError as e:
    logger.error(f"Redis 연결 실패: {str(e)}")
    redis_client = None
    
    
def create_error_response(code: str, message: str, status: int = 400) -> JsonResponse:
    """
    표준화된 에러 응답을 생성합니다.
    
    Args:
        code: 에러 코드
        message: 에러 메시지
        status: HTTP 상태 코드
    """
    return JsonResponse({
        "status": "error",
        "error": {
            "code": code,
            "message": message
        }
    }, status=status)


def generate_jwt_token(user: CustomUser, is_access: bool = True, temp_2fa: bool = False) -> str:
    """
    JWT 토큰을 생성합니다.
    
    Args:
        user: 토큰을 생성할 사용자
        is_access: True면 액세스 토큰, False면 리프레시 토큰
        temp_2fa: True면 2FA 검증용 임시 토큰
    """
    exp = timezone.now() + timedelta(
        seconds=300 if temp_2fa else  # 임시 토큰은 5분
        settings.ACCESS_TOKEN_EXPIRATION if is_access 
        else settings.REFRESH_TOKEN_EXPIRATION
    )
    
    payload = {
        'user_id': user.user_id,
        'displayname': user.displayname,
        'exp': exp,
        'iat': timezone.now(),
        'type': 'temp_2fa' if temp_2fa else 'access' if is_access else 'refresh'
    }

    if temp_2fa:
        payload['temp_2fa'] = True
    
    return jwt.encode(
        payload,
        settings.JWT_SECRET_KEY,
        algorithm=settings.JWT_ALGORITHM
    )
    
def jwt_required(view_func):
    """
    JWT 토큰 검증 데코레이터.
    쿠키에서 JWT를 검증하고 사용자 정보를 request에 추가합니다.
    """
    @wraps(view_func)
    def wrapper(request, *args, **kwargs):
        access_token = request.COOKIES.get('access_token')
        refresh_token = request.COOKIES.get('refresh_token')
        temp_token = request.COOKIES.get('temp_token')
        
        # 임시 토큰이 있는 경우 접근 거부
        if temp_token:
            return create_error_response(
                "FORBIDDEN",
                "2FA 인증이 필요합니다.",
                403
            )

        if not access_token:
            return create_error_response(
                "UNAUTHORIZED",
                "인증 토큰이 필요합니다.",
                401
            )

        # 토큰 블랙리스트 확인
        if refresh_token and TokenBlacklist.objects.filter(token=refresh_token).exists():
            return create_error_response(
                "INVALID_TOKEN",
                "무효화된 토큰입니다.",
                401
            )

        try:
            payload = jwt.decode(
                access_token,
                settings.JWT_SECRET_KEY,
                algorithms=[settings.JWT_ALGORITHM]
            )
            
            request.user = CustomUser.objects.get(user_id=payload['user_id'])
            
        except jwt.ExpiredSignatureError:
            return create_error_response(
                "EXPIRED_TOKEN",
                "만료된 토큰입니다.",
                401
            )
        except jwt.InvalidTokenError:
            return create_error_response(
                "INVALID_TOKEN",
                "유효하지 않은 토큰입니다.",
                401
            )
        except CustomUser.DoesNotExist:
            return create_error_response(
                "USER_NOT_FOUND",
                "사용자를 찾을 수 없습니다.",
                404
            )
        
        return view_func(request, *args, **kwargs)
    
    return wrapper


def get_game_status(user_id: str) -> Dict:
    """
    사용자의 현재 게임 상태를 조회합니다.
    
    Args:
        user_id: 사용자 ID
        
    Returns:
        게임 상태 정보를 담은 딕셔너리
    """
    if not redis_client:
        logger.error("Redis 클라이언트가 초기화되지 않았습니다.")
        return {'in_game': False, 'in_queue': False}

    try:
        in_game = bool(redis_client.get(f"game:{user_id}"))
        in_queue = bool(redis_client.get(f"queue:{user_id}"))
        return {'in_game': in_game, 'in_queue': in_queue}
    except RedisError as e:
        logger.error(f"게임 상태 조회 실패: {str(e)}")
        return {'in_game': False, 'in_queue': False}


def update_game_status(user_id: str, status: str, value: bool = True) -> bool:
    """
    사용자의 게임 상태를 업데이트합니다.
    
    Args:
        user_id: 사용자 ID
        status: 상태 유형 ('game' 또는 'queue')
        value: 설정할 값
        
    Returns:
        성공 여부
    """
    if status not in ['game', 'queue']:
        logger.error(f"잘못된 상태값: {status}")
        return False
    
    if not redis_client:
        logger.error("Redis 클라이언트가 초기화되지 않았습니다.")
        return False

    try:
        key = f"{status}:{user_id}"
        if value:
            redis_client.setex(key, settings.GAME_STATUS_TIMEOUT, '1')
        else:
            redis_client.delete(key)
        return True
    except RedisError as e:
        logger.error(f"게임 상태 업데이트 실패: {str(e)}")
        return False

def required_2fa(view_func):
    """2FA가 활성화된 사용자만 접근을 허용하는 데코레이터"""
    @wraps(view_func)
    def wrapper(request, *args, **kwargs):
        if not request.user.is_totp_enabled:
            return create_error_response(
                "2FA_REQUIRED",
                "2차 인증이 필요합니다.",
                403
            )
        return view_func(request, *args, **kwargs)
    return wrapper


def update_last_seen(user_id: str) -> bool:
    """
    사용자의 마지막 활동 시간을 업데이트합니다.
    
    Args:
        user_id: 사용자 ID
        
    Returns:
        성공 여부
    """
    if not redis_client:
        logger.error("Redis 클라이언트가 초기화되지 않았습니다.")
        return False

    try:
        key = f"lastseen:{user_id}"
        # 현재 timestamp를 저장
        redis_client.setex(key, settings.POLLING_TIMEOUT + 5, str(timezone.now().timestamp()))
        return True
    except RedisError as e:
        logger.error(f"마지막 활동 시간 업데이트 실패: {str(e)}")
        return False


def get_active_users() -> List[str]:
    """
    최근 활동한 사용자 ID 목록을 반환합니다.
    POLLING_TIMEOUT 시간 내에 활동한 사용자를 온라인으로 간주합니다.
    
    Returns:
        활성 사용자 ID 목록
    """
    if not redis_client:
        logger.error("Redis 클라이언트가 초기화되지 않았습니다.")
        return []

    try:
        # 모든 lastseen 키를 가져옴
        keys = redis_client.keys("lastseen:*")
        active_users = []
        
        for key in keys:
            user_id = key.split(":")[1]
            last_seen = redis_client.get(key)
            if last_seen:
                # 마지막 활동 시간이 POLLING_TIMEOUT 이내인 경우만 포함
                if float(last_seen) > (timezone.now() - timedelta(seconds=settings.POLLING_TIMEOUT)).timestamp():
                    active_users.append(user_id)
                    
        return active_users
    except RedisError as e:
        logger.error(f"활성 사용자 조회 실패: {str(e)}")
        return []
    
def validate_image(image_data):
    """이미지 파일 유효성 검사"""
    if len(image_data) > settings.MAX_UPLOAD_SIZE:
        raise ValidationError("이미지 크기는 5MB를 초과할 수 없습니다.")
    
    image_type = imghdr.what(None, image_data)
    if image_type not in ['jpeg', 'png']:
        raise ValidationError("JPG 또는 PNG 형식의 이미지만 허용됩니다.")
    
    return image_type

def optimize_image(image_data):
    """이미지 최적화"""
    img = Image.open(io.BytesIO(image_data))
    max_size = (800, 800)
    img.thumbnail(max_size, Image.LANCZOS)
    
    output = io.BytesIO()
    img.save(output, format='PNG', optimize=True)
    return output.getvalue()

def validate_displayname(value: str) -> bool:
    """
    닉네임 유효성 검사
    Returns: 
        bool: 유효하면 True, 아니면 ValidationError 발생
    """
    if not value.isalnum():
        raise ValidationError('닉네임은 영문자와 숫자만 사용할 수 있습니다.')
    
    forbidden_names = ['ai', 'admin', 'me']
    if value.lower() in forbidden_names:
        raise ValidationError('사용할 수 없는 닉네임입니다.')
    
    return True