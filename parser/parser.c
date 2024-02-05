/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:52:54 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/05 18:05:03 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_linked_list	*init_parse(char *input)
{
	
}

t_linked_list	*parser(char *input)
{
	t_linked_list	*list;
	t_list_node		*node;

	list = (t_linked_list *)malloc(sizeof(t_linked_list));
	node = (t_list_node *)malloc(sizeof(t_list_node));
	list->size = 1;
	list->front = node;
	list->back = node;
	node->next = node;
	node->str = input;
}
