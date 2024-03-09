/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_extern_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:34:20 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/09 11:31:40 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	check_file_valid(char *execute_path, t_cmd_node *cmd_node,
	t_minishell *minishell)
{
	struct stat	file_info;

	if (!execute_path)
		command_not_found_error(minishell, cmd_node->cmd_name);
	stat(execute_path, &file_info);
	if (S_ISDIR(file_info.st_mode))
		command_is_directory_error(minishell, cmd_node->cmd_name);
	return (0);
}

static char	*get_check_path_str(char *path_prefix, char *cmd_name)
{
	char	*temp_str;
	int		malloc_size;

	malloc_size = ft_strlen(path_prefix) + ft_strlen(cmd_name) + 2;
	temp_str = ft_calloc(sizeof(char), malloc_size);
	ft_strlcat(temp_str, path_prefix, malloc_size);
	ft_strlcat(temp_str, "/", malloc_size);
	ft_strlcat(temp_str, cmd_name, malloc_size);
	return (temp_str);
}

char	*find_from_path(t_cmd_node *cmd_node, t_minishell *minishell)
{
	char	*path;
	char	**parsed_path;
	char	*temp_str;
	int		i;

	i = -1;
	path = ft_getenv(minishell->env, "PATH");
	if (!path)
		return (0);
	parsed_path = ft_split(path, ':');
	while (parsed_path[++i])
	{
		temp_str = get_check_path_str(parsed_path[i], cmd_node->cmd_name);
		if (access(temp_str, F_OK) == 0)
		{
			free_2d_str(parsed_path);
			return (temp_str);
		}
		free(temp_str);
	}
	free_2d_str(parsed_path);
	return (0);
}

static int	process_cmd_parent(pid_t pid, t_minishell *minishell)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WTERMSIG(status) == 2)
	{
		minishell->exit_code = 130;
		ft_printf("\n");
	}
	else if (WTERMSIG(status) == 3)
	{
		minishell->exit_code = 131;
		ft_printf("Quit: 3\n", 1);
	}
	else
		minishell->exit_code = WEXITSTATUS(status);
	set_signal_handler();
	return (minishell->exit_code);
}

int	process_extern_cmd(t_cmd_node *cmd_node, t_minishell *minishell)
{
	pid_t		pid;
	char		**envp;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		envp = ft_charenv(minishell->export, FALSE);
		if (!ft_strchr(cmd_node->cmd_name, '/'))
			process_extern_cmd_no_slash(cmd_node, minishell);
		else
		{
			check_file_valid(cmd_node->cmd_name, cmd_node, minishell);
			if (execve(cmd_node->cmd_name, cmd_node->str, envp) == -1)
				shell_error(minishell, cmd_node->cmd_name, 0);
		}
	}
	else
		minishell->exit_code = process_cmd_parent(pid, minishell);
	return (minishell->exit_code);
}
