# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 16:02:57 by minsepar          #+#    #+#              #
#    Updated: 2024/03/05 20:32:39 by sunghwki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra 

NAME = minishell

SRCS = main.c

BUILTIN_SRCS = $(addprefix builtin/, builtin.c ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c)

ENVIRON_SRCS = $(addprefix environ/, binary_tree_mem.c binary_tree_util.c binary_tree.c env_to_binary_tree.c environ.c)

INNER_SRCS = $(addprefix inner_parser/, argument_parser_utils.c argument_parser.c argument_parser_str_list.c)

PARSER_SRCS = $(addprefix parser/, lexar.c parser.c traverse.c set_mem.c util.c)

TRAVERSR_SRCS = $(addprefix parser/, traverse.c)

SIGNAL_SRCS = $(addprefix signal/, signal.c)

SUBSYSTEM_SRCS = $(addprefix subsystem/, process_command.c)

UTIL_SRCS = $(addprefix utils/, common_util.c error_exit.c error_msg.c)

SRCS_OBJS = $(SRCS:.c=.o)

BUILTIN_OBJS = $(BUILTIN_SRCS:.c=.o)

ENVIRON_OBJS = $(ENVIRON_SRCS:.c=.o)

INNER_OBJS = $(INNER_SRCS:.c=.o)

PARSER_OBJS = $(PARSER_SRCS:.c=.o)

SIGNAL_OBJS = $(SINGAL_SRCS:.c=.o)

SUBSYSTEM_OBJS = $(SUBSYSTEM_SRCS:.c=.o)

UTIL_OBJS = $(UTIL_SRCS:.c=.o)

LIBFT = ./libft/libftprintf.a

all: $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(LIBFT):
	make -C ./libft all bonus

$(NAME): $(LIBFT) 
	$(CC) -g -fsanitize=address $(CFLAGS) $(SRCS) $(PARSER_SRCS) $(BUILTIN_SRCS) $(ENVIRON_SRCS) $(INNER_SRCS) $(SIGNAL_SRCS) $(SUBSYSTEM_SRCS) $(UTIL_SRCS) $(LIBFT) -o $(NAME) -lreadline
#	$(CC) -g -fsanitize=address  -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include $(CFLAGS) $(SRCS) $(PARSER_SRCS) $(BUILTIN_SRCS) $(ENVIRON_SRCS) $(INNER_SRCS) $(SIGNAL_SRCS) $(SUBSYSTEM_SRCS) $(UTIL_SRCS) $(LIBFT) -o $(NAME) -lreadline

clean:
	rm -rf $(SRCS_OBJS) $(BUILTIN_OBJS) $(ENVIRON_OBJS) $(INNER_OBJS) $(PARSER_OBJS) $(SIGNAL_OBJS) $(SUBSYSTEM_OBJS) $(UTIL_OBJS)
	make -C ./libft clean

fclean:
	make clean
	rm -rf $(NAME) $(LIBFT)

re:
	make fclean
	make all

test:
	cc main.c test.c ./signal/signal.c common_util.c -lreadline $(LIBFT)

run: re
	./minishell

.PHONY: all clean fclean re
