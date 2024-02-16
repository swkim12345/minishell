/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:04:25 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/16 14:12:37 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

t_tree_node	*rb_get_ancestor(t_tree_node *node)
{
	t_tree_node	*ret;

	ret = node->parent_node;
	if (!ret)
		return (NULL);
	return (ret->parent_node);
}

t_tree_node	*rb_get_uncle(t_tree_node *node)
{
	t_tree_node	*ret;

	ret = node->parent_node;
	if (!ret || !ret->parent_node)
		return (NULL);
	if (ret->parent_node->left_node == ret)
		return (ret->parent_node->right_node);
	else
		return (ret->parent_node->left_node);
}

int			rb_tree_restruct(t_tree_node *node)
{
	
}

int			rb_tree_recolor(t_tree_node *node)
{
	
}

int			rb_tree_left_rotate(t_tree_node *node)
{
	
}

int			rb_tree_right_rotate(t_tree_node *node)
{
	
}

int			rb_tree_insert(t_tree_head *head, t_tree_node *leaf)
{
	t_tree_node	*next;
	int			tmp;
	
	next = head->head;
	if (next)
	{
		head->head = leaf;
		return (0);
	}
	while (next)
	{
		tmp = ft_strlen(leaf->key);
		tmp = ft_strncmp(next->key, leaf->key, tmp);
		if (tmp == 0)
			return (NOTDEFINED);
		if (tmp < 0)
		{
			if (!next->left_node)
			{
				next->left_node = leaf;
				leaf->parent_node = next;
			}
			next = next->left_node;
		}
		if (tmp > 0)
		{
			if (!next->right_node)
			{
				next->right_node = leaf;
				leaf->parent_node = next;
			}
			next = next->right_node;
		}
	}
	head->size += 1;
	if (leaf->parent_node && leaf->color == leaf->parent_node->color) //red
	{	
		if (rb_get_uncle(leaf)->color != leaf->color) //uncle == leaf
		{
			if (leaf->parent_node->parent_node
		}
		rb_get_uncle(leaf)->color = BLACK;
		leaf->parent_node->color = BLACK;
		rb_get_ancestor(leaf)->color = RED;
	}

	return (0);
}

t_tree_node	*rb_tree_search(t_tree_head *head, char *key)
{
	t_tree_node	*next;
	int			tmp;

	next = head->head;
	while (next)
	{
		tmp = ft_strlen(next->key);
		tmp = ft_strncmp(next->key, key, tmp);
		if (tmp < 0)
			next = next->left_node;
		else if (tmp > 0)
			next = next->right_node;
		else
			return (next);
	}
	return (NULL);
}

t_tree_node	*rb_tree_pop(t_tree_head *head, char *key)
{
	t_tree_node	*target;

	target = rb_tree_search(head, key);
	if (!target)
		return (NULL);
	if (target)
	
	return (target);
}
