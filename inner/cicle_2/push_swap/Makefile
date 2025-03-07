CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = push_swap
SRCS = main.c parse.c utils.c split.c error.c push.c swap.c rotate.c reverse.c sort.c small.c cal.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
