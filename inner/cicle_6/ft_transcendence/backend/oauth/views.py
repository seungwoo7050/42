import json
import jwt
import requests
import pyotp
import base64
import redis
import uuid
import logging
import hashlib

from typing import Dict, Any
from django.conf import settings
from django.views import View
from django.http import JsonResponse
from django.utils.decorators import method_decorator
from django.db import transaction, models
from django.utils.http import urlencode
from django.utils import timezone
from django.core.files.storage import default_storage
from django.core.files.base import ContentFile
from django.core.exceptions import ValidationError
from django.shortcuts import render

from .models import CustomUser, TokenBlacklist, Match
from .utils import (
    create_error_response,
    generate_jwt_token,
    jwt_required,
    required_2fa,
    get_game_status,
    update_game_status,
    redis_client,
    update_last_seen,
    get_active_users,
    validate_image,
    optimize_image,
    validate_displayname,
)

# 로거 설정 - settings.py에 이미 있는 LOGGING 설정을 사용
logger = logging.getLogger(__name__)

class AuthStatusView(View):
    @method_decorator(jwt_required)
    def get(self, request):
        return JsonResponse({"ack": True})

class OAuth42LoginView(View):
    """42 OAuth 로그인 URL을 제공하는 뷰"""
    def get(self, request):
        """
        42 OAuth 로그인 URL을 반환합니다.

        Returns (200):
            {
                "authorize_url": str (OAuth 인증 페이지 URL)
            }
        """
        params = {
            "client_id" : settings.OAUTH_42_CLIENT_ID,
            "redirect_uri" : settings.OAUTH_42_REDIRECT_URI,
            "response_type": "code" }
        authorize_url = f"{settings.OAUTH_42_AUTHORIZE_URL}?{urlencode(params)}"
            # f"{settings.OAUTH_42_AUTHORIZE_URL}"
            # f"?client_id={settings.OAUTH_42_CLIENT_ID}"
            # f"&redirect_uri={settings.OAUTH_42_REDIRECT_URI}"
            # f"&response_type=code"
        return JsonResponse({"authorize_url": authorize_url})

