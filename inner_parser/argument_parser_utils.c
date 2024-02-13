/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:03:58 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/13 14:59:24 by minsepar         ###   ########.fr       */
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
	parse_str->str = malloc(11);
	parse_str->str[0] = 0;
	parse_str->cursor = 0;
	parse_str->malloc_size = 10;
	parse_str->asterisk_flag = 0;
}

void	init_str_node(t_str_node *str_node)
{
	str_node->next = 0;
	str_node->str = 0;
}

void	init_str_list(t_str_list *str_list)
{
	str_list->head = 0;
	str_list->tail = 0;
	str_list->size = 0;
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