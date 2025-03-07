SHELL := /bin/sh
NAME := ft_transcendence

swagger := ./docs/openapi.yaml
docker-compose-dev-flags := --profile dev
docker-compose-prod-flags := --profile prod


# <!> switch to production build before submitting
.PHONY: all
all : build

# production build
.PHONY: build
build :
	docker compose up

# development build
# .PHONY: dev
# dev :
# 	docker compose $(docker-compose-dev-flags) up

.PHONY: up
up :
	docker compose up

.PHONY: stop
stop :
	docker compose stop

.PHONY: start
start :
	docker compose start

# `up`이 생성한 containers, networks 제거
.PHONY: down
down :
	docker compose down

# `down` + 생성된 volumes 제거
.PHONY: clean
clean :
	docker compose down -v

# `clean` + Compose 파일에 없는 containers 제거 + custom tag 없는 images 제거
.PHONY: fclean
fclean :
	docker compose down -v --remove-orphans --rmi "local"

.PHONY: re
re :
	$(MAKE) fclean
	$(MAKE) all

# Swagger UI로 OpenAPI doc 보기. 실행 시 브라우저 열림.
# 에러 발생 시 nvm으로 사용 중인 node 버전 확인
.PHONY: api
api :
	npx --yes open-swagger-ui --open $(swagger)
