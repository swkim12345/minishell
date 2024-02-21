/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:03:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/21 16:40:09 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

char		*ft_getenv(t_tree_head *head, char *key)
{
	t_tree_node	*tmp;

	tmp = tree_search(head->head, NULL, key);
	if (tmp)
		return (tmp->value);
	return (NULL);
}

char		*ft_getexport(t_tree_head *head, char *key)
{
	t_tree_node	*tmp;

	tmp = tree_search(head->head, NULL, key);
	if (tmp)
		return (tmp->value);
	return (NULL);
}

int			ft_setenv(t_tree_head *head, char *key, char *value)
{
	t_tree_node	*tmp;

	tmp = tree_search(head->head, NULL, key);
	if (tmp)
	{
		printf("key : %s, value : %s\n", tmp->key, tmp->value);
		free(tmp->value);
		tmp->value = ft_strdup(value);
		return (FUNC_SUC);
	}
	tmp = (t_tree_node *)malloc(sizeof(t_tree_node));
	if (!tmp)
		return (FUNC_FAIL);
	tmp->key = ft_strdup(key);
	tmp->value = ft_strdup(value);
	tmp->index = head->size++;
	printf("key : %s, value : %s\n", tmp->key, tmp->value);
	tree_insert(head, tmp);
	return (FUNC_SUC);
}

int			ft_setexport(t_tree_head *head, char *key, char *value)
{
	t_tree_node	*tmp;

	tmp = tree_search(head->head, NULL, key);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
		return (FUNC_SUC);
	}
	tmp = (t_tree_node *)malloc(sizeof(t_tree_node));
	if (!tmp)
		return (FUNC_FAIL);
	tmp->key = ft_strdup(key);
	tmp->value = ft_strdup(value);
	tmp->index = head->size++;
	tree_insert(head, tmp);
	return (FUNC_SUC);
}

int			ft_unsetexport(t_tree_head *head, char *key)
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

int			ft_unsetenv(t_tree_head *head, char *key)
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

t_tree_head	*ft_dup_tree(t_tree_head *head)
{
	t_tree_head	*ret;
	t_tree_node	*tmp;
	t_tree_node	*new;

	ret = (t_tree_head *)malloc(sizeof(t_tree_head));
	if (!ret)
		return (NULL);
	ret->head = NULL;
	ret->size = head->size;
	tmp = head->head;
	while (tmp)
	{
		new = (t_tree_node *)malloc(sizeof(t_tree_node));
		if (!new)
		{
			recur_tree_delete(ret->head);
			free(ret);
			return (NULL);
		}
		new->key = ft_strdup(tmp->key);
		new->value = ft_strdup(tmp->value);
		new->index = tmp->index;
		tree_insert(ret, new);
		tmp = tmp->right_node;
	}
	return (ret);
}

t_tree_head	*ft_initenv(t_tree_head *head, char **envp)
{
	t_tree_head	*ret;
	t_tree_node	*tmp;
	char		*key;
	char		*value;
	int			index;

	ret = (t_tree_head *)malloc(sizeof(t_tree_head));
	if (!ret)
		return (NULL);
	ret->head = NULL;
	ret->size = 0;
	index = -1;
	while (envp[++index])
	{
		parse_env(envp[index], &key, &value);
		tmp = (t_tree_node *)malloc(sizeof(t_tree_node));
		if (!tmp)
		{
			recur_tree_delete(ret->head);
			free(ret);
			return (NULL);
		}
		tmp->key = ft_strdup(key);
		tmp->value = ft_strdup(value);
		tmp->index = head->size++;
		tree_insert(ret, tmp);
	}
	return (ret);
}
