/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_binary_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:02:22 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/26 12:02:40 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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
			str_size += tree_recurv_traversal(stack[index]->left_node,
						&(ret_str[str_size]), size - str_size);
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
