from django.contrib import admin
from django.contrib.auth.admin import UserAdmin
from .models import CustomUser

@admin.register(CustomUser)
class CustomUserAdmin(UserAdmin):
    model = CustomUser

    # 검색, 필터링, 정렬 필드를 `CustomUser`에 맞게 설정
    list_display = ('user_id', 'displayname', 'email', 'is_staff', 'date_joined')
    list_filter = ('is_staff', 'is_totp_enabled', 'date_joined')
    search_fields = ('user_id', 'displayname', 'email')
    ordering = ('user_id',)  # 정렬 기준

    # 읽기 전용 필드
    readonly_fields = ('date_joined', 'last_login')

    # 사용자 상세 보기 필드
    fieldsets = (
        (None, {'fields': ('user_id', 'displayname', 'email', 'password')}),
        ('Permissions', {'fields': ('is_staff', 'is_superuser', 'groups', 'user_permissions')}),
        ('Important dates', {'fields': ('last_login', 'date_joined')}),
    )

    # 사용자 생성 페이지 필드
    add_fieldsets = (
        (None, {
            'classes': ('wide',),
            'fields': ('user_id', 'displayname', 'email', 'password1', 'password2', 'is_staff', 'is_superuser'),
        }),
    )