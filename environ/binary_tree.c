/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:22:04 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/26 12:04:00 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	tree_insert(t_tree_head *head, t_tree_node *leaf)
{
	t_tree_node	*next;
	int			tmp;

	next = head->head;
	if (!next)
	{
		head->head = leaf;
		return (FUNC_SUC);
	}
	while (next)
	{
		tmp = ft_strlen(leaf->key);
		tmp = ft_strncmp(next->key, leaf->key, tmp + 1);
		if (tmp == 0)
		{
			next->value = leaf->value;
			node_delete(leaf);
			return (FUNC_SUC);
		}
		if (tmp < 0)
		{
			if (!next->left_node)
			{
				next->left_node = leaf;
				break ;
			}
			next = next->left_node;
		}
		if (tmp > 0)
		{
			if (!next->right_node)
			{
				next->right_node = leaf;
				break ;
			}
			next = next->right_node;
		}
	}
	return (FUNC_SUC);
}

t_tree_node	*tree_search(t_tree_node *node, t_tree_node **parent, char *key)
{
	int			size;
	int			tmp;
	int			flag;

	size = ft_strlen(key);
	if (!parent)
		flag = FALSE;
	else
		flag = TRUE;
	while (node)
	{
		tmp = ft_strncmp(node->key, key, size + 1);
		if (tmp == 0)
			return (node);
		else
		{
			if (flag == TRUE)
				*parent = node;
			if (tmp < 0)
				node = node->left_node;
			if (tmp > 0)
				node = node->right_node;
		}
	}
	return (NULL);
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
		{
			node = node->right_node;
		}
		exchange_node_key_value(node->right_node, target);
		target = node->right_node;
		node->right_node = NULL;
	}
	else if (!target->right_node || !target->left_node)
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
	return (target);
}