class OAuth42CallbackView(View):
    """42 OAuth 콜백을 처리하고 토큰을 발급하는 뷰"""
    def post(self, request):
        code = request.GET.get("code")
        if not code:
            return create_error_response("NO_CODE", "인증 코드가 필요합니다.", 400)
        
        try:
            # 42 API로부터 토큰 획득
            token_response = requests.post(
                settings.OAUTH_42_TOKEN_URL,
                data = {
                    "grant_type": "authorization_code",
                    "client_id": settings.OAUTH_42_CLIENT_ID,
                    "client_secret": settings.OAUTH_42_CLIENT_SECRET,
                    "code": code,
                    "redirect_uri": settings.OAUTH_42_REDIRECT_URI
                }
            )

            if token_response.status_code != requests.codes.ok:
                return create_error_response("AUTH_FAILED", "42 인증에 실패했습니다.", 401)

            access_token = token_response.json().get("access_token")
            
            # 42 API로부터 사용자 정보 획득
            user_response = requests.get(
                settings.OAUTH_42_USERINFO_URL,
                headers={"Authorization": f"Bearer {access_token}"},
            )

            if user_response.status_code != requests.codes.ok:
                return create_error_response("AUTH_FAILED", "사용자 정보 조회에 실패했습니다.", 401)

            user_data = user_response.json()

            # 사용자 생성 또는 업데이트
            try:
                with transaction.atomic():
                    user, created = CustomUser.objects.get_or_create(
                        user_id=user_data['login'],
                        defaults={
                            'email': user_data['email'],
                            'displayname': user_data['login']
                        }
                    )
                    
                    # 프로필 이지 처
                    image_url = user_data.get('image', {}).get('link')
                    if image_url:
                        try:
                            
                            # URL의 해시값 계산
                            url_hash = hashlib.md5(image_url.encode()).hexdigest()
                            
                            # 해시가 다를 때만 이미지 업데이트
                            if not user.avatar_hash or url_hash != user.avatar_hash:
                                img_response = requests.get(image_url)
                                if img_response.ok:
                                    image_data = img_response.content
                                    image_type = validate_image(image_data)
                                    optimized_image = optimize_image(image_data)
                                    
                                    if user.avatar:
                                        try:
                                            default_storage.delete(user.avatar)
                                        except Exception as e:
                                            logger.error(f"기존 아바타 삭제 실패: {e}")

                                    file_name = f"avatar_{user.user_id}_{uuid.uuid4()}.{image_type}"
                                    file_path = f'avatars/{file_name}'
                                    user.avatar = default_storage.save(file_path, ContentFile(optimized_image))
                                    user.avatar_hash = url_hash
                                    user.save()
                        except Exception as e:
                            logger.error(f"이미지 처리 중 오류: {e}")
                    
                    user.last_login = timezone.now()
                    user.save()
                    
                    # 2FA 확인
                    if user.is_totp_enabled:
                        # 2FA가 필요한 경우 임시 토큰 발급
                        temp_token = generate_jwt_token(user, is_access=False, temp_2fa=True)
                        response = JsonResponse({
                            "requires_2fa": True,
                            "user": {
                                "user_id": user.user_id,
                                "displayname": user.displayname,
                            }
                        })
                        
                        response.set_cookie(
                            'temp_token',
                            temp_token,
                            httponly=True,
                            secure=True,
                            samesite='Strict',
                            max_age=300  # 5분
                        )
                        return response

                    # 2FA가 필요없는 경우 정상 토큰 발급
                    jwt_access_token = generate_jwt_token(user, is_access=True)
                    jwt_refresh_token = generate_jwt_token(user, is_access=False)
                    
                    response = JsonResponse({
                        "requires_2fa": False,
                        "user": {
                            "user_id": user.user_id,
                            "displayname": user.displayname,
                            "email": user.email,
                            "avatar": user.avatar
                        }
                    })
                    
                    response.set_cookie(
                        'access_token',
                        jwt_access_token,
                        httponly=True,
                        secure=True,
                        samesite='Strict',
                        max_age=settings.ACCESS_TOKEN_EXPIRATION
                    )
                    
                    response.set_cookie(
                        'refresh_token',
                        jwt_refresh_token,
                        httponly=True,
                        secure=True,
                        samesite='Strict',
                        max_age=settings.REFRESH_TOKEN_EXPIRATION
                    )
                    
                    return response

            except KeyError as e:
                logger.error(f"42 API 응답에서 필수 필드 누락: {e}")
                return create_error_response("INVALID_USER_DATA", "유효하지 않은 사용자 정보입니다.", 400)

        except requests.RequestException as e:
            logger.error(f"42 API 요청 실패: {e}")
            return create_error_response("SERVER_ERROR", "외부 서비스 요청 실패", 500)
        except Exception as e:
            logger.error(f"예상치 못한 오류: {e}")
            return create_error_response("SERVER_ERROR", str(e), 500)
                    

@method_decorator(jwt_required, name='dispatch')
class LogoutView(View):
    """로그아웃을 처리하는 뷰"""
    def post(self, request):
        """
        로그아웃을 처리하고 토큰을 무효화합니다.

        Cookies Required:
            access_token: JWT 액세스 토큰
            refresh_token: JWT 리프레시 토큰

        Returns (200):
            {
                "message": "로그아웃되었습니다."
            }
        """
        refresh_token = request.COOKIES.get('refresh_token')
        if refresh_token:
            TokenBlacklist.objects.create(token=refresh_token)
            
        response = JsonResponse({"message": "로그아웃되었습니다."})
        response.delete_cookie('access_token')
        response.delete_cookie('refresh_token')
        return response

@method_decorator(jwt_required, name='dispatch')
class TokenRefreshView(View):
    """토큰 갱신을 처리하는 뷰"""
    def post(self, request):
        """리프레시 토큰으로 새로운 액세스 토큰을 발급합니다."""
        refresh_token = request.COOKIES.get('refresh_token')
        
        if not refresh_token:
            return create_error_response("NO_TOKEN", "리프레시 토큰이 필요합니다.", 401)

        if TokenBlacklist.objects.filter(token=refresh_token).exists():
            return create_error_response("INVALID_TOKEN", "무효화된 토큰입니다.", 401)

        try:
            # JWT 토큰 검증
            payload = jwt.decode(
                refresh_token,
                settings.JWT_SECRET_KEY,
                algorithms=[settings.JWT_ALGORITHM]
            )

            user = CustomUser.objects.get(user_id=payload['user_id'])
            access_token = generate_jwt_token(user, is_access=True)

            response = JsonResponse({"message": "토큰이 갱신되었습니다."})
            response.set_cookie(
                'access_token',
                access_token,
                httponly=True,
                secure=settings.USE_HTTPS,
                samesite='Lax',
                max_age=settings.ACCESS_TOKEN_EXPIRATION
            )
            return response

        except jwt.ExpiredSignatureError:
            return create_error_response("TOKEN_EXPIRED", "만료된 토큰입니다.", 401)
        except jwt.InvalidTokenError:
            return create_error_response("INVALID_TOKEN", "유효하지 않은 토큰입니다.", 401)
        except CustomUser.DoesNotExist:
            return create_error_response("USER_NOT_FOUND", "사용자를 찾을 수 없습니다.", 404)

