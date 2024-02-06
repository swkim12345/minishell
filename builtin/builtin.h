/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:37:09 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/06 22:15:39 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

typedef struct s_parse_str
{
    char	*str;
    size_t  malloc_size;
    size_t  cursor;
}	t_parse_str;

typedef struct s_str_node
{
	char				*str;
	struct s_str_node	*next;
}  	t_str_node;

typedef struct s_str_list
{
    int  size;
    t_str_node	*head;
	t_str_node	*tail;
}   t_str_list;

/* argument_parser.c */
void	parse_single_char(t_parse_str *parse_str, char **str);
void	parse_double_quote(t_parse_str *parse_str, char **str);
void	parse_single_quote(t_parse_str *parse_str, char **str);
void	parse_single_word(char **str, t_str_list *str_list);

/* argument_parser_str_list.c */
void	enqueue(t_str_list *str_list, t_str_node *str_node);
t_str_node	*dequeue(t_str_list *str_list);
void	add_string_node(t_str_list *str_list, t_parse_str *parse_str);
char	**list_to_char_arr(t_str_list *str_list);

/* argument_parser_utils.c */
void	free_parse_str(t_parse_str *parse_str);
void	init_parse_str(t_parse_str *parse_str);
void	init_str_node(t_str_node *str_node);
void	init_str_list(t_str_list *str_list);
void	append_char(t_parse_str *parse_str, char c);

/* ft_echo.c */
void	print_echo(char **str);
int ft_echo(char *str);
int		ft_isspace(int c);

#endif