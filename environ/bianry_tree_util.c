/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bianry_tree_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:52:19 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/19 12:36:41 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int			parse_env(char *env, char **key, char **value)
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
	//"", '' 처리 필요
	return (FUNC_SUC);
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
