/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:17:12 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/09 11:49:34 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexar.h"

static int	subshell_parser_bracket(t_ast_node *head, int index,
		int flag, t_minishell *minishell)
{
	char	*ptr;
	int		tmp;

	ptr = head->cmd_node->str[0];
	tmp = bracket_finder(&ptr[index]);
	if (tmp + index == NOTDEFINED || tmp == index + 1)
	{
		head->err_flag = TRUE;
		syntax_err_message(&ptr[index], tmp, SYN_ERR, minishell);
		return (NOTDEFINED);
	}
	if (flag & STRING_FLAG)
	{
		head->err_flag = TRUE;
		syntax_err_message(&ptr[index + 1], tmp - 1,
			SYN_ERR, minishell);
		return (NOTDEFINED);
	}
	ptr[tmp + index] = ' ';
	ptr[index] = ' ';
	index += tmp;
	return (index);
}

int	subshell_lexar(t_ast_node *head, int index,
		int flag, t_minishell *minishell)
{
	char	*ptr;
	int		tmp;

	index = subshell_parser_bracket(head, index, flag, minishell);
	if (index == NOTDEFINED)
		return (FUNC_FAIL);
	ptr = head->cmd_node->str[0];
	while (TRUE)
	{
		index += skip_space(&ptr[index]);
		if (ptr[index] == '\0' || ptr[index] == '<' || ptr[index] == '>')
		{
			head->flag |= BRACKET_FLAG;
			return (index);
		}
		else
		{
			head->err_flag = TRUE;
			tmp = err_token_finder(ptr, index);
			syntax_err_message(&ptr[index], tmp - index,
				SYN_ERR, minishell);
			return (FUNC_FAIL);
		}
	}
	return (index);
}