@method_decorator(jwt_required, name='dispatch')
class UserProfileView(View):
    """사용자 프로필을 관리하는 뷰"""
    def get(self, request):
        """
        현재 로그인한 사용자의 프로필 정보를 조회합니다.

        Returns (200):
            {
                "user": {
                    "user_id": str,
                    "displayname": str,
                    "email": str,
                    "avatar": path | null,
                    "is_2fa_enabled": bool,
                    "game_status": {
                        "in_game": bool,
                        "in_queue": bool
                    }
                }
            }
        """
        user = request.user
        game_status = get_game_status(user.user_id)
        
        response_data = {
            "user": {
                "user_id": user.user_id,
                "displayname": user.displayname,
                "email": user.email,
                "avatar": user.avatar,
                "is_2fa_enabled": user.is_totp_enabled,
                "game_status": game_status
            }
        }
        
        return JsonResponse(response_data)

    def patch(self, request):
        """
        사용자 프로필 정보를 부분 수정합니다.

        Body:
            {
                "displayname": str (optional),
                "avatar": str (base64, optional)
            }
        """
        try:
            data = json.loads(request.body)
            user = request.user

            if 'displayname' in data:
                if CustomUser.objects.filter(displayname=data['displayname'])\
                        .exclude(user_id=user.user_id).exists():
                    return create_error_response("DUPLICATE_NAME", "이미 사용 중인 닉네임입니다.")
                try:
                    validate_displayname(data['displayname'])
                except ValidationError as e:
                    return create_error_response("INVALID_NAME", str(e))
                user.displayname = data['displayname']
                
            

            if 'avatar' in data:
                try:
                    image_data = base64.b64decode(data['avatar'])
                    
                    image_type = validate_image(image_data)
                    
                    optimized_image = optimize_image(image_data)
                    
                    file_name = f"avatar_{user.user_id}_{uuid.uuid4()}.{image_type}"
                    
                    if user.avatar:
                        try:
                            default_storage.delete(user.avatar)
                        except Exception:
                            pass
                        
                    path = default_storage.save(
                        f'avatars/{file_name}',
                        ContentFile(optimized_image)
                    )
                    user.avatar = path
                except ValidationError as e:
                    return create_error_response("INVALID_AVATAR", str(e))
                except Exception as e:
                    return create_error_response("AVATAR_UPLOAD_ERROR", f"이미지 업로드 중 오류: {str(e)}")

            user.save()
            
            return JsonResponse({
                "message": "프로필이 수정되었습니다.",
                "user": {
                    "displayname": user.displayname,
                    "avatar": user.avatar if user.avatar else None
                    # "avatar": base64.b64encode(user.avatar).decode() if user.avatar else None
                }
            })
            
        except json.JSONDecodeError:
            return create_error_response("INVALID_DATA", "잘못된 데이터 형식입니다.")

