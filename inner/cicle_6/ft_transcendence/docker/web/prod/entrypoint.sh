#!/bin/sh

# 데이터베이스가 준비될 때까지 대기
echo "Waiting for database..."
while ! python manage.py check; do
  sleep 1
done
echo "Database is ready"

# 마이그레이션 실행 
echo "Applying migrations..."
python manage.py makemigrations
python manage.py migrate

# 정적 파일 수집
echo "Collecting static files..."
python manage.py collectstatic --noinput --clear

# Gunicorn을 사용하여 애플리케이션 실행 (Nginx와 함께 사용)
echo "Starting Gunicorn server..."
gunicorn spa.wsgi:application --bind 0.0.0.0:8000 --workers 3
