/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:17:12 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/07 20:18:29 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	subshell_recurv_parser(t_ast_node *head, int index,
		int flag, t_minishell *minishell)
{
	char	*ptr;
	int		tmp;

	ptr = head->cmd_node->str[0];
	tmp = bracket_finder(&ptr[index]);
	if (tmp + index == NOTDEFINED || tmp == index + 1)
	{
		head->err_flag = TRUE;
		return (syntax_err_message(&ptr[index], tmp, FUNC_FAIL, minishell));
	}
	if (flag & STRING_FLAG)
	{
		head->err_flag = TRUE;
		return (syntax_err_message(&ptr[index + 1], tmp - 1, FUNC_FAIL, minishell));
	}
	ptr[tmp + index] = ' ';
	ptr[index] = ' ';
	index += tmp;
	tmp = index;
	while (TRUE)
	{
		tmp += skip_space(&ptr[tmp]);
		if (ptr[tmp] == '\0' || ptr[tmp] == '<' || ptr[tmp] == '>')
		{
			head->flag |= BRACKET_FLAG;
			return (tmp);
		}
		else if (ptr[tmp] == '(')
			return (syntax_err_message(&ptr[tmp], tmp + 1, FUNC_FAIL, minishell));
		else
		{
			head->err_flag = TRUE;
			return (syntax_err_message(&ptr[tmp], NOTDEFINED, FUNC_FAIL, minishell)); //adhoc
		}
	}
	return (tmp);
}
