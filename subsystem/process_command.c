/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:20:26 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/05 12:58:09 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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
	parsed_path = ft_split(path, ':');
	while (parsed_path[++i])
	{
		malloc_size = ft_strlen(parsed_path[i])
			+ ft_strlen(cmd_node->cmd_name) + 2;
		temp_str = ft_calloc(sizeof(char), malloc_size);
		ft_strlcat(temp_str, parsed_path[i], malloc_size);
		ft_strlcat(temp_str, "/", malloc_size);
		ft_strlcat(temp_str, cmd_node->cmd_name, malloc_size);
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

int	is_builtin_fn(t_cmd_node *cmd_node)
{
	char	*lowercase_str;

	lowercase_str = to_lowercase_str(cmd_node->cmd_name);
	if (str_equal(lowercase_str, "echo") || str_equal(lowercase_str, "pwd")
		|| str_equal(lowercase_str, "cd") || str_equal(lowercase_str, "export")
		|| str_equal(lowercase_str, "unset") || str_equal(lowercase_str, "env")
		|| str_equal(lowercase_str, "exit"))
	{
		free(lowercase_str);
		return (1);
	}
	free(lowercase_str);
	return (0);
}

int	check_file_valid(char *execute_path, t_cmd_node *cmd_node, t_minishell *minishell)
{
	struct stat	file_info;

	//ft_printf("execute_path: [%s]\n", execute_path);
	if (!execute_path)
		command_not_found_error(minishell, cmd_node->cmd_name);
	stat(execute_path, &file_info);
	if (S_ISDIR(file_info.st_mode))
		command_is_directory_error(minishell, cmd_node->cmd_name);
	return (0);
}

int	process_extern_cmd(t_cmd_node *cmd_node, t_minishell *minishell)
{
	pid_t		pid;
	int			status;
	char		*execute_path;
	char		**envp;
	// struct stat	file_info;

	// envp = minishell->envp;
	status = 0;
	pid = fork();
	signal(SIGINT, SIG_DFL);
	if (pid == 0)
	{
		envp = ft_charenv(minishell->export, FALSE);
		// printf("here----------------------------\n");
		// int i = 0;
		// while (envp[i])
		// {
		// 	printf("envp: [%s]\n", envp[i]);
		// 	i++;
		// }
		if (!ft_strchr(cmd_node->cmd_name, '/'))
		{
			// ft_printf("[%s]\n", cmd_node->cmd_name);
			if (strncmp(cmd_node->cmd_name, "", 1) == 0)
				command_not_found_error(minishell, cmd_node->cmd_name);
			execute_path = find_from_path(cmd_node, minishell);
			check_file_valid(execute_path, cmd_node, minishell);
			// //ft_printf("cmd_name: [%s]\n", cmd_node->cmd_name);
			//arg 가 그냥 fixed 할수 없음. 고쳐야 됨
			if (execve(execute_path, cmd_node->str, minishell->envp) == -1)
			{
				//ft_printf("error\n");
				shell_error(minishell, cmd_node->cmd_name, cmd_node->str[1]);
			}
		}
		else
		{
			check_file_valid(cmd_node->cmd_name, cmd_node, minishell);
			if (execve(cmd_node->cmd_name, cmd_node->str, envp) == -1)
			{
				//ft_printf("error\n");
				shell_error(minishell, cmd_node->cmd_name, 0);
			}
		}
	}
	else
	{
		// set_signal_handler();
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		set_signal_handler();
	}
	return (WEXITSTATUS(status));
}

void	print_ast_node(t_ast_node *ast_node)
{
	(void) ast_node;
	ft_printf("ast_node------------------------\n");
	ft_printf("left_node: [%p]\n", ast_node->left_node);
	ft_printf("right_node: [%p]\n", ast_node->right_node);
	ft_printf("next_ast_node: [%p]\n", ast_node->next_ast_node);
	ft_printf("cmd_node: [%p]\n", ast_node->cmd_node);
	ft_printf("flag: [%d]\n", ast_node->flag);
}

void	print_cmd_node(t_cmd_node *cmd_node)
{
	ft_printf("cmd_node---------------------------\n");
	ft_printf("cmd_node: [%p]\n", cmd_node);
	ft_printf("[%s]\n", cmd_node->cmd_name);
	int i = 0;
	while (cmd_node->str[i])
	{
		ft_printf("str[%d]: [%s]\n", i, cmd_node->str[i]);
		i++;
	}
}

int	process_command(t_cmd_node *cmd_node, t_minishell *minishell)
{
	t_pipe_traverse	*info;

	// ft_printf("%p\n", cmd_node->str);
	(void)info;
	cmd_node->cmd_name = cmd_node->str[0];
	// print_cmd_node(cmd_node);
	//argumnet already expanded ..?
	//expand_argument(cmd_node);
	// ft_unsetenv(minishell->export, "_");
	// ft_setenv(minishell->env, "_", cmd_node->cmd_name);
	if (is_builtin_fn(cmd_node))
	{
		//ft_printf("running builtin fn\n");
		//ft_printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		minishell->exit_code = process_builtin(cmd_node, minishell);
		// ft_printf("flag %d\n", minishell->flag);
		if (minishell->flag & PIPE_TRAVERSE)
		{
			// ft_printf("here\n");
			info = minishell->pipe_info;
			// printf("info->current_pipe: %d\n", info->current_pipe);
			exit(minishell->exit_code);
		}
		//ft_printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	}
	else
	{
		//ft_printf("running extern cmd\n");
		//ft_printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		minishell->exit_code = process_extern_cmd(cmd_node, minishell);
		set_signal_handler();
		//ft_printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	}
	return (minishell->exit_code);
}