# views.py에 추가
@method_decorator(jwt_required, name='dispatch')
class UserProfileDetailView(View):
    """특정 유저의 프로필 정보를 조회하는 뷰"""
    def get(self, request, user_id):
        try:
            # 요청한 유저가 친구인지 확인
            current_user = request.user
            target_user = CustomUser.objects.get(user_id=user_id)
            
            if not current_user.friends.filter(user_id=user_id).exists():
                return create_error_response(
                    "NOT_FRIEND", 
                    "친구가 아닌 유저의 프로필은 볼 수 없습니다.", 
                    403
                )
            
            # 매치 기록 조회
            matches = Match.objects.filter(
                models.Q(player1=target_user) | models.Q(player2=target_user)
            ).order_by('-created_at')
            
            match_list = [{
                "id": match.id,
                "player1": {
                    "user_id": match.player1.user_id,
                    "displayname": match.player1.displayname,
                    "score": match.score_player1
                },
                "player2": {
                    "user_id": match.player2.user_id if match.player2 else 'AI',
                    "displayname": match.player2.displayname if match.player2 else 'AI',
                    "score": match.score_player2
                },
                "winner": {
                    "user_id": match.winner.user_id,
                    "displayname": match.winner.displayname
                } if match.winner else None,
                "created_at": match.created_at.isoformat()
            } for match in matches]
            
            # 전적 통계 계산
            total_matches = matches.count()
            # print("total_matches\n", total_matches)
            wins = matches.filter(winner=target_user).count()
            # print("wins\n", wins)
            # print("hey")
            win_rate = (wins / total_matches * 100) if total_matches > 0 else 0

            return JsonResponse({
                "profile": {
                    "user_id": target_user.user_id,
                    "displayname": target_user.displayname,
                    "email": target_user.email,
                    "avatar": target_user.avatar,
                    "stats": {
                        "total_matches": total_matches,
                        "wins": wins,
                        "win_rate": round(win_rate, 1)
                    }
                },
                "recent_matches": match_list
            })
            
        except CustomUser.DoesNotExist:
            return create_error_response("USER_NOT_FOUND", "사용자를 찾을 수 없습니다.", 404)
        except Exception as e:
            return create_error_response("SERVER_ERROR", str(e), 500)


        
@method_decorator(jwt_required, name='dispatch')
class FriendView(View):
    """친구 관계를 관리하는 뷰"""
    def get(self, request):
        """
        현재 사용자의 친구 목록을 조회합니다.

        Returns (200):
            {
                "friends": [{
                    "user_id": str,
                    "displayname": str,
                    "game_status": {
                        "in_game": bool,
                        "in_queue": bool
                    }
                }]
            }
        """
        user = request.user
        friends = user.friends.all()
        
        friend_list = [{
            "user_id": friend.user_id,
            "displayname": friend.displayname,
            "game_status": get_game_status(friend.user_id)
        } for friend in friends]
        
        return JsonResponse({"friends": friend_list})

    def post(self, request):
        """
        친구를 추가합니다.

        Body:
            {
                "user_id": str (필수)
            }

        Returns (201):
            {
                "message": "친구가 추가되었습니다.",
                "friend": {
                    "user_id": str,
                    "displayname": str
                }
            }
        """
        try:
            data = json.loads(request.body)
            friend_id = data.get('user_id')
            
            if not friend_id:
                return create_error_response("MISSING_USER_ID", "친구 ID가 필요합니다.")
                
            if friend_id == request.user.user_id:
                return create_error_response("SELF_FRIEND", "자기 자신을 친구로 추가할 수 없습니다.")

            try:
                friend = CustomUser.objects.get(user_id=friend_id)
                if request.user.add_friend(friend):  # models.py의 메소드 사용
                    return JsonResponse({
                        "message": "친구가 추가되었습니다.",
                        "friend": {
                            "user_id": friend.user_id,
                            "displayname": friend.displayname
                        }
                    }, status=201)
                return create_error_response("ALREADY_FRIEND", "이미 친구로 등록된 사용자입니다.")
            except CustomUser.DoesNotExist:
                return create_error_response("USER_NOT_FOUND", "사용자를 찾을 수 없습니다.", 404)
                
        except json.JSONDecodeError:
            return create_error_response("INVALID_DATA", "잘못된 데이터 형식입니다.")

    def delete(self, request):
        """
        친구를 삭제합니다.

        Body:
            {
                "user_id": str (필수)
            }

        Returns (200):
            {
                "message": "친구가 삭제되었습니다."
            }
        """
        try:
            data = json.loads(request.body)
            friend_id = data.get('user_id')
            
            if not friend_id:
                return create_error_response("MISSING_USER_ID", "친구 ID가 필요합니다.")

            try:
                friend = CustomUser.objects.get(user_id=friend_id)
                if request.user.remove_friend(friend):  # models.py의 메소드 사용
                    return JsonResponse({"message": "친구가 삭제되었습니다."})
                return create_error_response("NOT_FRIEND", "친구 목록에 없는 사용자입니다.")
            except CustomUser.DoesNotExist:
                return create_error_response("USER_NOT_FOUND", "사용자를 찾을 수 없습니다.", 404)
                
        except json.JSONDecodeError:
            return create_error_response("INVALID_DATA", "잘못된 데이터 형식입니다.")

