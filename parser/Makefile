
CC = cc

CFLAGS = -Wall -Werror -Wextra 

NAME = minishell

SRCS = traverse.c parser.c \
	../inner_parser/argument_parser_str_list.c ../inner_parser/argument_parser_utils.c


OBJS = $(SRCS:.c=.o)

LIBFT = libftprintf.a

all: $(NAME)

test: 
	cc $(SRCS) test.c

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
