/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:22:04 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/25 17:07:56 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	tree_insert(t_tree_head *head, t_tree_node *leaf)
{
	t_tree_node	*next;
	int			tmp;

	next = head->head;
	if (!next)
	{
		head->head = leaf;
		return (FUNC_SUC);
	}
	while (next)
	{
		tmp = ft_strlen(leaf->key);
		//printf("tmp : %d, leaf key: %s\n", tmp, leaf->key);
		tmp = ft_strncmp(next->key, leaf->key, tmp + 1);
		if (tmp == 0)
		{
			next->value = leaf->value;
			node_delete(leaf);
			return (FUNC_SUC);
		}
		if (tmp < 0)
		{
			if (!next->left_node)
			{
				next->left_node = leaf;
				break ;
			}
			next = next->left_node;
		}
		if (tmp > 0)
		{
			if (!next->right_node)
			{
				next->right_node = leaf;
				break ;
			}
			next = next->right_node;
		}
	}
	return (FUNC_SUC);
}

t_tree_node	*tree_search(t_tree_node *node, t_tree_node **parent, char *key)
{
	int			size;
	int			tmp;
	int			flag;

	size = ft_strlen(key);
	if (!parent)
		flag = FALSE;
	else
		flag = TRUE;
	while (node)
	{
		tmp = ft_strncmp(node->key, key, size + 1);
		if (tmp == 0)
			return (node);
		else
		{
			if (flag == TRUE)
				*parent = node;
			if (tmp < 0)
				node = node->left_node;
			if (tmp > 0)
				node = node->right_node;
		}
	}
	return (NULL);
}

t_tree_node	*tree_pop(t_tree_node *head, char *key)
{
	t_tree_node	*parent;
	t_tree_node	*target;
	t_tree_node	*node;

	target = tree_search(head, &parent, key);
	if (!target || !parent)
		return (target);
	if (target->left_node && target->right_node)
	{
		node = target->left_node;
		if (!node->right_node)
		{
			exchange_node_key_value(node, target);
			target->left_node = NULL;
			return (node);
		}
		while (node->right_node->right_node)
		{
			node = node->right_node;
		}
		exchange_node_key_value(node->right_node, target);
		target = node->right_node;
		node->right_node = NULL;
	}
	else if (!target->right_node || !target->left_node)
	{
		if (target->right_node)
			node = target->right_node;
		else
			node = target->left_node;
		if (parent->right_node == target)
			parent->right_node = node;
		else
			parent->left_node = node;
	}
	else
	{
		if (parent->right_node == target)
			parent->right_node = NULL;
		else
			parent->left_node = NULL;
	}
	return (target);
}

t_tree_head	*char_to_tree(char **str)
{
	int			index;
	t_tree_node	*node;
	t_tree_head	*ret;

	index = -1;
	ret = (t_tree_head *)malloc(sizeof(t_tree_head));
	ret->head = 0;
	ret->size = 0;
	while (str[++index])
	{
		node = (t_tree_node *)malloc(sizeof(t_tree_node));
		ft_memset((void *)node, 0, sizeof(t_tree_node));
		parse_env(str[index], &node->key, &node->value);
		tree_insert(ret, node);
		ret->size += 1;
	}
	return (ret);
}

char	*key_value_to_str(t_tree_node *node)
{
	char	*ret;
	char	*tmp;

	if (node->value == NULL)
		ret = ft_strdup(node->key);
	else if (node->value[0] == '\0')
		ret = ft_strjoin(node->key, "=\"\"");
	else
	{
		tmp = ft_strjoin(node->key, "=\"");
		ret = ft_strjoin(tmp, node->value);
		free(tmp);
		tmp = ft_strdup(ret);
		free(ret);
		ret = ft_strjoin(tmp, "\"");
		free(tmp);
	}
	return (ret);
}

static int	tree_recurv_traversal(t_tree_node *head, char **ret_str, int size)
{
	t_tree_node	**stack;
	t_tree_node	*tmp;
	int			index;
	int			str_size;

	index = 0;
	str_size = 0;
	tmp = head;
	if (!head)
		return (FUNC_SUC);
	stack = (t_tree_node **)malloc(sizeof(t_tree_node *) * size);
	if (tmp)
	{
		while (tmp)
		{
			stack[index++] = tmp;
			tmp = tmp->right_node;
		}
		while (--index >= 0)
		{
			ret_str[str_size] = key_value_to_str(stack[index]);
			str_size += 1;
			str_size += tree_recurv_traversal(stack[index]->left_node, &(ret_str[str_size]), size - str_size);
		}
	}
	free(stack);
	stack = NULL;
	return (str_size);
}

char	**tree_to_char(t_tree_head *head)
{
	char		**ret;

	ret = (char **)malloc(sizeof(char *) * (head->size + 1));
	ft_memset((void *)ret, 0, sizeof(char *) * (head->size + 1));
	tree_recurv_traversal(head->head, ret, head->size);
	return (ret);
}
