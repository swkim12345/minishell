/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_tree_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:52:19 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/16 19:08:30 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_tree.h"

int			parse_env(char *env, char **key, char **value) //=기준으로 파싱
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
	if (!key || !value)
		return (NOTDEFINED);
	*key = ft_strdup(env);
	*value = ft_strdup(&env[index + 1]);
	return (0);
}

void		node_delete(t_tree_node *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

void	recur_tree_delete(t_tree_node *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	recur_tree_delete(node->left_node);
	recur_tree_delete(node->right_node);
	free(node);
}

void		exchange_node_key_value(t_tree_node *n, t_tree_node *t)
{
	char	*key;
	char	*value;

	key = n->key;
	value = n->value;
	n->key = t->key;
	n->value = t->value;
	t->key = key;
	t->value = value;
}
