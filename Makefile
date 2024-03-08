# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 16:02:57 by minsepar          #+#    #+#              #
#    Updated: 2024/03/08 20:13:55 by minsepar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		gcc

CFLAGS =	-Wall -Werror -Wextra -fsanitize=address

NAME =		minishell

SRCS =		main.c main_util.c

BUILTIN_SRCS =	builtin/builtin.c builtin/ft_cd.c builtin/ft_echo.c builtin/ft_env.c \
				builtin/ft_exit.c builtin/ft_export.c builtin/ft_pwd.c builtin/ft_unset.c \
				builtin/ft_cd2.c builtin/ft_cd_parse_dot.c builtin/parse_dot_loop.c \
				builtin/ft_cd_find_curpath.c builtin/ft_cd3.c

ENVIRON_SRCS =	environ/binary_tree_mem.c environ/binary_tree_util.c environ/binary_tree.c environ/env_to_binary_tree.c \
				environ/environ.c environ/binary_tree_pop.c

INNER_SRCS =	inner_parser/argument_parser_str_list.c inner_parser/argument_parser_utils.c inner_parser/argument_parser.c \
				inner_parser/argument_parser2.c inner_parser/argument_parser3.c inner_parser/argument_parser_env_var.c \
				inner_parser/argument_parser_asterisk.c inner_parser/argument_parser_str_node.c \
				inner_parser/argument_parser_str_list2.c

PARSER_SRCS = 	parser/lexar.c parser/parser.c parser/set_mem.c parser/util.c
				
TRAVERSE_SRCS =	traverse/traverse.c traverse/pipe_traverse.c traverse/redirection_util.c traverse/redirection.c

SIGNAL_SRCS =	signal/signal.c

SUBSYSTEM_SRCS =	subsystem/process_command.c subsystem/process_extern_command.c subsystem/process_extern_command2.c

UTIL_SRCS =		utils/common_util.c utils/error_exit.c utils/error_msg.c utils/cd_error_msg.c utils/error_exit2.c \
				utils/tmp_list.c utils/error_redirection.c

SRCS_OBJS = $(SRCS:.c=.o)

BUILTIN_OBJS = $(BUILTIN_SRCS:.c=.o)

ENVIRON_OBJS = $(ENVIRON_SRCS:.c=.o)

INNER_OBJS = $(INNER_SRCS:.c=.o)

PARSER_OBJS = $(PARSER_SRCS:.c=.o)

TRAVERSE_OBJS = $(TRAVERSE_SRCS:.c=.o)

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
#	$(CC) -g $(CFLAGS) $(SRCS) $(PARSER_SRCS) $(BUILTIN_SRCS) $(ENVIRON_SRCS) $(INNER_SRCS) $(SIGNAL_SRCS) $(SUBSYSTEM_SRCS) $(UTIL_SRCS) $(LIBFT) -o $(NAME) -lreadline
#	$(CC) -g -fsanitize=address $(CFLAGS) $(SRCS) $(PARSER_SRCS) $(BUILTIN_SRCS) $(ENVIRON_SRCS) $(INNER_SRCS) $(SIGNAL_SRCS) $(SUBSYSTEM_SRCS) $(UTIL_SRCS) $(LIBFT) -o $(NAME) -lreadline
	$(CC) -g $(CFLAGS) $(SRCS) $(TRAVERSE_SRCS) $(PARSER_SRCS) $(BUILTIN_SRCS) $(ENVIRON_SRCS) $(INNER_SRCS) $(SIGNAL_SRCS) $(SUBSYSTEM_SRCS) $(UTIL_SRCS) $(LIBFT) -o $(NAME) -lreadline

clean:
	rm -rf $(SRCS_OBJS) $(TRAVERSE_OBJS) $(BUILTIN_OBJS) $(ENVIRON_OBJS) $(INNER_OBJS) $(PARSER_OBJS) $(SIGNAL_OBJS) $(SUBSYSTEM_OBJS) $(UTIL_OBJS)
	make -C ./libft clean

fclean:
	make clean
	rm -rf $(NAME) $(LIBFT)

re:
	make fclean
	make all

test:
	make fclean
	make -C ./libft all bonus
	$(CC) -g $(CFLAGS) $(SRCS) $(PARSER_SRCS) $(BUILTIN_SRCS) $(ENVIRON_SRCS) $(INNER_SRCS) $(SIGNAL_SRCS) $(SUBSYSTEM_SRCS) $(UTIL_SRCS) $(LIBFT) -o $(NAME) -lreadline

run: re
	./minishell

.PHONY: all clean fclean re test
