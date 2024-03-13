/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:46:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/13 13:46:52 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	traverse_tmp_file(t_ast_node *node, t_minishell *minishell)
{
	t_redirection	*red;

	if (node->left_node)
		traverse_tmp_file(node->left_node, minishell);
	if (node->right_node)
		traverse_tmp_file(node->right_node, minishell);
	if (node->next_ast_node)
		traverse_tmp_file(node->next_ast_node, minishell);
	if (node->red)
	{
		red = node->red;
		while (red)
		{
			if (red->flag == DB_LT_SIGN)
			{
				red->str = eof_parser(red->str);
				node->index = minishell->tmp_file_counter + 1;
				if (heredoc_open_fd(red, minishell) == FUNC_FAIL)
					return ;
			}
			red = red->next;
		}	
	}
}

t_ast_node	*parser(char *str, t_minishell *minishell)
{
	t_ast_node	*ret;
	int			err;

	minishell->tmp_file_counter = 0;
	ret = init_ast_node(CMDNODE);
	ret->cmd_node->str = init_doub_char(&str, 1);
	err = recurv_parser(ret, minishell);
	traverse_tmp_file(ret, minishell);
	traverse_redirection(minishell);
	if (err == FUNC_FAIL)
	{
		free_ast_tree(ret);
		return (NULL);
	}
	return (ret);
}
