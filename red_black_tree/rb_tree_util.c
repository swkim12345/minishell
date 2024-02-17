/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:27:53 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/16 14:25:08 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

int			parse_env(char *env, char *key, char *value) //=기준으로 파싱
{
	int	index;
	
	index = -1;
	while (env[++index])
	{
		if (env[index] == '=')
		{
			env[index] = '\0';
			break ;
		}
	}
	if (!env[index] || !key || !value)
		return (NOTDEFINED);
	key = ft_strdup(env);
	value = ft_strdup(&env[index + 1]);
	return (0);
}

static void	recur_rb_tree_delete(t_tree_node *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	recur_rb_tree_delete(node->left_node);
	recur_rb_tree_delete(node->right_node);
}

void		rb_tree_delete(t_tree_head *head)
{
	if (!head)
		return ;
	recur_rb_tree_delete(head->head);
}