@method_decorator(jwt_required, name='dispatch')
class MatchView(View):
    """매치 정보를 관리하는 뷰"""
    def post(self, request):
        try:
            data = json.loads(request.body)
            
            # 기본 매치 데이터 준비
            match_data = {
                'player1': request.user,
                'score_player1': data.get('score_player1'),
                'score_player2': data.get('score_player2'),
            }
            
            # AI 매치 처리
            if data.get('opponent_id') == 'AI':
                match_data['player2'] = None  # AI는 None으로 처리
                match_data['winner'] = request.user if data.get('winner') == 'player1' else None
            else:
                # 일반 PvP 매치 처리
                match_data['player2'] = CustomUser.objects.get(user_id=data.get('opponent_id'))
                match_data['winner'] = (request.user if data.get('winner') == 'player1' 
                                      else match_data['player2'])
            
            # 매치 생성
            match = Match.objects.create(**match_data)
            
            return JsonResponse({"message": "매치 결과가 저장되었습니다."})
            
        except CustomUser.DoesNotExist:
            return create_error_response("USER_NOT_FOUND", "상대방을 찾을 수 없습니다.", 404)
        except Exception as e:
            return create_error_response("MATCH_SAVE_ERROR", str(e))
        
    def get(self, request):
        limit = min(int(request.GET.get('limit', 10)), 50)  # 최대 50개
        offset = int(request.GET.get('offset', 0))
        
        matches = Match.objects.filter(
            models.Q(player1=request.user) | models.Q(player2=request.user)
        ).order_by('-created_at')

        total_count = matches.count()
        matches = matches[offset:offset + limit + 1]
        has_next = len(matches) > limit
        matches = matches[:limit]

        match_list = [{
            "id": match.id,
            "player1": {
                "user_id": match.player1.user_id,
                "displayname": match.player1.displayname,
                "score": match.score_player1
            },
            "player2": {
                "user_id": "AI",
                "displayname": "AI",
                "score": match.score_player2
            } if not match.player2 else {
                "user_id": match.player2.user_id,
                "displayname": match.player2.displayname,
                "score": match.score_player2
            },
            "winner": {
                "user_id": match.winner.user_id,
                "displayname": match.winner.displayname
            } if match.winner else None,
            "created_at": match.created_at.isoformat()
        } for match in matches]

        return JsonResponse({
            "matches": match_list,
            "total_count": total_count,
            "has_next": has_next
        })
        
