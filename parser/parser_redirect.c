/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:32:15 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/07 20:02:53 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	read_heredoc_child_join(t_minishell *minishell,
		t_tmp_file *tmp_file, int fd, char *line)
{
	char		*str;
	char		**tmp;
	int			index;

	str = ft_strjoin("\"", line);
	free(line);
	line = ft_strjoin(str, "\"");
	free(str);
	tmp = string_parser(line, minishell);
	index = -1;
	while (tmp[++index])
	{
		ft_putstr_fd(tmp[index], fd);
		if (tmp[index + 1])
			ft_putstr_fd(" ", fd);
	}
	ft_putchar_fd('\n', fd);
	free_2d_str(tmp);
}

static void	read_heredoc_child_while(t_minishell *minishell,
			t_tmp_file *tmp_file, int fd)
{
	char		*line;

	while (1)
	{
		line = readline("> ");
		if (!line || str_equal(line, tmp_file->eof))
			break ;
		read_heredoc_child_join(minishell, tmp_file, fd, line);
		free(line);
	}
}

static void	read_heredoc_child(t_minishell *minishell, t_tmp_file *tmp_file)
{
	int			fd;
	int			index;
	char		**tmp;

	set_heredoc_int_handler();
	fd = tmp_file->fd;
	if (fd == -1)
		shell_error(minishell, "heredoc", 0);
	read_heredoc_child_while(minishell, tmp_file, fd);
	free_tmp_list(minishell->tmp_list, minishell, FALSE);
	close(fd);
	exit(FUNC_SUC);
}

int	read_heredoc(t_minishell *minishell, t_tmp_file *tmp_file)
{
	pid_t		pid;
	int			wstatus;

	pid = fork();
	wstatus = 0;
	if (pid == 0)
		read_heredoc_child(minishell, tmp_file);
	else
	{
		signal(SIGINT, SIG_IGN);
		wait(&wstatus);
	}
	return (wstatus);
}

int	traverse_redirection(t_minishell *minishell)
{
	t_tmp_file	*tmp;

	if (minishell->tmp_list == NULL)
		return (FUNC_SUC);
	tmp = minishell->tmp_list->head;
	if (tmp == NULL)
		return (FUNC_SUC);
	while (tmp)
	{
		read_heredoc(minishell, tmp);
		tmp = tmp->next;
	}
	return (FUNC_SUC);
}
