/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:03:58 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/06 17:14:22 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	free_parse_str(t_parse_str *parse_str)
{
	free(parse_str->str);
	parse_str->str = 0;
}

void	init_parse_str(t_parse_str *parse_str)
{
	ft_memset((void *)(parse_str), 0, sizeof(t_parse_str));
	parse_str->str = ft_calloc(sizeof(char), 11);
	parse_str->malloc_size = 10;
	parse_str->asterisk_flag = -1;
}

void	init_str_node(t_str_node *str_node)
{
	str_node->next = 0;
	str_node->str = 0;
	str_node->prev = 0;
}

void	init_str_list(t_str_list *str_list)
{
	memset(str_list, 0, sizeof(t_str_list));
}

void	append_char(t_parse_str *parse_str, char c)
{
	char	*new_malloc;
	int		prev_size;

	if (parse_str->malloc_size == parse_str->cursor)
	{
		prev_size = parse_str->cursor;
		parse_str->malloc_size *= 2;
		new_malloc = malloc(parse_str->malloc_size + 1);
		while (prev_size--)
			new_malloc[prev_size] = parse_str->str[prev_size];
		free(parse_str->str);
		parse_str->str = new_malloc;
	}
	parse_str->str[parse_str->cursor] = c;
	parse_str->cursor++;
	parse_str->str[parse_str->cursor] = 0;
}
