/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:55:43 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/06 17:13:03 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_tree_node	*init_tree_node(void)
{
	t_tree_node	*node;

	node = (t_tree_node *)ft_calloc(sizeof(t_tree_node), 1);
	if (!node)
		return (NULL);
	return (node);
}

void	node_delete(t_tree_node *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

static void	recur_tree_delete(t_tree_node *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	recur_tree_delete(node->left_node);
	recur_tree_delete(node->right_node);
	free(node);
}

void	free_tree_delete(t_tree_head *head)
{
	if (!head)
		return ;
	recur_tree_delete(head->head);
	free(head);
}
