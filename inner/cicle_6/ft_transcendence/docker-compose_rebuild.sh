# 실행중인 컨테이너 종료
docker-compose down -v

# 캐시 제거 (optional)
docker builder prune --all --force
docker rm -f $(docker ps -aq)
docker rmi -f $(docker images -aq)
docker network prune --force
docker volume prune --force

# 재빌드 및 실행
docker-compose build --no-cache
docker-compose up --force-recreate