@method_decorator(jwt_required, name='dispatch')
class GameMatchingView(View):
    """게임 매칭을 관리하는 뷰"""
    def get(self, request):
        """
        현재 매칭 상태를 조회합니다.

        Returns (200):
            {
                "status": "idle"|"in_queue"|"matched",
                "queue_position": int | null,
                "match_info": {
                    "opponent": {
                        "user_id": str,
                        "displayname": str
                    }
                } | null
            }

        Errors:
            401: {"error": {"code": "NO_TOKEN", "message": str}}
        """
        user = request.user
        status = get_game_status(user.user_id)

        response_data = {
            "status": "idle",
            "queue_position": None,
            "match_info": None
        }

        if status.get('in_queue'):
            response_data['status'] = "in_queue"
            queue_key = f"queue:{user.user_id}"
            position = redis_client.zrank("matching_queue", user.user_id)
            if position is not None:
                response_data['queue_position'] = position + 1
                
        elif status.get('in_game'):
            response_data['status'] = "matched"
            match_key = f"match:{user.user_id}"
            match_data = redis_client.get(match_key)
            if match_data:
                response_data['match_info'] = json.loads(match_data)

        return JsonResponse(response_data)

    def post(self, request):
        """
        매칭 큐에 참가하거나 매칭을 수락/거절합니다.

        Body:
            {
                "action": "join"|"leave"|"accept"|"decline" (필수)
            }

        Returns (200):
            {
                "message": str,
                "status": "idle"|"in_queue"|"matched",
                "match_info": {...} | null
            }

        Errors:
            400: {"error": {"code": "INVALID_ACTION"|"ALREADY_IN_QUEUE"|"NOT_IN_QUEUE", "message": str}}
        """
        try:
            data = json.loads(request.body)
            action = data.get('action')
            opponent_id = data.get('opponent_id')
            
            if action not in ['join', 'leave']:
                return create_error_response("INVALID_ACTION", "유효하지 않은 액션입니다.")

            user = request.user
            game_status = get_game_status(user.user_id)

            if action == 'join':
                # 본인 체크
                if game_status.get('in_queue') or game_status.get('in_game'):
                    return create_error_response(
                        "ALREADY_IN_GAME", 
                        "이미 게임중이거나 대기중입니다."
                    )
            
                # 상대방 체크
                if opponent_id != 'AI':
                    opponent_status = get_game_status(opponent_id)
                    if opponent_status.get('in_queue') or opponent_status.get('in_game'):
                        return create_error_response(
                            "OPPONENT_BUSY", 
                            "상대방이 게임중이거나 대기중입니다."
                        )
                
                # 양쪽 다 게임 상태로 설정
                update_game_status(user.user_id, 'game', True)
                if opponent_id != 'AI':
                    update_game_status(opponent_id, 'game', True)
                return JsonResponse({
                    "message": "게임이 시작되었습니다.",
                    "status": "matched",
                    "opponent_id": opponent_id
                })

            elif action == 'leave':
                if not game_status.get('in_game'):
                    return create_error_response(
                        "NOT_IN_GAME", 
                        "떠난 게임이 없습니다."
                    )
                
                if game_status.get('in_game'):
                    update_game_status(user.user_id, 'game', False)
                    
                    opponent_id = data.get('opponent_id')
                    if opponent_id and opponent_id != 'AI':  # AI가 아닌 경우에만 처리
                        update_game_status(opponent_id, 'game', False)
                        
                    return JsonResponse({
                        "message": "게임에서 나왔습니다.",
                        "status": "idle"
                    })
        except json.JSONDecodeError:
            return create_error_response("INVALID_DATA", "잘못된 데이터 형식입니다.")
        except redis.RedisError:
            return create_error_response("SERVER_ERROR", "서버 오류가 발생했습니다.", 500)
        
@method_decorator(jwt_required, name='dispatch')
class TOTPSetupView(View):
    """2FA TOTP 설정을 관리하는 뷰"""
    def post(self, request):
        """
        TOTP 초기 설정을 수행합니다.

        Returns (200):
            {
                "secret": str (TOTP 비밀키),
                "provisioning_uri": str (QR 코드용 URI)
            }

        Errors:
            400: {"error": {"code": "ALREADY_ENABLED", "message": str}}
            500: {"error": {"code": "SETUP_FAILED", "message": str}}
        """
        try:
            user = request.user
            
            if user.is_totp_enabled:
                return create_error_response(
                    "ALREADY_ENABLED",
                    "이미 2FA가 활성화되어 있습니다."
                )

            # TOTP 비밀키 생성
            secret = pyotp.random_base32()
            totp = pyotp.TOTP(secret)
            
            # QR 코드용 프로비저닝 URI 생성
            provisioning_uri = totp.provisioning_uri(
                user.email,
                issuer_name=settings.APP_NAME
            )

            # 임시로 비밀키 저장 (검증 전)
            user.totp_secret = secret
            user.is_totp_enabled = True
            user.save()

            return JsonResponse({
                "secret": secret,
                "provisioning_uri": provisioning_uri
            })
            
        except Exception as e:
            return create_error_response("SETUP_FAILED", str(e), 500)

    def delete(self, request):
        """
        2FA를 비활성화합니다.

        Returns (200):
            {
                "message": "2FA가 비활성화되었습니다."
            }

        Errors:
            400: {"error": {"code": "NOT_ENABLED", "message": str}}
        """
        user = request.user
        
        if not user.is_totp_enabled:
            return create_error_response(
                "NOT_ENABLED",
                "2FA가 활성화되어 있지 않습니다."
            )

        user.totp_secret = None
        user.is_totp_enabled = False
        user.save()

        return JsonResponse({
            "message": "2FA가 비활성화되었습니다."
        })

