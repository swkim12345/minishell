/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser_str_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:03:03 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/14 21:56:47 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	enqueue(t_str_list *str_list, t_str_node *str_node)
{
	if (!(str_list->head))
	{
		str_list->head = str_node;
		str_list->tail = str_node;
	}
	else
	{
		str_list->tail->next = str_node;
		str_node->prev = str_list->tail;
		str_list->tail = str_node;
	}
	str_list->size++;
}

t_str_node	*dequeue(t_str_list *str_list)
{
	t_str_node	*head;

	if (!(str_list->head))
		return (0);
	else if (str_list->size == 1)
	{
		head = str_list->head;
		str_list->head = 0;
		str_list->tail = 0;
	}
	else
	{
		head = str_list->head;
		str_list->head = head->next;
		str_list->head->prev = 0;
	}
	str_list->size--;
	return (head);
}

t_str_node	*create_node(char *str)
{
	t_str_node	*str_node;

	str_node = malloc(sizeof(t_str_node));
	str_node->str = str;
	str_node->next = 0;
	return (str_node);
}

void	add_string_node(t_str_list *str_list, t_parse_str *parse_str)
{
	char	*str;

	str = ft_substr(parse_str->str, 0, parse_str->cursor);
	free_parse_str(parse_str);
	enqueue(str_list, create_node(str));
}

char	**list_to_char_arr(t_str_list *str_list)
{
	char		**return_list;
	t_str_node	*node;
	int			i;

	i = 0;
	return_list = malloc(sizeof(char *) * (str_list->size + 1));
	return_list[str_list->size] = 0;
	while (str_list->size > 0)
	{
		node = dequeue(str_list);
		return_list[i] = node->str;
		free(node);
		i++;
	}
	return (return_list);
}
