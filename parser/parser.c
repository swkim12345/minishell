/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:46:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/27 15:14:58 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	bracket_parser(char *str, int index, int str_flag, t_minishell *minishell)
{
	char	*ptr;
	int		ret;

	ptr = &str[index];
	if (*ptr == '(')
	{
		if (str_flag == TRUE)
			return (syntax_err_message(ptr, index, -1, minishell));
		else
		{
			ret = bracket_finder(ptr);
			if (ret == NOTDEFINED)
				return (syntax_err_message(ptr, index, -1, minishell));
			else
				return (ret);
		}
	}
	return (index);
}

static int	split_recurv_parser(t_ast_node *head, int str_end,
			int dup_str_start, t_minishell *minishell)
{
	char	*ptr;
	char	*tmp;
	int		size;

	ptr = head->cmd_node->str[0];
	if (str_end <= 0)
		return (syntax_err_message(ptr, dup_str_start, -1, minishell));
	size = ft_strlen(ptr);
	head->str = dup_str(ptr, 0, str_end);
	head->left_node = init_ast_node(CMDNODE);
	head->right_node = init_ast_node(CMDNODE);
	tmp = dup_str(ptr, 0, str_end);
	head->left_node->cmd_node->str = \
		init_doub_char(&tmp, 1);
	free(tmp);
	tmp = dup_str(ptr, dup_str_start, size);
	head->right_node->cmd_node->str = \
		init_doub_char(&tmp, 1);
	free(tmp);
	if (recurv_parser(head->left_node, minishell) == FUNC_FAIL)
		return (FUNC_FAIL);
	if (recurv_parser(head->right_node, minishell) == FUNC_FAIL)
		return (FUNC_FAIL);
	return (FUNC_SUC);
}

int	recurv_parser(t_ast_node *head, t_minishell *minishell)
{
	int			index;
	int			tmp;
	char		*ptr;

	index = -1;
	ptr = head->cmd_node->str[0];
	while (ptr[++index])
	{	
		index += skip_space(&ptr[index]);
		if (ptr[index] == '\"' || ptr[index] == '\'')
		{
			tmp = finder(&ptr[index + 1], ptr[index]);
			if (tmp == NOTDEFINED)
				return (syntax_err_message(ptr, index, -1, minishell));
			index += tmp;
			continue ;
		}
		if (ptr[index] == '(')
		{
			tmp = bracket_finder(&ptr[index + 1]);
			if (tmp == NOTDEFINED)
				return (tmp);
			index += tmp;
			continue ;
		}
		if (ptr[index] == '|' && ptr[index + 1] == '|')
			return (split_recurv_parser(head, index - 1, index + 2, minishell));
		if (ptr[index] == '&' && ptr[index + 1] == '&')
			return (split_recurv_parser(head, index - 1, index + 2, minishell));
		if (ptr[index] == '|')
			return (split_recurv_parser(head, index - 1, index + 1, minishell));
	}
	tmp = lexar(head, minishell);
	if (tmp == FUNC_FAIL)
		return (FUNC_FAIL);
	return (FUNC_SUC);
}

t_ast_node	*parser(char *str, t_minishell *minishell)
{
	t_ast_node	*ret;
	int			err;

	ret = init_ast_node(CMDNODE);
	ret->cmd_node->str = init_doub_char(&str, 1);
	err = recurv_parser(ret, minishell);
	if (err == FUNC_FAIL)
	{
		free_ast_tree(ret);
		return (NULL);
	}
	return (ret);
}
