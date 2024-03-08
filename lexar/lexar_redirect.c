/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:16:35 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/08 14:04:23 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexar.h"

static int	lexar_redirect_next_token(t_ast_node *node,
			t_minishell *minishell, int index)
{
	char	*ptr;
	int		tmp;

	ptr = node->cmd_node->str[0];
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
	return (index);
}

static int	lexar_redirect_ret(t_ast_node *node, t_minishell *minishell,
			t_redirection *red, int start)
{
	if (red->flag == DB_LT_SIGN)
	{
		red->str = eof_parser(red->str);
		node->index = minishell->tmp_file_counter + 1;
		if (heredoc_open_fd(red, minishell) == FUNC_FAIL)
			return (-2);
	}
	if (red->flag == DB_LT_SIGN || red->flag == DB_GT_SIGN)
		return (start - 3);
	else
		return (start - 2);
}

static int	lexar_redirect_err_token(t_ast_node *node, t_minishell *minishell,
			int index, int start)
{
	char	*ptr;
	int		tmp;

	ptr = node->cmd_node->str[0];
	index = start - index;
	node->err_flag = TRUE;
	index += skip_space(&ptr[index]);
	tmp = err_token_finder(ptr, index);
	return (syntax_err_message(&ptr[index], tmp, -2, minishell));
}

int	lexar_redirect(t_ast_node *node, t_minishell *minishell, int index)
{
	char			*ptr;
	int				start;
	int				name_start;
	t_redirection	*red;

	ptr = node->cmd_node->str[0];
	red = (t_redirection *)ft_calloc(sizeof(t_redirection), 1);
	redirect_node_push(node, red);
	index = find_next_token_red(ptr, index, red);
	start = index;
	index += skip_space(&ptr[index]);
	if (ptr[index] == '\0' || ptr[index] == '<' || ptr[index] == '>')
		return (lexar_redirect_err(node, minishell, ptr, index));
	index = lexar_redirect_next_token(node, minishell, index);
	if (index == NOTDEFINED)
		return (FUNC_FAIL);
	name_start = start + skip_space(&ptr[start]);
	red->str = ft_substr(&ptr[name_start], 0, index - name_start);
	ft_strlcat(ptr, &ptr[index], ft_strlen(ptr) + ft_strlen(&ptr[index]) + 1);
	if (red->str[0] == '\0')
		return (lexar_redirect_err_token(node, minishell, index, start));
	return (lexar_redirect_ret(node, minishell, red, start));
}
