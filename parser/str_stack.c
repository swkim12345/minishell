/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:28:30 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/14 21:29:51 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_str_node	*pop(t_str_list *list)
{
	t_str_node	*next;

	if (list == NULL || list->head == NULL)
		return (NULL);
	next = list->head;
	list->size -= 1;
	if (list->size == 0)
	{
		list->head = NULL;
		list->tail = NULL;
		return (next);
	}
	list->head = next->next;
	return (next);
}

void	push(t_str_list *list, t_str_node *node)
{
	if (list->head == NULL)
	{	
		list->head = node;
		list->tail = node;
	}
	else
	{
		node->next = list->head;
		list->head = node;
	}
	list->size++;
}
