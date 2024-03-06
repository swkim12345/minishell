/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:22:04 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/06 21:51:37 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static int	tree_insert_not_node(t_tree_node **next,
		t_tree_node *leaf, int size)
{
	if (size < 0)
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

static int	tree_insert_node(t_tree_node **next, t_tree_node *leaf, int size)
{
	if (size == 0)
	{
		if (!(*next)->value)
			(*next)->value = NULL;
		if (leaf->value)
		{
			free((*next)->value);
			(*next)->value = ft_strdup(leaf->value);
		}
		node_delete(leaf);
		return (FUNC_SUC);
	}
	else
		return (tree_insert_not_node(next, leaf, size));
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
