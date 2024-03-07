/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:36:45 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/07 19:16:58 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**init_doub_char(char **input, int size)
{
	char	**ret;
	int		i;

	i = -1;
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	while (++i < size && input[i])
		ret[i] = ft_strdup(input[i]);
	ret[i] = NULL;
	return (ret);
}

void	free_redirection_node(t_redirection *red)
{
	t_redirection	*tmp;

	if (red == NULL)
		return ;
	while (red)
	{
		tmp = red->next;
		free(red->str);
		free(red);
		red = NULL;
		red = tmp;
	}
}

void	free_cmd_node(t_cmd_node **node)
{
	if (*node == NULL)
		return ;
	if ((*node)->str)
		free_2d_str((*node)->str);
	free(*node);
	*node = NULL;
}

void	free_ast_tree(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->next_ast_node)
		free_ast_tree(node->next_ast_node);
	if (node->left_node)
		free_ast_tree(node->left_node);
	if (node->right_node)
		free_ast_tree(node->right_node);
	if (node->cmd_node)
		free_cmd_node(&(node->cmd_node));
	if (node->red)
		free_redirection_node(node->red);
	free(node);
	node = NULL;
	return ;
}

t_ast_node	*init_ast_node(int child_node)
{
	t_ast_node	*ret;
	t_cmd_node	*node;

	ret = (t_ast_node *)ft_calloc(sizeof(t_ast_node), 1);
	if (CMDNODE & child_node)
	{
		node = (t_cmd_node *)ft_calloc(sizeof(t_cmd_node), 1);
		ret->cmd_node = node;
	}
	if (LEFTNODE & child_node)
		ret->left_node = init_ast_node(CMDNODE);
	if (RIGHTNODE & child_node)
		ret->right_node = init_ast_node(CMDNODE);
	return (ret);
}
