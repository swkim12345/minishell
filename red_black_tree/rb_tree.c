/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:04:25 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/15 20:20:23 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

int			rb_tree_restruct(t_tree_node *node)
{
	
}

int			rb_tree_recolor(t_tree_node *node)
{
	
}

int			rb_tree_rotate(t_tree_node *node)
{
	
}

t_tree_node	*rb_get_parent(t_tree_node *node)
{
	
}

t_tree_node	*rb_get_ancestor(t_tree_node *node)
{
	
}

t_tree_node	*rb_get_uncle(t_tree_node *node)
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
				next->left_node = leaf;
			next = next->left_node;
		}
		if (tmp > 0)
		{
			if (!next->right_node)
				next->right_node = leaf;
			next = next->right_node;
		}
	}
}

t_tree_node	*rb_tree_pop(t_tree_head *head, char *key)
{
	
}
