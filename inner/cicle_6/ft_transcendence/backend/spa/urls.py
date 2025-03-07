# spa/urls.py (프로젝트 레벨)
from django.contrib import admin
from django.urls import path, include, re_path
from django.views.generic import TemplateView
from django.conf import settings
from django.conf.urls.static import static
from django.views.static import serve # for test only
from oauth.views import OAuth42CallbackView

urlpatterns = [
    # API 엔드포인트 - 모든 API는 /api/v1/ 아래에 위치
    path('favicon.ico', include('index.urls', namespace='favicon'), name = 'favicon'),
    # path('admin', admin.site.urls),
    path('api/v1/', include('oauth.urls')),  # api_urls.py로 이름 변경 추천

    # path('auth/callback/42', OAuth42CallbackView.as_view(), name='oauth-callback'),
    # path('', include('index.urls')),  # 이 줄 추가
    # re_path(r"^static/(?P<path>.*)$", serve, {"document_root": settings.STATIC_ROOT}), # for test only
    # re_path(
    #     r"^.*$", TemplateView.as_view(template_name="index.html", extra_context={"debug": settings.DEBUG})
    # ),
]

# 개발 환경에서만 static 파일 서빙 (DEBUG=True 일 때만)
if settings.DEBUG:
    urlpatterns += static(settings.STATIC_URL, document_root=settings.STATIC_ROOT)
    urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
    # 관리자 페이지
    urlpatterns += [ path('admin', admin.site.urls) ]

# SPA를 위한 catchwall 라우트 - 반드시 마지막에 위치
urlpatterns += [
    re_path(
        r"^.*$", TemplateView.as_view(template_name="index.html", extra_context={"debug": settings.DEBUG})
    ),
    # path('<path:path>', TemplateView.as_view(template_name="index.html", extra_context={"debug": settings.DEBUG})),
]
