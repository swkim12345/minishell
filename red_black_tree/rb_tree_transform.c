/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_transform.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:51:25 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/16 12:32:47 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

char		**rb_tree_to_char(t_tree_node *head)
{
	
}

t_tree_head	*char_to_rb_tree(char **str)
{
	int	index;
	t_tree_head	*ret;
	t_tree_node	*node;
	
	index = -1;
	ret = (t_tree_head *)malloc(sizeof(t_tree_head));
	while (str[++index])
	{
		node = (t_tree_node *)malloc(sizeof(t_tree_node));
		ft_memset((void *)node, 0, sizeof(t_tree_node));
		node->color = RED;
		parse_env(str[index], node->key, node->value);
		rb_tree_insert(ret, node);
	}
	return (ret);
}
