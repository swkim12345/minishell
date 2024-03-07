/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_binary_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:02:22 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/06 22:05:22 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	tree_recurv_traversal(t_tree_node *node, char **ret_str,
		int size, int quote_flag)
{
	t_tree_node	**stack;
	int			index;
	int			str_size;

	index = 0;
	str_size = 0;
	if (!node)
		return (FUNC_SUC);
	stack = (t_tree_node **)ft_calloc(sizeof(t_tree_node *), size);
	if (node)
	{
		while (node)
		{
			stack[index++] = node;
			node = node->right_node;
		}
		while (--index >= 0)
		{
			ret_str[str_size++] = key_value_to_str(stack[index], quote_flag);
			str_size += tree_recurv_traversal(stack[index]->left_node,
					&(ret_str[str_size]), size - str_size, quote_flag);
		}
	}
	free(stack);
	return (str_size);
}

static int	parse_envp(char *env, char **key, char **value)
{
	int			index;
	size_t		size;

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
	if (size != ft_strlen(env))
	{
		*value = ft_strdup(&env[index + 1]);
		env[index] = '=';
	}
	else
		*value = NULL;
	return (FUNC_SUC);
}

t_tree_head	*ft_push_node_to_tree(t_tree_head *head, char **envp,
		t_minishell *minishell)
{
	t_tree_node	*tmp;
	int			index;

	index = -1;
	(void)minishell;
	while (envp[++index])
	{
		tmp = init_tree_node();
		if (!tmp)
		{
			free_tree_delete(head);
			return (NULL);
		}
		if (parse_envp(envp[index], &tmp->key, &tmp->value) == FUNC_FAIL)
		{
			free_tree_delete(head);
			return (NULL);
		}
		tmp->index = index;
		head->size += 1;
		tree_insert(head, tmp);
		tmp = NULL;
	}
	return (head);
}
