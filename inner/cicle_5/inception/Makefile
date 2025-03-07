NAME = inception
TARGET = srcs/docker-compose.yml
DATA = /home/seungwok/data

BLUE = \033[0;34m
RESET = \033[0m

all:
	@mkdir -p $(DATA)/wordpress
	@mkdir -p $(DATA)/mariadb
	@docker-compose -f $(TARGET) up -d --build
	@echo "$(BLUE)docker compose up$(RESET)"

up: all
build: all

clean:
	@docker-compose -f $(TARGET) down
	@echo "$(BLUE)docker compose down$(RESET)"

down: clean

fclean: clean
	@docker-compose -f $(TARGET) down --rmi all -v
	@sudo rm -rf $(DATA)
	@echo "$(BLUE)removed all data$(RESET)"

re: fclean all

restart: re

.PHONY: all up build clean down fclean re restart

# 실행중인 개별 컨테이너에 interactive shell 접속 방법
# docker exec -it <container_name> /bin/sh