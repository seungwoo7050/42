# oauth/urls.py (API 라우트)
from django.urls import path
from . import views

app_name = 'api'  # API 네임스페이스

urlpatterns = [
    # Authentication URLs
    path('auth/status', views.AuthStatusView.as_view(), name='oauth-status'),
    path('auth/42/login', views.OAuth42LoginView.as_view(), name='oauth-login'),
    path('auth/42/callback', views.OAuth42CallbackView.as_view(), name='oauth-callback'),
    path('auth/logout', views.LogoutView.as_view(), name='logout'),
    path('auth/token/refresh', views.TokenRefreshView.as_view(), name='token-refresh'),
    
    # 2FA URLs
    path('auth/2fa/setup', views.TOTPSetupView.as_view(), name='2fa-setup'),
    path('auth/2fa/verify', views.TOTPVerifyView.as_view(), name='2fa-verify'),
    
    # User Management URLs
    path('users/profile', views.UserProfileView.as_view(), name='user-profile'),
    path('users/<str:user_id>/profile', views.UserProfileDetailView.as_view(), name='user-profile-detail'),
    path('users/friends', views.FriendView.as_view(), name='friends'),
    path('users/polling', views.UserPollingView.as_view(), name='user-polling'),
    path('users/active', views.ActiveUsersView.as_view(), name='active-users'),
    
    # Game URLs
    path('game/matches', views.MatchView.as_view(), name='matches'),
    path('game/matchmaking', views.GameMatchingView.as_view(), name='matchmaking'),
    
    # Protected Resources
    path('protected', views.Protected2FAView.as_view(), name='protected-resource'),
]