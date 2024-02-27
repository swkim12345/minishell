/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:36:45 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/27 17:16:33 by sunghwki         ###   ########.fr       */
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

	while (red)
	{
		tmp = red->next;
		free_2d_str(&red->str);
		free(red);
		red = tmp;
	}
}

void	free_cmd_node(t_cmd_node *node)
{
	int			i;

	i = -1;
	if (node == NULL)
		return ;
	if (node->cmd_name)
		free(node->cmd_name);
	if (node->str)
		free_2d_str(node->str);
	free(node);
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
		free_cmd_node(node->cmd_node);
	if (node->red)
		free_redirection_node(node->red);
	if (node->str)
		free(node->str);
	free(node);
	node = NULL;
	return ;
}
