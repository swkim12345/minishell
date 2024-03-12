/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:22:56 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/12 21:30:28 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexar.h"

static int	lexar_ret(t_ast_node *node, t_minishell *minishell,
			char *ptr, int str_flag)
{
	char	**cmd_str;
	int		tmp;

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

static int	lexar_token_check(t_ast_node *node, t_minishell *minishell,
			int index)
{
	char	*ptr;
	int		tmp;

	ptr = node->cmd_node->str[0];
	if (ptr[index] == '\"' || ptr[index] == '\'')
	{
		tmp = finder(&ptr[index + 1], ptr[index]);
		if (tmp == NOTDEFINED)
		{
			node->err_flag = TRUE;
			syntax_err_message(ptr, NOTDEFINED, FUNC_FAIL, minishell);
			return (INDEX_ERR);
		}
		index += tmp + 1;
	}
	else if (ptr[index] == '<' || ptr[index] == '>')
	{
		index = lexar_redirect(node, minishell, index);
		if (index == INDEX_ERR)
			return (INDEX_ERR);
	}
	return (index);
}

static int	lexar_bracket(t_ast_node *node, t_minishell *minishell,
			int index, int *str_flag)
{
	int		tmp;
	char	*ptr;

	ptr = node->cmd_node->str[0];
	if (ptr[index] == '(')
	{
		tmp = subshell_lexar(node, index, *str_flag, minishell);
		if (tmp == FUNC_FAIL)
			return (INDEX_ERR);
		*str_flag |= BRACKET_FLAG;
		index = tmp - 1;
	}
	else
		*str_flag |= STRING_FLAG;
	if (ptr[index] == ')')
	{
		syntax_err_message(&ptr[index], 1, SYN_ERR, minishell);
		return (INDEX_ERR);
	}
	return (index);
}

int	lexar(t_ast_node *node, t_minishell *minishell)
{
	char		*ptr;
	int			index;
	int			str_flag;

	index = -1;
	str_flag = FALSE;
	ptr = node->cmd_node->str[0];
	while (ptr[++index])
	{
		index += skip_space(&ptr[index]);
		if (ptr[index] == '\0')
			break ;
		index = lexar_token_check(node, minishell, index);
		if (index == INDEX_ERR)
			return (FUNC_FAIL);
		else
		{
			index = lexar_bracket(node, minishell, index, &str_flag);
			if (index == INDEX_ERR)
				return (FUNC_FAIL);
		}
	}
	return (lexar_ret(node, minishell, ptr, str_flag));
}
