# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 16:02:57 by minsepar          #+#    #+#              #
#    Updated: 2024/02/07 20:13:12 by minsepar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra 

NAME = minishell

SRCS = main.c common_util.c

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libftprintf.a

all: $(NAME)

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

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