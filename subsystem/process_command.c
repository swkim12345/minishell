/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:20:26 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/25 15:54:57 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

/*
	cmd struct list
*/

int	contains_slash(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}

char	*find_from_path(t_cmd_node *cmd_node, t_minishell *minishell)
{
	char	*path;
	char	**parsed_path;
	char	*temp_str;
	int		i;
	int		malloc_size;

	i = -1;
	path = ft_getenv(minishell->env, "PATH");
	if (!path)
		return (0);
	parsed_path = ft_split(path, ":");
	while (parsed_path[++i])
	{
		malloc_size = ft_strlen(parsed_path[i])
			+ ft_strlen(cmd_node->cmd_name) + 2;
		ft_strlcat(temp_str, parsed_path[i], malloc_size);
		ft_strlcat(temp_str, "/", malloc_size);
		ft_strlcat(temp_str, cmd_node->str, malloc_size);
		if (access(temp_str, X_OK | F_OK) == 0)
			return (temp_str);
		free(temp_str);
	}
	return (0);
}

int	is_builtin_fn(t_cmd_node *cmd_node)
{
	char	*str;

	str = malloc(cmd_node->cmd_name);

	if (str_equal(str, "echo") || str_equal(str, "pwd")
		|| str_equal(str, "pwd") || str_equal(str, "export")
		|| str_equal(str, "unset") || str_equal(str, "env")
		|| str_equal(str, "exit"))
		return (1);
	return (0);
}


int	process_extern_cmd(t_cmd_node *cmd_node, t_minishell *minishell)
{
	pid_t	pid;
	int		status;
	char	*execute_path;
	char	**envp;

	pid = fork();
	if (pid == 0)
	{
		envp = tree_to_char(minishell->export);
		if (!contains_slash(cmd_node->cmd_name))
		{
			execute_path = set_command_path(cmd_node, minishell);
			if (!execute_path)
				command_not_found_error(minishell, cmd_node->cmd_name);
			if (execve(execute_path, cmd_node->str, envp));
				shell_error(minishell, cmd_node->cmd_name, "hello");
		}
		else
		{
			
			execve(cmd_node->cmd_name, cmd_node->str, envp);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (WIFEXITED(status));
}

// int	set_read_fd(t_redirection *node, t_minishell *minishell)
// {
// 	int	fd;

// 	if (node->flag & LT_SIGN)
// 		fd = open(minishell->tmp_file, O_CREAT | O_TRUNC, 0777);
// 	else if (node->flag & DB_LT_SIGN)
		
// }

// int	process_redirection(t_cmd_node *cmd_node, t_minishell *minishell)
// {
// 	t_redirection	*cur_node;

// 	cur_node = cmd_node->red;
// 	while (cur_node)
// 	{
// 		if (cur_node->flag & LT_SIGN)
// 			set_read_fd(cur_node, minishell);
// 	}
// 	return (0);
// }

int	process_command(t_cmd_node *cmd_node, t_minishell *minishell)
{
	cmd_node->cmd_name = cmd_node->str[0];
	expand_argument(cmd_node);
	if (is_builtin_fn(cmd_node))
		minishell->exit_code = process_builtin(cmd_node, minishell);
	else
		minishell->exit_code = process_extern_cmd(cmd_node, minishell);
	return (minishell->exit_code);
}
