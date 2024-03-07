/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:22:56 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/07 21:23:58 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	lexar(t_ast_node *node, t_minishell *minishell)
{
	char		*ptr;
	char		**cmd_str;
	int			index;
	int			str_flag;
	int			tmp;

	index = -1;
	str_flag = FALSE;
	ptr = node->cmd_node->str[0];
	while (ptr[++index])
	{
		index += skip_space(&ptr[index]);
		if (ptr[index] == '\0')
			break ;
		if (ptr[index] == '\"' || ptr[index] == '\'')
		{
			tmp = finder(&ptr[index + 1], ptr[index]);
			if (tmp == NOTDEFINED)
				return (syntax_err_message(ptr, NOTDEFINED, FUNC_FAIL, minishell));
			index += tmp + 1;
			continue ;
		}
		if (ptr[index] == '<' || ptr[index] == '>')
		{
			index = lexar_redirect(node, minishell, index);
			if (index == -2)
				return (FUNC_FAIL);
			continue ;
		}
		if (ptr[index] == '(')
		{
			tmp = subshell_recurv_parser(node, index, str_flag, minishell);
			if (tmp == FUNC_FAIL)
				return (FUNC_FAIL);
			str_flag |= BRACKET_FLAG;
			index = tmp - 1; //error?
			continue ;
		}
		str_flag |= STRING_FLAG;
	}
	if (str_flag & BRACKET_FLAG)
	{
		tmp = recurv_parser(node, minishell);
		node->flag |= BRACKET_FLAG;
		return (tmp);
	}
	cmd_str = string_parser(ptr, minishell);
	free_2d_str(node->cmd_node->str);
	node->cmd_node->str = cmd_str;
	return (FUNC_SUC);
}
