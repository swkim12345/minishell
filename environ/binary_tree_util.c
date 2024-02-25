/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:52:19 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/25 19:22:24 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	parse_env(char *env, char **key, char **value)
{
	int		index;
	int		size;

	index = -1;
	size = ft_strlen(env);
	while (env[++index])
	{
		if (env[index] == '=')
		{
			if (index == 0)
				return (FUNC_FAIL);
			env[index] = '\0';
			break ;
		}
	}
	*key = ft_strdup(env);
	if (ft_strlen(env) != (size_t)size)
	{
		if (env[index + 1] == '\0')
		{
			*value = (char *)malloc(sizeof(char) * 1);
			*value[0] = '\0';
		}
		else
			*value = ft_strdup(&env[index + 1]);
		env[index] = '=';
	}
	else
		*value = NULL;
	return (FUNC_SUC);
}

t_tree_node	*init_tree_node(void)
{
	t_tree_node	*node;

	node = (t_tree_node *)malloc(sizeof(t_tree_node));
	if (!node)
		return (NULL);
	ft_memset((void *)node, 0, sizeof(t_tree_node));
	return (node);
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

void	free_tree_delete(t_tree_head *head)
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
