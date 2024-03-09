/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:39:19 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/09 13:21:36 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	find_split_node(t_ast_node *node, int new_node_flag,
			t_ast_node **old_node, t_ast_node **new_node)
{
	if (new_node_flag & LEFTNODE)
	{
		node->left_node = init_ast_node(CMDNODE);
		*old_node = node->left_node;
	}
	if (new_node_flag & RIGHTNODE)
	{
		node->right_node = init_ast_node(CMDNODE);
		*new_node = node->right_node;
	}
	if (new_node_flag & NEXTNODE)
	{
		node->next_ast_node = init_ast_node(CMDNODE);
		*new_node = node->next_ast_node;
	}
}

int	split_node(int end, int new_start, t_ast_node *node, int new_node_flag)
{
	char		*ptr;
	char		*tmp;
	t_ast_node	*old_node;
	t_ast_node	*new_node;

	old_node = node;
	new_node = NULL;
	ptr = ft_strdup(node->cmd_node->str[0]);
	tmp = ft_substr(ptr, 0, end + 1);
	find_split_node(node, new_node_flag, &old_node, &new_node);
	free_2d_str(node->cmd_node->str);
	node->cmd_node->str = NULL;
	old_node->cmd_node->str = init_doub_char(&tmp, 1);
	free(tmp);
	tmp = ft_substr(ptr, new_start, ft_strlen(&ptr[new_start]));
	new_node->cmd_node->str = init_doub_char(&tmp, 1);
	free(tmp);
	free(ptr);
	tmp = new_node->cmd_node->str[0];
	tmp += skip_space(tmp);
	if (*tmp == '\0')
		return (FUNC_FAIL);
	return (FUNC_SUC);
}
