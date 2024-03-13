/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:13:58 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/13 16:06:49 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	get_file_num(char **file_list)
{
	int	i;

	i = 0;
	while (file_list[i])
		i++;
	return (i);
}

int	set_read_fd(t_redirection *redirect_node, t_minishell *minishell,
		t_ast_node *ast_node)
{
	int				fd;
	char			**file_list;

	if (redirect_node->flag & LT_SIGN)
	{
		file_list = string_parser(redirect_node->str, minishell);
		if (get_file_num(file_list) > 1 || file_list[0] == NULL)
		{
			ambiguous_redirect_error(minishell, redirect_node, file_list);
			return (1);
		}
		fd = open(file_list[0], O_RDONLY);
		free_2d_str(file_list);
	}
	else if (redirect_node->flag & DB_LT_SIGN)
		fd = get_heredoc_fd(minishell, ast_node->index);
	else
		return (1);
	if (fd < 0)
		return (redirection_error(minishell, redirect_node));
	if (dup2(fd, 0) == -1)
		return (redirection_error(minishell, redirect_node));
	close(fd);
	return (0);
}

int	set_write_fd(t_redirection *redirect_node, t_minishell *minishell)
{
	int				fd;
	char			**file_list;

	file_list = string_parser(redirect_node->str, minishell);
	if (get_file_num(file_list) > 1 || file_list[0] == NULL)
	{
		ambiguous_redirect_error(minishell, redirect_node, file_list);
		return (1);
	}
	if (redirect_node->flag & GT_SIGN)
		fd = open(file_list[0], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (redirect_node->flag & DB_GT_SIGN)
		fd = open(file_list[0], O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
	{
		free_2d_str(file_list);
		return (1);
	}
	free_2d_str(file_list);
	if (fd < 0)
		return (redirection_error(minishell, redirect_node));
	if (dup2(fd, 1) == -1)
		return (redirection_error(minishell, redirect_node));
	close(fd);
	return (0);
}

int	process_redirection(t_ast_node *ast_node, t_minishell *minishell)
{
	t_redirection	*cur_node;

	cur_node = ast_node->red;
	if (cur_node)
		minishell->exit_code = 0;
	while (cur_node)
	{
		if ((cur_node->flag & LT_SIGN) || (cur_node->flag & DB_LT_SIGN))
			minishell->exit_code = set_read_fd(cur_node, minishell, ast_node);
		else if ((cur_node->flag & GT_SIGN) || (cur_node->flag & DB_GT_SIGN))
			minishell->exit_code = set_write_fd(cur_node, minishell);
		if (minishell->exit_code != 0)
			return (minishell->exit_code);
		cur_node = cur_node->next;
	}
	return (0);
}
