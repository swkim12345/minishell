/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:03:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/22 20:30:47 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	ft_setenv(t_tree_head *head, char *key, char *value)
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

char	*ft_getenv(t_tree_head *head, char *key)
{
	t_tree_node	*tmp;

	tmp = tree_search(head->head, NULL, key);
	if (tmp)
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

t_tree_head	*ft_initenv(char **envp)
{
	t_tree_head	*head;
	t_tree_node	*tmp;
	int			index;

	head = (t_tree_head *)malloc(sizeof(t_tree_head));
	if (!head)
		return (NULL);
	head->head = NULL;
	head->size = 0;
	index = -1;
	while (envp[++index])
	{
		tmp = (t_tree_node *)malloc(sizeof(t_tree_node));
		ft_memset((void *)tmp, 0, sizeof(t_tree_node));
		if (parse_env(envp[index], &tmp->key, &tmp->value) == FUNC_FAIL)
		{
			tree_delete(head);
			return (NULL);
		}
		if (!tmp)
		{
			tree_delete(head);
			free(tmp);
			return (NULL);
		}
		tmp->index = index;
		head->size += 1;
		tree_insert(head, tmp);
		tmp = NULL;
	}
	return (head);
}

#include <stdio.h>
//int			ft_setexport(t_tree_head *head, char *key, char *value)
//{
//	t_tree_node	*tmp;

//	tmp = tree_search(head->head, NULL, key);
//	if (tmp)
//	{
//		free(tmp->value);
//		tmp->value = ft_strdup(value);
//		return (FUNC_SUC);
//	}
//	tmp = (t_tree_node *)malloc(sizeof(t_tree_node));
//	if (!tmp)
//		return (FUNC_FAIL);
//	tmp->key = ft_strdup(key);
//	tmp->value = ft_strdup(value);
//	tmp->index = head->size++;
//	tree_insert(head, tmp);
//	return (FUNC_SUC);
//}

//char		*ft_getexport(t_tree_head *head, char *key)
//{
//	t_tree_node	*tmp;

//	tmp = tree_search(head->head, NULL, key);
//	if (tmp)
//		return (tmp->value);
//	return (NULL);
//}

//int			ft_unsetexport(t_tree_head *head, char *key)
//{
//	t_tree_node	*tmp;

//	tmp = tree_pop(head->head, key);
//	if (tmp)
//	{
//		head->size--;
//		node_delete(tmp);
//		return (FUNC_SUC);
//	}
//	return (FUNC_FAIL);
//}