class TOTPVerifyView(View):
    """2FA TOTP 검증을 처리하는 뷰"""
    def post(self, request):
        try:
            # 임시 토큰은 쿠키에서 확인
            temp_token = request.COOKIES.get('temp_token')
            if not temp_token:
                return create_error_response("NO_TOKEN", "임시 토큰이 필요합니다.", 401)

            # 토큰 검증
            try:
                payload = jwt.decode(
                    temp_token,
                    settings.JWT_SECRET_KEY,
                    algorithms=[settings.JWT_ALGORITHM]
                )
                
                if not payload.get('temp_2fa'):
                    return create_error_response("INVALID_TOKEN", "유효하지 않은 토큰입니다.", 401)
                
                user = CustomUser.objects.get(user_id=payload['user_id'])
            except (jwt.InvalidTokenError, CustomUser.DoesNotExist):
                return create_error_response("INVALID_TOKEN", "유효하지 않은 토큰입니다.", 401)

            # TOTP 코드 검증
            data = json.loads(request.body)
            code = data.get('code')
            
            if not code:
                return create_error_response("NO_CODE", "TOTP 코드가 필요합니다.", 400)

            totp = pyotp.TOTP(user.totp_secret)
            
            if not totp.verify(code):
                return create_error_response("INVALID_CODE", "잘못된 TOTP 코드입니다.", 401)

            # 정상 토큰 발급
            response = JsonResponse({
                "status": "success",
                "user": {
                    "user_id": user.user_id,
                    "displayname": user.displayname,
                    "email": user.email,
                    "avatar": user.avatar
                }
            })

            # 쿠키에 토큰 설정
            response.set_cookie(
                'access_token',
                generate_jwt_token(user, is_access=True),
                httponly=True,
                secure=True,
                samesite='Strict',
                max_age=settings.ACCESS_TOKEN_EXPIRATION
            )
            
            response.set_cookie(
                'refresh_token',
                generate_jwt_token(user, is_access=False),
                httponly=True,
                secure=True,
                samesite='Strict',
                max_age=settings.REFRESH_TOKEN_EXPIRATION
            )

            # 임시 토큰 삭제
            response.delete_cookie('temp_token')
            
            return response

        except json.JSONDecodeError:
            return create_error_response("INVALID_DATA", "잘못된 데이터 형식입니다.", 400)
        except Exception as e:
            logger.error(f"2FA 검증 중 오류 발생: {e}")
            return create_error_response("SERVER_ERROR", "서버 오류가 발생했습니다.", 500)

@method_decorator(jwt_required, name='dispatch')
@method_decorator(required_2fa, name='dispatch')
class Protected2FAView(View):
    """2FA가 필요한 보호된 리소스에 접근하는 뷰"""
    def get(self, request):
        """
        2FA가 활성화된 사용자만 접근 가능한 리소스입니다.

        Returns (200):
            {
                "message": "2FA 인증된 리소스에 접근했습니다."
            }
        """
        return JsonResponse({
            "message": "2FA 인증된 리소스에 접근했습니다."
        })
        
        
@method_decorator(jwt_required, name='dispatch')
class UserPollingView(View):
    """사용자 polling을 처리하는 뷰"""
    
    def post(self, request):
        """
        사용자의 활동 상태를 업데이트합니다.
        클라이언트는 주기적으로 이 엔드포인트를 호출해야 합니다.
        
        Returns (200):
            {
                "status": "ok"
            }
        """
        if update_last_seen(request.user.user_id):
            return JsonResponse({"status": "ok"})
        return create_error_response("SERVER_ERROR", "상태 업데이트 실패", 500)
        
        
@method_decorator(jwt_required, name='dispatch')
class ActiveUsersView(View):
    def get(self, request):
        """
        현재 활성 상태인 사용자 목록을 조회합니다.
        
        Returns (200):
            {
                "users": [{
                    "user_id": str, // NOTE: ijo
                    "displayname": str,
                    "is_friend": bool
                }]
            }
        """
        active_user_ids = get_active_users()  # 활성 유저 ID들 가져오기
        current_user = request.user
        
        # 활성 유저 정보 조회
        users = CustomUser.objects.filter(user_id__in=active_user_ids)
        
        # 현재 사용자의 친구 목록
        friend_ids = set(current_user.friends.values_list('user_id', flat=True))
        
        # 필요한 정보만 포함
        user_list = [{
            "user_id" : user.user_id,
            "displayname": user.displayname,
            "is_friend": user.user_id in friend_ids
        } for user in users if user.user_id != current_user.user_id]  # 자신은 제외
        
        return JsonResponse({"users": user_list})