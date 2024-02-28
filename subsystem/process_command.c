/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:20:26 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/28 19:59:21 by minsepar         ###   ########.fr       */
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
	pid = fork();
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
			execute_path = find_from_path(cmd_node, minishell);
			check_file_valid(execute_path, cmd_node, minishell);
			printf("cmd_name: %s\n", cmd_node->cmd_name);
			//arg 가 그냥 fixed 할수 없음. 고쳐야 됨
			if (execve(execute_path, cmd_node->str, minishell->envp) == -1)
			{
				printf("error\n");
				shell_error(minishell, cmd_node->cmd_name, cmd_node->str[1]);
			}
		}
		else
		{
			check_file_valid(cmd_node->cmd_name, cmd_node, minishell);
			printf("cmd_name: %s\n", cmd_node->cmd_name);
			if (execve(cmd_node->cmd_name, cmd_node->str, envp) == -1)
			{
				printf("error\n");
				shell_error(minishell, cmd_node->cmd_name, 0);
			}
		}
	}
	else
		waitpid(pid, &status, 0);
	return (WIFEXITED(status));
}

void	print_ast_node(t_ast_node *ast_node)
{
	printf("ast_node------------------------\n");
	printf("left_node: [%p]\n", ast_node->left_node);
	printf("right_node: [%p]\n", ast_node->right_node);
	printf("next_ast_node: [%p]\n", ast_node->next_ast_node);
	printf("cmd_node: [%p]\n", ast_node->cmd_node);
	printf("log_opr: [%d]\n", ast_node->flag);
}

void	print_cmd_node(t_cmd_node *cmd_node)
{
	printf("cmd_node-------------------------------\n");
	printf("cmd_node: [%p]\n", cmd_node);
	printf("cmd_name: [%s]\n", cmd_node->cmd_name);
	int i = 0;
	while (cmd_node->str[i])
	{
		printf("str[%d]: [%s]\n", i, cmd_node->str[i]);
		i++;
	}
}

int	process_command(t_cmd_node *cmd_node, t_minishell *minishell)
{
	printf("%p\n", cmd_node->str);
	cmd_node->cmd_name = cmd_node->str[0];
	print_cmd_node(cmd_node);
	//argumnet already expanded ..?
	//expand_argument(cmd_node);
	ft_unsetenv(minishell->export, "_");
	ft_setenv(minishell->env, "_", cmd_node->cmd_name);
	if (is_builtin_fn(cmd_node))
	{
		printf("running builtin fn\n");
		minishell->exit_code = process_builtin(cmd_node, minishell);
	}
	else
	{
		printf("running builtin fn\n");
		minishell->exit_code = process_extern_cmd(cmd_node, minishell);
	}
	return (minishell->exit_code);
}
