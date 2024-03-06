/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:22:04 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/06 21:10:45 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static int	tree_insert_node(t_tree_node **next, t_tree_node *leaf, int size)
{
	if (size == 0)
	{
		free((*next)->value);
		if (!(*next)->value)
			(*next)->value = NULL;
		if (leaf->value)
			(*next)->value = ft_strdup(leaf->value);
		node_delete(leaf);
		return (FUNC_SUC);
	}
	else if (size < 0)
	{
		if (!(*next)->left_node)
		{
			(*next)->left_node = leaf;
			return (FUNC_SUC);
		}
		(*next) = (*next)->left_node;
	}
	else if (size > 0)
	{
		if (!(*next)->right_node)
		{
			(*next)->right_node = leaf;
			return (FUNC_SUC);
		}
		(*next) = (*next)->right_node;
	}
	return (FUNC_FAIL);
}

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
		if (tree_insert_node(&next, leaf, tmp) == FUNC_SUC)
			return (FUNC_SUC);
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
		if (flag == TRUE)
			*parent = node;
		if (tmp < 0)
			node = node->left_node;
		if (tmp > 0)
			node = node->right_node;
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
