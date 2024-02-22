/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:52:19 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/22 18:40:35 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	parse_env(char *env, char **key, char **value)
{
	int		index;
	char	*tmp;

	index = -1;
	tmp = ft_strdup(env);
	while (tmp[++index])
	{
		if (tmp[index] == '=')
		{
			if (index == 0)
			{
				free(tmp);
				return (FUNC_FAIL);
			}
			tmp[index] = '\0';
			break ;
		}
	}
	*key = ft_strdup(tmp);
	if (!tmp[index] && tmp[index - 1] != '=')
		*value = ft_strdup("");
	else if (!tmp[index])
		*value = NULL;
	else
		*value = ft_strdup(&tmp[index + 1]);
	*value = ft_strdup(&tmp[index + 1]);
	free(tmp);
	return (FUNC_SUC);
}

void	node_delete(t_tree_node *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

static void	recur_tree_delete(t_tree_node *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	recur_tree_delete(node->left_node);
	recur_tree_delete(node->right_node);
	free(node);
}

void	tree_delete(t_tree_head *head)
{
	if (!head)
		return ;
	recur_tree_delete(head->head);
	free(head);
}

void	exchange_node_key_value(t_tree_node *n, t_tree_node *t)
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
