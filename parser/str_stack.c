/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:28:30 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/14 21:51:13 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_str_node	*pop(t_str_list *list)
{
	t_str_node	*return_node;

	if (list == NULL || list->head == NULL)
		return (NULL);
	return_node = list->tail;
	list->size -= 1;
	if (list->size == 0)
	{
		list->head = NULL;
		list->tail = NULL;
		return (return_node);
	}
	list->tail = return_node->prev;
	return (return_node);
}

