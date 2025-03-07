#!/bin/sh

mkdir -p ./frontend/src/dist

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

# 개발용 서버 시작
python manage.py runserver 0.0.0.0:8000
