###################################################################
#                          ANSI COLORS                            #
###################################################################
GREEN	:= \033[0;32m
RED		:= \033[0;31m
YELLO	:= \033[0;33m
BLUE	:= \033[0;34m
RESET	:= \033[0m

###################################################################
#                          PROJECT VARS                           #
###################################################################
NAME	:= mylibc.a
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
AR		:= ar
ARFLAGS	:= rcs
SRC_DIR	:= src
OBJ_DIR	:= obj
INCLUDE	:= $(SRC_DIR)/mylibc.h

###################################################################
#                          SOURCE FILES                           #
###################################################################
SRCS		:= $(filter-out %_bonus.c, $(wildcard $(SRC_DIR)/my_*.c))
SRCS_BONUS	:= $(wildcard $(SRC_DIR)/my_*_bonus.c)

OBJS		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJS_BONUS	:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_BONUS))

###################################################################
#                          MAKE TARGEST                           #
###################################################################
.PHONY: all bonus clean fclean re

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "$(BLUE)[AR]$(RESET) Creating archive $(NAME)"
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo "$(GREEN)Library $(NAME) built successfully!$(RESET)"

bonus: bonus_timestamp

bonus_timestamp: $(NAME) $(OBJS_BONUS)
	@echo "$(BLUE)[BONUS]$(RESET) Adding bonus objects..."
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS_BONUS)
	@echo "$(GREEN)Bonus objects added!$(RESET)"
	@touch bonus_timestamp
# bonus 명령어의 레시피를 직접 설정하지 않고 한 번 거치는 이유는 timestamp를 명시하여 리링크를 방지하기 위함이다.
# 현재 makefile의 빌드 구조가 make, make bonus 둘 다 같은 이름의 파일을 생성하기 때문에 이 과정을 거치지 않으면 리링크가 발생한다.

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@echo "$(YELLO)[CC]$(RESET) Compiling $< ..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

###################################################################
#                          CLEANING RULES                         #
###################################################################
clean:
	@echo "$(RED)[CLEAN]$(RESET) Removing object files..."
	@rm -rf $(OBJ_DIR) bonus_timestamp

fclean: clean
	@echo "$(RED)[FCLEAN]$(RESET) Removing library and biranires..."
	@rm -f $(NAME)

re: fclean all