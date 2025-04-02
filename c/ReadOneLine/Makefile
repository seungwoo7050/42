###################################################################
#                          ANSI COLORS                            #
###################################################################
GREEN	:= \033[0;32m
RED		:= \033[0;31m
YELLOW	:= \033[0;33m
BLUE	:= \033[0;34m
RESET	:= \033[0m

###################################################################
#                          PROJECT VARS                           #
###################################################################
NAME		:= read_one_line_test
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
SRC_DIR		:= src
OBJ_DIR		:= obj

###################################################################
#                          FILES                                  #
###################################################################
HDRS		:= $(wildcard $(SRC_DIR)/*.h)
SRCS		:= $(wildcard $(SRC_DIR)/*.c)
OBJS		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

###################################################################
#                          DEFAULT TARGET                         #
###################################################################
.PHONY: all clean fclean re test

all: test

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS)
	@echo "$(YELLOW)[CC]$(RESET) Compiling $< ..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "$(BLUE)[LD]$(RESET) Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Build complete: $(NAME)$(RESET)"

###################################################################
#                          TEST TARGET                            #
###################################################################
test: $(NAME)
	@echo "$(YELLOW)[TEST]$(RESET) Creating test file..."
	@echo "Hello, World!" > test.txt
	@echo "Line Two." >> test.txt
	@echo "Last line without newline" >> test.txt

	@echo "$(YELLOW)[TEST]$(RESET) Running $(NAME)..."
	@./$(NAME) test.txt > test_output.txt

	@echo "$(YELLOW)[TEST]$(RESET) Comparing results..."
	@diff -q test.txt test_output.txt > /dev/null && \
	echo "$(GREEN)[OK]$(RESET) Output matches expected ✅" || \
	(echo "$(RED)[FAIL]$(RESET) Output differs ❌"; \
	echo ""; echo "$(YELLOW)Expected:$(RESET)"; cat test.txt; \
	echo ""; echo "$(YELLOW)Got:$(RESET)"; cat test_output.txt)

	@rm -f test.txt test_output.txt

###################################################################
#                          CLEANING RULES                         #
###################################################################
clean:
	@echo "$(RED)[CLEAN]$(RESET) Removing object files..."
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)[FCLEAN]$(RESET) Removing binary..."
	@rm -f $(NAME)

re: fclean all
