/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_tree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:22:04 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/16 22:11:47 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_tree.h"

int			tree_insert(t_tree_head *head, t_tree_node *leaf)
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
		tmp = ft_strncmp(next->key, leaf->key, tmp + 1);
		if (tmp == 0)
			return (NOTDEFINED);
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

	size = ft_strlen(key);
	*parent = NULL;
	while (node)
	{
		tmp = ft_strncmp(node->key, key, size + 1);
		if (tmp == 0)
			return (node);
		else
		{
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
	else if(!target->right_node || !target->left_node)
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
	while (str[++index]) //균형 잡게 넣어야 하는데... 이거...
	{
		node = (t_tree_node *)malloc(sizeof(t_tree_node));
		ft_memset((void *)node, 0, sizeof(t_tree_node));
		parse_env(str[index], &node->key, &node->value);
		tree_insert(ret, node);
		ret->size += 1;
	}
	return (ret);
}

int			tree_recurv_traversal(t_tree_node *head, t_tree_node **ordered, int size)
{
	t_tree_node	**stack;
	t_tree_node	*tmp;
	int			index;
	int			ordered_size;

	index = 0;
	ordered_size = 0;
	stack = (t_tree_node **)malloc(sizeof(t_tree_node *) * size);
	tmp = head;
	if (!head)
		return (FUNC_SUC);
	if (tmp)
	{
		while (tmp)
		{
			stack[index++] = tmp;
			tmp = tmp->right_node;
		}
		while (--index >= 0)
		{
			ordered[ordered_size] = stack[index];
			printf("in recurv key : %s, value : %s\n", ordered[ordered_size]->key, ordered[ordered_size]->value);
			ordered_size += 1;
			ordered_size += tree_recurv_traversal(stack[index]->left_node, &(ordered[ordered_size]), size);
		}
	}
	free(stack);
	return (ordered_size);
}

char		**tree_to_char(t_tree_head *head)
{
	int			index;
	char		*tmp;
	char		**ret;
	t_tree_node	**ordered;
	
	index = 0;
	ret = (char **)malloc(sizeof(char *) * (head->size + 1));
	ordered = (t_tree_node **)malloc(sizeof(t_tree_node *) * (head->size + 1));
	tree_recurv_traversal(head->head, ordered, head->size);
	while (index < head->size)
	{
		tmp = ft_strjoin(ordered[index]->key, "=");
		ret[index] = ft_strjoin(tmp, ordered[index]->value);
		free(tmp);
		printf("index : %d, size : %ld\n", index, head->size);
		printf("key value: %s\n", ret[index]);
		index++;
	}
	free(ordered);
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_tree_head	*head;
	t_tree_node	*tmp;
	char		**ret;
	char		*key;
	char		*value;
	int			index;

	index = -1;
	while (envp[++index])
	{
		printf("%d : %s\n", index, envp[index]);
	}
	head = char_to_tree(envp);
	printf("head size : %ld\n", head->size);
	index = -1;
	while (envp[++index])
	{
		parse_env(envp[index], &key, &value);
		printf("key : %s, node value : %s, real value: %s\n",key, tree_search(head->head, &tmp, key)->value, value);
	}
	printf("key : %s, node value : %s, real value: %s\n", "_", tree_search(head->head, &tmp, "_")->value, "velu");
	ret = tree_to_char(head);
	index = -1;
	while (ret[++index])
	{
		printf("%d : %s\n", index, ret[index]);
	}
	return (0);
}
