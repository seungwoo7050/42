from pathlib import Path
import os

# Project Directory Configuration
# BASE_DIR은 프로젝트의 루트 디렉토리를 가리킵니다
BASE_DIR = Path(__file__).resolve().parent.parent
# Vite로 빌드된 프론트엔드 파일들의 위치를 지정합니다
VITE_APP_DIR = os.path.join(BASE_DIR, 'frontend', 'src')

# Core Application Settings
APP_NAME = "ft_transcendence"
# DEBUG 모드는 기본적으로 False이며, 환경변수에서 'True' 문자열이 주어질 때만 활성화됩니다
DEBUG = os.environ.get('DEBUG', 'False') == 'True'
# SECRET_KEY는 필수 값으로, 없으면 서버가 구동되지 않습니다
SECRET_KEY = os.environ.get('SECRET_KEY')
if not SECRET_KEY:
    raise ValueError("SECRET_KEY is not set")

# Host Configuration
# 쉼표로 구분된 허용 호스트 문자열을 리스트로 변환합니다
ALLOWED_HOSTS = ['127.0.0.1', 'localhost']
INTERNAL_IPS = ["127.0.0.1"]

# Application Definition
INSTALLED_APPS = [
    # "corsheaders",  # cors 세팅
    "django.contrib.admin",
    "django.contrib.auth",
    "django.contrib.contenttypes",
    "django.contrib.sessions",
    "django.contrib.messages",
    "django.contrib.staticfiles",
    "oauth",
    "index",
]

# Middleware Configuration
MIDDLEWARE = [
    # 'corsheaders.middleware.CorsMiddleware',  # cors 세팅
    "django.middleware.security.SecurityMiddleware",
    "django.contrib.sessions.middleware.SessionMiddleware",
    "django.middleware.common.CommonMiddleware",
    # "django.middleware.csrf.CsrfViewMiddleware",
    "django.contrib.auth.middleware.AuthenticationMiddleware",
    "django.contrib.messages.middleware.MessageMiddleware",
    "django.middleware.clickjacking.XFrameOptionsMiddleware",
]

# URL Configuration
ROOT_URLCONF = "spa.urls"

# Template Configuration
TEMPLATES = [
    {
        "BACKEND": "django.template.backends.django.DjangoTemplates",
        "DIRS": [],
        "APP_DIRS": True,
        "OPTIONS": {
            "context_processors": [
                "django.template.context_processors.debug",
                "django.template.context_processors.request",
                "django.contrib.auth.context_processors.auth",
                "django.contrib.messages.context_processors.messages",
            ],
        },
    },
]

# WSGI Application
WSGI_APPLICATION = "spa.wsgi.application"

# Database Configuration
DATABASES = {
    "default": {
        "ENGINE": "django.db.backends.postgresql",
        "NAME": os.environ.get('POSTGRES_DB', ''),
        "USER": os.environ.get('POSTGRES_USER', ''),
        "PASSWORD": os.environ.get('POSTGRES_PASSWORD', ''),
        # "HOST": "localhost",
        "HOST": ("db-dev" if DEBUG else "db"),
        "PORT": 5432,
    }
}

# 42 Authorization
OAUTH_42_CLIENT_ID = os.getenv('OAUTH_42_CLIENT_ID')
OAUTH_42_CLIENT_SECRET = os.getenv('OAUTH_42_CLIENT_SECRET')
OAUTH_42_REDIRECT_URI='https://127.0.0.1/auth/callback/42'
OAUTH_42_TOKEN_URL='https://api.intra.42.fr/oauth/token'
OAUTH_42_AUTHORIZE_URL='https://api.intra.42.fr/oauth/authorize'
OAUTH_42_USERINFO_URL='https://api.intra.42.fr/v2/me'

# Redis 설정
REDIS_HOST = os.getenv('REDIS_HOST', ('redis-dev' if DEBUG else 'redis'))  # 기본값: redis
# REDIS_HOST = 'localhost'
REDIS_PORT = int(os.getenv('REDIS_PORT', 6379))  # 기본값: 6379
REDIS_DB = int(os.getenv('REDIS_DB', 0))  # 기본값: 0

# # Cache Configuration
# CACHES = {
#     "default": {
#         "BACKEND": "django.core.cache.backends.redis.RedisCache",
#         "LOCATION": f"redis://{os.environ.get('REDIS_HOST', 'redis')}:{os.environ.get('REDIS_PORT', '6379')}/{os.environ.get('REDIS_DB', '0')}",
#     }
# }

# Authentication Configuration
AUTH_USER_MODEL = "oauth.CustomUser"

# JWT Configuration
JWT_SECRET_KEY = os.environ.get('JWT_SECRET_KEY', '')
JWT_ALGORITHM = os.environ.get('JWT_ALGORITHM', 'HS256')
ACCESS_TOKEN_EXPIRATION = int(os.environ.get('ACCESS_TOKEN_EXPIRATION', '30000'))
REFRESH_TOKEN_EXPIRATION = int(os.environ.get('REFRESH_TOKEN_EXPIRATION', '86400'))

# Static and Media Files Configuration
# URL prefix for static files
STATIC_URL = '/static/'
# Directory where collectstatic will collect static files
STATIC_ROOT = os.path.join(BASE_DIR, 'collected_static')
# URL prefix for media files
MEDIA_URL = '/media/'
# Directory where uploaded files will be stored
MEDIA_ROOT = os.path.join(BASE_DIR, 'media')
# Additional locations of static files
STATICFILES_DIRS = [
    os.path.join(VITE_APP_DIR, 'dist'),
    # os.path.join(BASE_DIR, 'frontend'),
    os.path.join(BASE_DIR, 'static'),
]

# Upload Restrictions
MAX_UPLOAD_SIZE = 5242880  # 기본값 5MB
ALLOWED_IMAGE_TYPES = os.environ.get('ALLOWED_IMAGE_TYPES', 'image/jpeg,image/png').split(',')

# Logging Configuration
LOGGING = {
    "version": 1,
    "disable_existing_loggers": False,
    "handlers": {
        "console": {
            "class": "logging.StreamHandler",
        },
    },
    "root": {
        "handlers": ["console"],
        "level": "INFO",
    },
    "django": {
        "handlers": ["console"],
        "level": "INFO",
        "propagate": True,
    },
}

# Polling Timeout configuration
POLLING_TIMEOUT = 30
GAME_STATUS_TIMEOUT = 1800

# Default Primary Key Field Type
DEFAULT_AUTO_FIELD = "django.db.models.BigAutoField"

# cors 세팅
CORS_ALLOW_ALL_ORIGINS = True  # 개발 환경에서만 사용
CORS_ALLOW_CREDENTIALS = True  # credentials: 'include' 사용시 필요
