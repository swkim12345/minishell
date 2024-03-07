/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:16:35 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/07 20:18:59 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	heredoc_open_fd(t_redirection *red, t_minishell *minishell)
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
		return (FUNC_SUC);
	}
	red->index = minishell->tmp_file_counter;
	tmp_file->eof = ft_strdup(red->str);
	tmp_list_push(tmp_file, minishell);
	return (FUNC_SUC);
}

static int	find_next_token_red(char *ptr, int index, t_redirection *red)
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

int	lexar_redirect(t_ast_node *node, t_minishell *minishell, int index)
{
	char			*ptr;
	int				start;
	int				name_start;
	int				tmp;
	t_redirection	*red;

	ptr = node->cmd_node->str[0];
	red = (t_redirection *)malloc(sizeof(t_redirection));
	ft_memset((void *)red, 0, sizeof(t_redirection));
	redirect_node_push(node, red);
	index = find_next_token_red(ptr, index, red);
	start = index;
	index += skip_space(&ptr[index]);
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
		return (syntax_err_message(&ptr[index], tmp - index + 1,
				-2, minishell));
	}
	while (ptr[index] != '\0')
	{
		if (ptr[index] == '\"' || ptr[index] == '\'')
		{
			tmp = finder(&ptr[index + 1], ptr[index]);
			if (tmp == NOTDEFINED)
			{
				node->err_flag = TRUE;
				return (syntax_err_message(&ptr[index],
						NOTDEFINED, -2, minishell));
			}
			index += tmp + 2;
			continue ;
		}
		if (ft_isspace(ptr[index]) == TRUE || ptr[index] == '<'
				|| ptr[index] == '>')
			break ;
		index++;
	}
	name_start = start + skip_space(&ptr[start]);
	red->str = ft_substr(&ptr[name_start], 0, index - name_start);
	ft_strlcat(ptr, &ptr[index], ft_strlen(ptr) + ft_strlen(&ptr[index]) + 1);
	if (red->str[0] == '\0')
	{
		index = start - index;
		node->err_flag = TRUE;
		index += skip_space(&ptr[index]);
		tmp = err_token_finder(ptr, index);
		return (syntax_err_message(&ptr[index], tmp + 1, -2, minishell));
	}
	if (red->flag == DB_LT_SIGN)
	{
		red->str = eof_parser(red->str);
		node->index = minishell->tmp_file_counter + 1;
		if (heredoc_open_fd(red, minishell) == FUNC_FAIL) //free add required
			return (-2);
	}
	if (red->flag == DB_LT_SIGN || red->flag == DB_GT_SIGN)
		return (start - 3);
	else
		return (start - 2);
}
