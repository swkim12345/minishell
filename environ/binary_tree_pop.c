/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_pop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:51:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/06 21:51:45 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	tree_pop_nochild(t_tree_node *target, t_tree_node *parent)
{
	t_tree_node	*node;

	if (!target->right_node || !target->left_node)
	{
		if (target->right_node)
			node = target->right_node;
		else
			node = target->left_node;
		if (parent->right_node == target)
			parent->right_node = node;
		else
			parent->left_node = node;
	}
	else
	{
		if (parent->right_node == target)
			parent->right_node = NULL;
		else
			parent->left_node = NULL;
	}
}

t_tree_node	*tree_pop(t_tree_node *head, char *key)
{
	t_tree_node	*parent;
	t_tree_node	*target;
	t_tree_node	*node;

	target = tree_search(head, &parent, key);
	if (!target || !parent)
		return (target);
	if (target->left_node && target->right_node)
	{
		node = target->left_node;
		if (!node->right_node)
		{
			exchange_node_key_value(node, target);
			target->left_node = NULL;
			return (node);
		}
		while (node->right_node->right_node)
			node = node->right_node;
		exchange_node_key_value(node->right_node, target);
		target = node->right_node;
		node->right_node = NULL;
	}
	else
		tree_pop_nochild(target, parent);
	return (target);
}
