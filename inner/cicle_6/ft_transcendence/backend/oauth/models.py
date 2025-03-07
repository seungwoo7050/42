from django.contrib.auth.models import AbstractBaseUser, BaseUserManager, PermissionsMixin
from django.core.exceptions import ValidationError
from django.db import models
from .common import validate_displayname

class TokenBlacklist(models.Model):
    """
    사용된 리프레시 토큰을 저장하는 모델입니다.
    JWT 토큰의 명시적 무효화(예: 로그아웃)를 지원합니다.
    """
    token = models.TextField(
        unique=True,
        help_text="무효화된 Refresh 토큰"
    )
    blacklisted_at = models.DateTimeField(
        auto_now_add=True,
        help_text="토큰이 블랙리스트에 추가된 시간"
    )

    class Meta:
        indexes = [
            models.Index(fields=['token'], name='token_idx'),
        ]

class CustomUserManager(BaseUserManager):
    """
    사용자 생성을 관리하는 매니저입니다.
    42 OAuth를 통한 사용자 생성을 주로 처리합니다.
    """
    def create_user(self, email, user_id, displayname, **extra_fields):
        """
        일반 사용자를 생성합니다.
        OAuth 인증을 통해 생성되므로 비밀번호는 처리하지 않습니다.
        """
        if not email:
            raise ValueError('이메일 주소는 필수입니다.')
        if not user_id:
            raise ValueError('유저 ID는 필수입니다.')
        if not displayname:
            raise ValueError('표시 이름은 필수입니다.')

        user = self.model(
            email=self.normalize_email(email),
            user_id=user_id,
            displayname=displayname,
            **extra_fields
        )
        user.set_unusable_password()  # OAuth 사용자는 비밀번호를 사용하지 않음
        user.save(using=self._db)
        return user

    def create_superuser(self, email, user_id, displayname, **extra_fields):
        """
        관리자 사용자를 생성합니다.
        개발 및 관리 목적으로만 사용됩니다.
        """
        extra_fields.setdefault('is_staff', True)
        extra_fields.setdefault('is_superuser', True)

        return self.create_user(email, user_id, displayname, **extra_fields)

class CustomUser(AbstractBaseUser, PermissionsMixin):
    """
    사용자 정보를 저장하는 모델입니다.
    OAuth 인증 기반으로 설계되어 있으며, 게임 서비스에 필요한 필드들을 포함합니다.
    """
    # 기본 식별 필드
    user_id = models.CharField(
        max_length=10,
        primary_key=True,
        unique=True,
        error_messages={'unique': '이미 사용 중인 유저 ID입니다.'}
    )
    displayname = models.CharField(
        max_length=10,
        unique=True,
        validators=[validate_displayname],
        error_messages={'unique': '이미 사용 중인 표시 이름입니다.'}
    )
    email = models.EmailField(
        unique=True,
        error_messages={'unique': '이미 사용 중인 이메일입니다.'}
    )

    # 프로필 관련 필드
    avatar = models.CharField(
        max_length=255,
        blank=True,
        null=True,
        help_text='프로필 이미지 파일 경로'
    )

    avatar_hash = models.CharField(
        max_length=32,
        blank=True,
        null=True,
    )

    # 상태 관련 필드
    is_staff = models.BooleanField(
        default=False,
        help_text='관리자 권한 여부'
    )
    date_joined = models.DateTimeField(auto_now_add=True)
    last_login = models.DateTimeField(
        blank=True, 
        null=True,
        help_text='과제 요구사항에 따른 마지막 로그인 시간'
    )

    # 2FA 관련 필드
    totp_secret = models.CharField(
        max_length=32,
        blank=True,
        null=True,
        help_text='TOTP 2FA 비밀키'
    )
    is_totp_enabled = models.BooleanField(
        default=False,
        help_text='2FA 활성화 상태'
    )

    # 친구 관계
    friends = models.ManyToManyField(
        'self',
        symmetrical=True,
        blank=True,
        help_text='양방향 친구 관계'
    )

    class Meta:
        """자주 사용되는 검색을 위한 인덱스 정의"""
        indexes = [
            models.Index(fields=['displayname'], name='displayname_idx'),
        ]

    objects = CustomUserManager()

    USERNAME_FIELD = 'user_id'
    REQUIRED_FIELDS = ['email', 'displayname']

    def add_friend(self, friend):
        """
        친구를 추가합니다.
        이미 친구인 경우 False를 반환합니다.
        """
        if friend != self and not self.friends.filter(user_id=friend.user_id).exists():
            self.friends.add(friend)
            return True
        return False

    def remove_friend(self, friend):
        """
        친구를 삭제합니다.
        친구가 아닌 경우 False를 반환합니다.
        """
        if self.friends.filter(user_id=friend.user_id).exists():
            self.friends.remove(friend)
            return True
        return False

    def __str__(self):
        return f"{self.displayname} ({self.user_id})"

class Match(models.Model):
    """
    게임 매치 기록을 저장하는 모델입니다.
    플레이어 정보, 점수, 승자 등 게임의 결과를 저장합니다.
    """
    # 게임 참가자
    player1 = models.ForeignKey(
        CustomUser,
        on_delete=models.CASCADE,
        related_name='matches_as_player1',
        help_text='첫 번째 플레이어'
    )
    player2 = models.ForeignKey(
        CustomUser,
        on_delete=models.CASCADE,
        related_name='matches_as_player2',
        null=True,
        blank=True,
        help_text='두 번째 플레이어'
    )
    winner = models.ForeignKey(
        CustomUser,
        on_delete=models.CASCADE,
        related_name='won_matches',
        null=True,
        blank=True,
        help_text='매치의 승자'
    )

    # 게임 결과
    score_player1 = models.IntegerField(
        default=0,
        help_text='첫 번째 플레이어의 점수'
    )
    score_player2 = models.IntegerField(
        default=0,
        help_text='두 번째 플레이어의 점수'
    )

    # 시간 정보
    created_at = models.DateTimeField(
        auto_now_add=True,
        help_text='매치 생성 시간'
    )

    class Meta:
        indexes = [
            models.Index(fields=['player1', 'created_at'], name='player1_date_idx'),
            models.Index(fields=['player2', 'created_at'], name='player2_date_idx'),
            models.Index(fields=['created_at'], name='match_date_idx'),
        ]

    def save(self, *args, **kwargs):
        self.clean()  # clean() 메서드를 자동으로 호출
        super().save(*args, **kwargs)
        
    def clean(self):
        """매치 데이터의 유효성을 검증합니다."""
        if self.player1 == self.player2:
            raise ValidationError('동일한 플레이어와의 매치는 불가능합니다.')
            
        if self.winner and self.winner not in [self.player1, self.player2]:
            raise ValidationError('승자는 매치 참가자 중 한 명이어야 합니다.')

    def __str__(self):
        return f"{self.player1.displayname} vs {self.player2.displayname}"