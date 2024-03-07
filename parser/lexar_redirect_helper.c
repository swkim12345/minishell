/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_redirect_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:47:24 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/07 22:48:31 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	heredoc_open_fd(t_redirection *red, t_minishell *minishell)
{
	t_tmp_file	*tmp_file;
	char		*tmp;

	tmp_file = (t_tmp_file *)ft_calloc(sizeof(t_tmp_file), 1);
	tmp = ft_itoa(minishell->tmp_file_counter);
	tmp_file->tmp = ft_strjoin(minishell->tmp_file_name, tmp);
	free(tmp);
	tmp_file->fd = open(tmp_file->tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tmp_file->fd == -1)
	{
		free(tmp_file->tmp);
		free(tmp_file);
		return (FUNC_FAIL);
	}
	red->index = minishell->tmp_file_counter;
	tmp_file->eof = ft_strdup(red->str);
	tmp_list_push(tmp_file, minishell);
	return (FUNC_SUC);
}

int	find_next_token_red(char *ptr, int index, t_redirection *red)
{
	if (ptr[index] == '<')
	{
		ptr[index] = '\0';
		if (ptr[index + 1] == '<')
		{
			red->flag = DB_LT_SIGN;
			index++;
		}
		else
			red->flag = LT_SIGN;
	}
	else
	{
		ptr[index] = '\0';
		if (ptr[index + 1] == '>')
		{
			red->flag = DB_GT_SIGN;
			index++;
		}
		else
			red->flag = GT_SIGN;
	}
	index += 1;
	return (index);
}

int	lexar_redirect_err(t_ast_node *node, t_minishell *minishell,
		char *ptr, int index)
{
	int	tmp;

	if (ptr[index] == '\0')
	{
		node->err_flag = TRUE;
		if (node->flag & OR_FLAG)
			return (syntax_err_message("||", NOTDEFINED, -2, minishell));
		if (node->flag & AND_FLAG)
			return (syntax_err_message("&&", NOTDEFINED, -2, minishell));
		if (node->next_ast_node)
			return (syntax_err_message("|", NOTDEFINED, -2, minishell));
		return (syntax_err_message("newline", NOTDEFINED, -2, minishell));
	}
	if (ptr[index] == '<' || ptr[index] == '>')
	{
		node->err_flag = TRUE;
		tmp = err_token_finder(ptr, index);
		return (syntax_err_message(&ptr[index], tmp - index,
				-2, minishell));
	}
	return (NOTDEFINED);
}
