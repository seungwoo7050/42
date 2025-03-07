CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
NAME = libftprintf.a
LIBFT = libft
LIBFT_A = libft.a
SRCS = ft_printf.c ft_printf_cs.c ft_printf_diu.c ft_printf_pxX.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT)/
	cp $(LIBFT)/$(LIBFT_A) $(NAME)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY : all bonus clean fclean re
