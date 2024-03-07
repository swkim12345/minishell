/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_recurv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:42:23 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/07 19:48:09 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	pipe_recurv_parser(t_ast_node *head, int str_end,
			int dup_str_start, t_minishell *minishell)
{
	char	*ptr;

	ptr = head->cmd_node->str[0];
	if (str_end <= 0)
	{
		head->err_flag = TRUE;
		return (syntax_err_message(ptr, dup_str_start, FUNC_FAIL, minishell));
	}
	if (split_node(str_end, dup_str_start, head, NEXTNODE) == FUNC_FAIL)
	{
		head->err_flag = TRUE;
		return (syntax_err_message("|", NOTDEFINED, FUNC_FAIL, minishell));
	}
	if (recurv_parser(head->next_ast_node, minishell) == FUNC_FAIL)
		return (FUNC_FAIL);
	if (recurv_parser(head, minishell) == FUNC_FAIL)
		return (FUNC_FAIL);
	return (FUNC_SUC);
}

static int	split_setflag_parser(t_ast_node *head, int str_end,
			int dup_str_start, t_minishell *minishell)
{
	char	*ptr;

	ptr = head->cmd_node->str[0];
	if (str_end <= 0)
	{
		head->err_flag = TRUE;
		return (syntax_err_message(ptr, dup_str_start,
				FUNC_FAIL, minishell));
	}
	if (ft_strncmp(&ptr[str_end + 1], "&&", ft_strlen("&&")) == 0)
		head->flag |= AND_FLAG;
	else if (ft_strncmp(&ptr[str_end + 1], "||", ft_strlen("||")) == 0)
		head->flag |= OR_FLAG;
	else
		head->flag |= NO_FLAG;
	return (FUNC_SUC);
}

static int	split_recurv_parser(t_ast_node *head, int str_end,
			int dup_str_start, t_minishell *minishell)
{
	if (split_setflag_parser(head, str_end,
			dup_str_start, minishell) == FUNC_FAIL)
		return (FUNC_FAIL);
	if (split_node(str_end, dup_str_start, head,
			LEFTNODE | RIGHTNODE) == FUNC_FAIL)
	{
		head->err_flag = TRUE;
		if (head->flag & AND_FLAG)
			return (syntax_err_message("&&", NOTDEFINED, FUNC_FAIL, minishell));
		if (head->flag & OR_FLAG)
			return (syntax_err_message("||", NOTDEFINED, FUNC_FAIL, minishell));
	}
	free_cmd_node(&(head->cmd_node));
	if (recurv_parser(head->left_node, minishell) == FUNC_FAIL)
		return (FUNC_FAIL);
	if (recurv_parser(head->right_node, minishell) == FUNC_FAIL)
		return (FUNC_FAIL);
	return (FUNC_SUC);
}

static int	recurv_parser_sub(t_ast_node *head, t_minishell *minishell,
			char *ptr, int index)
{
	int	tmp;

	tmp = 0;
	if (ptr[index] == '(')
	{
		tmp = bracket_finder(&ptr[index]);
		if (tmp == NOTDEFINED)
		{
			head->err_flag = TRUE;
			return (syntax_err_message(&ptr[index], index + 1, -2, minishell));
		}
		index += tmp;
	}
	if (ptr[index] == '\"' || ptr[index] == '\'')
	{
		tmp = finder(&ptr[index + 1], ptr[index]);
		if (tmp == NOTDEFINED)
		{
			head->err_flag = TRUE;
			return (syntax_err_message(ptr, index + 1, -2, minishell));
		}
		index += tmp + 1;
	}
	return (index);
}

int	recurv_parser(t_ast_node *head, t_minishell *minishell)
{
	int			index;
	char		*ptr;

	index = -1;
	ptr = head->cmd_node->str[0];
	while (ptr[++index])
	{
		index += skip_space(&ptr[index]);
		if (ptr[index] == '\0')
			break ;
		if (ptr[index] == '|' && ptr[index + 1] == '|')
			return (split_recurv_parser(head, index - 1, index + 2, minishell));
		if (ptr[index] == '&' && ptr[index + 1] == '&')
			return (split_recurv_parser(head, index - 1, index + 2, minishell));
		if (ptr[index] == '|')
			return (pipe_recurv_parser(head, index - 1, index + 1, minishell));
		index = recurv_parser_sub(head, minishell, ptr, index);
		if (index == -2)
			return (FUNC_FAIL);
	}
	if (lexar(head, minishell) == FUNC_FAIL)
		return (FUNC_FAIL);
	return (FUNC_SUC);
}
