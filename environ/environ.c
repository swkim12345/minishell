/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:03:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/05 17:35:52 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	ft_setenv(t_tree_head *head, char *key, char *value)
{
	t_tree_node	*tmp;

	tmp = tree_search(head->head, NULL, key);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = NULL;
		if (value)
			tmp->value = ft_strdup(value);
		return (FUNC_SUC);
	}
	tmp = init_tree_node();
	if (!tmp)
		return (FUNC_FAIL);
	tmp->key = ft_strdup(key);
	if (!value)
		tmp->value = NULL;
	else if (value[0] == '\0')
		tmp->value = ft_strdup("\0");
	else
		tmp->value = ft_strdup(value);
	tmp->index = head->size++;
	tree_insert(head, tmp);
	return (FUNC_SUC);
}

char	*ft_getenv(t_tree_head *head, char *key)
{
	t_tree_node	*tmp;

	// if (!head)
	// {
		
	// 	tmp = getenv(key);
	// }
	// else
		tmp = tree_search(head->head, NULL, key);
	if (tmp && tmp->value)
		return (tmp->value);
	return (NULL);
}

int	ft_unsetenv(t_tree_head *head, char *key)
{
	t_tree_node	*tmp;

	tmp = tree_pop(head->head, key);
	if (tmp)
	{
		head->size--;
		node_delete(tmp);
		return (FUNC_SUC);
	}
	return (FUNC_FAIL);
}

t_tree_head	*ft_initenv(char **envp, t_minishell *minishell)
{
	t_tree_head	*head;

	head = (t_tree_head *)malloc(sizeof(t_tree_head));
	if (!head)
		return (NULL);
	ft_memset((void *)head, 0, sizeof(t_tree_head));
	return (ft_push_node_to_tree(head, envp, minishell));
}

char	**ft_charenv(t_tree_head *head, int quote_flag)
{
	char		**ret;

	ret = (char **)malloc(sizeof(char *) * (head->size + 1));
	if (!ret)
		return (NULL);
	ft_memset((void *)ret, 0, sizeof(char *) * (head->size + 1));
	ret[head->size] = NULL;
	tree_recurv_traversal(head->head, ret, head->size, quote_flag);
	return (ret);
}
