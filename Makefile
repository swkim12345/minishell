# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 16:02:57 by minsepar          #+#    #+#              #
#    Updated: 2024/02/26 19:02:07 by minsepar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra 

NAME = minishell

SRCS = main.c

BUILTIN_SRCS = builtin/builtin.c builtin/ft_cd.c builtin/ft_echo.c builtin/ft_env.c builtin/ft_exit.c builtin/ft_export.c builtin/ft_pwd.c builtin/ft_unset.c

ENVIRON_SRCS = environ/binary_tree_mem.c environ/binary_tree_util.c environ/binary_tree.c environ/env_to_binary_tree.c environ/environ.c

INNER_SRCS = inner_parser/argument_parser_str_list.c inner_parser/argument_parser_utils.c inner_parser/argument_parser.c

PARSER_SRCS = parser/lexar.c parser/parser.c parser/set_mem.c parser/traverse.c parser/util.c

SINGAL_SRCS = signal/signal.c

SUBSYSTEM_SRCS = subsystem/process_command.c

UTIL_SRCS = utils/common_util.c utils/error_exit.c utils/error_msg.c

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

$(NAME): $(LIBFT) $(SRCS_OBJS) $(BUILTIN_OBJS) $(ENVIRON_OBJS) $(INNER_OBJS) $(SIGNAL_OBJS) $(SUBSYSTEM_OBJS) $(UTIL_OBJS)
	$(CC) $(CFLAGS) $(SRCS_OBJS) $(BUILTIN_OBJS) $(ENVIRON_OBJS) $(INNER_OBJS) $(SIGNAL_OBJS) $(SUBSYSTEM_OBJS) $(UTIL_OBJS) $(LIBFT) -o $(NAME) -lreadline

clean:
	rm -rf $(SRCS_OBJS) $(BUILTIN_OBJS) $(ENVIRON_OBJS) $(INNER_OBJS) $(SIGNAL_OBJS) $(SUBSYSTEM_OBJS) $(UTIL_OBJS)

fclean:
	make clean
	rm -rf $(NAME)

re:
	make fclean
	make all

test:
	cc main.c test.c ./signal/signal.c common_util.c -lreadline $(LIBFT)

run: re
	./minishell

.PHONY: all clean fclean re