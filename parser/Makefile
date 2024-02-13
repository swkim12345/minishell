
CC = cc

CFLAGS = -Wall -Werror -Wextra 

NAME = minishell

SRCS = finder.c lexar.c main.c set_mem.c traverse.c util.c \
	argument_parser_str_list.c argument_parser_utils.c

OBJS = $(SRCS:.c=.o)

LIBFT = libftprintf.a

all: $(NAME)

%.o: %.c
	$(CC) -c -g $(FLAGS) $< -o $@

$(LIBFT):
	make -C ./libft all bonus

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

clean:
	rm -rf $(OBJS)

fclean:
	make clean
	rm -rf $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
