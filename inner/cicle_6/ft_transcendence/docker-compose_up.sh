# 실행중인 컨테이너 종료
docker-compose down -v

# 캐시 제거 (optional)
docker system prune -f
docker system prune --volumes -f # 네트워크, 볼륨 포함 완전 초기화

# 재빌드 및 실행
docker-compose build --no-cache
docker-compose up --force-recreate

