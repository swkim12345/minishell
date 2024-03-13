/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:46:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/13 10:59:03 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"




t_ast_node	*parser(char *str, t_minishell *minishell)
{
	t_ast_node	*ret;
	int			err;

	minishell->tmp_file_counter = 0;
	ret = init_ast_node(CMDNODE);
	ret->cmd_node->str = init_doub_char(&str, 1);
	err = recurv_parser(ret, minishell);
	traverse_redirection(minishell);
	if (err == FUNC_FAIL)
	{
		free_ast_tree(ret);
		return (NULL);
	}
	return (ret);
}
