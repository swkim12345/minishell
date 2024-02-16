/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:21:24 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/16 13:46:36 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

// int	fd_cd_helper(t_cmd_node *cmd_node)
// {
	
// }

int	ft_cd_error(t_cd *info, t_minishell *minishell)
{
	int		exit_status;

	minishell->exit_code = errno;
	exit_status = errno;
	write(2, minishell->execute_name, ft_strlen(minishell->execute_name));
	write(2, ": cd: ", 6);
	perror(info->directory);
	return (exit_status);
}

int	check_option(char *str)
{
	int	option_num;

	option_num = 0;
	printf("option_str: %s\n", str);
	if (ft_strlen(str) > 1 && str[0] == '-' && (str[1] == 'L' || str[1] == 'P'))
		str++;
	else
		return (NOTDEFINED);
	while (str && *str)
	{
		if (*str == 'L')
			option_num = 0;
		else if (*str == 'P')
			option_num = 1;
		else
			return (NOTDEFINED);
		str++;
	}
	return (option_num);
}

void	init_t_cd(t_cd *info, t_cmd_node *cmd_node)
{
	int	i;
	int	option_result;

	i = 1;
	info->home_dir = getenv("HOME");
	info->cd_flag = 0;
	while (cmd_node->str[i])
	{
		option_result = check_option(cmd_node->str[i]);
		if (option_result != NOTDEFINED)
			info->cd_flag = option_result;
		else
			break ;
		i++;
	}
	info->directory_index = i;
	info->directory = cmd_node->str[info->directory_index];
	if (info->directory[0] == '/')
		info->cd_flag |= PATH_TYPE;
	info->cur_path = 0;
}

int	check_end_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == '\\')
		return (1);
	return (0);
}

void	free_2d_str(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	check_is_dir(t_cd *info, t_minishell *minishell)
{
	if (stat(info->cur_path, &info->file_stat) == -1)
		return (ft_cd_error(info, minishell));
	if (S_ISDIR(info->file_stat.st_mode))
		return (TRUE);
	else
		return (FALSE);
}

void	find_local_dir(t_cd *info, t_minishell *minishell)
{
	char	*temp_str;

	temp_str = easy_cat(minishell->cwd, "/");
	info->check_str = easy_cat(temp_str, info->directory);
	printf("check_str: %s\n", info->check_str);
	if (stat(info->check_str, &info->file_stat) == -1)
		ft_cd_error(info, minishell);
	else
		info->cur_path = info->check_str;
	free(temp_str);
}

int	check_cdpath(t_cd *info, t_minishell *minishell)
{
	int		i;
	char	*temp_str;

	info->path_arr = ft_split(info->cdpath, ':');
	i = 0;
	while (info->path_arr[i])
	{
		if (check_end_slash(info->path_arr[i]) == FALSE)
		{
			temp_str = easy_cat(info->path_arr[i], "/");
			info->check_str = easy_cat(temp_str, info->directory);
			free(temp_str);
		}
		else
			info->check_str = easy_cat(info->path_arr[i], info->directory);
		if (stat(info->check_str, &info->file_stat) == -1 && errno != ENOENT)
		{
			free(info->check_str);
			return (ft_cd_error(info, minishell));
		}
		if (S_ISDIR(info->file_stat.st_mode))
		{
			free_2d_str(info->path_arr);
			info->cur_path = info->check_str;
			return (0);
		}
		free(info->check_str);
	}
	free_2d_str(info->path_arr);
	return (0);
}

void	find_curpath(t_cd *info, t_minishell *minishell)
{
	info->cdpath = getenv("CDPATH");
	if (info->cdpath)
		check_cdpath(info, minishell);
	else if (minishell->exit_code == 0 && !info->cur_path)
		find_local_dir(info, minishell);
	// printf("cwd_1: %s\n", info->cur_path);
}

char	*stack_to_str(t_str_list *stack)
{
	int			i;
	t_str_node	*cur_node;
	t_parse_str	parse_str;
	char		*return_str;

	init_parse_str(&parse_str);
	while (stack->size > 0)

	{
		i = -1;
		cur_node = dequeue(stack);
		while (cur_node->str[++i])
			append_char(&parse_str, cur_node->str[i]);
		free(cur_node->str);
		free(cur_node);
	}
	return_str = ft_substr(parse_str.str, 0, parse_str.cursor);
	free(parse_str.str);
	return (return_str);
}

void	parse_dots(t_cd *info, t_minishell *minishell)
{
	int			i;
	int			start;
	t_str_node	*cur;
	char		*temp_str;
	t_str_list	stack;

	i = 0;
	start = 0;
	init_str_list(&stack);
	while (info->cur_path[i])
	{
		if (ft_strncmp(&info->cur_path[i], "./", 2) == 0)
		{
			start += 2;
			i++;
		}
		else if (ft_strncmp(&info->cur_path[i], "../", 3) == 0)
		{
			i += 2;
			start += 3;
			cur = pop(&stack);
			if (cur)
			{
				free(cur->str);
				free(cur);
			}
		}
		else if (info->cur_path[i] == '/')
		{
			temp_str = ft_substr(info->cur_path, start, i - start + 1);
			printf("%s\n", temp_str);
			enqueue(&stack, create_node(temp_str));
			start = i + 1;
		}
		i++;
	}
	if (info->cur_path[i - 1] != '/')
	{
		temp_str = ft_substr(info->cur_path, start, i);
		enqueue(&stack, create_node(temp_str));
	}
	printf("tail_str: %s\n", stack.tail->str);
	while (stack.size > 1 && str_equal(stack.tail->str, "/") == 1)
	{
		printf("tail_str: %s\n", stack.tail->str);
		cur = pop(&stack);
		free(cur->str);
		free(cur);
	}
	minishell->cwd = stack_to_str(&stack);
}

void	set_curpath_pwd(t_cd *info, t_minishell *minishell)
{
	char	*temp_str;

	temp_str = easy_cat(minishell->cwd, "/");
	info->cur_path = easy_cat(temp_str, info->cur_path);
	free(temp_str);
}

void	cleanup(t_cd *info, char *temp_cwd)
{
	if ((info->cd_flag & PATH_TYPE) == FALSE)
		free(info->cur_path);
	free(temp_cwd);
}

int	ft_cd(t_cmd_node *cmd_node, t_minishell *minishell)
{
	t_cd	info;
	char	*temp_cwd;

	init_t_cd(&info, cmd_node);
	printf("option: %d\n", info.cd_flag);
	temp_cwd = minishell->cwd;
	if (!info.directory && !info.home_dir)
		return (0);
	else if (!info.directory && info.home_dir)
	{
		if (chdir(info.home_dir) == -1)
			return (ft_cd_error(&info, minishell));
	}
	if (info.directory[0] != '/' && info.directory[0] != '.'
		&& !(info.directory[0] == '.' && info.directory[1] == '.'))
		find_curpath(&info, minishell);
	if (chdir(info.directory) == -1)
		return (ft_cd_error(&info, minishell));
	else if (info.directory[0] == '/' && info.directory[0] == '.'
		&& (info.directory[0] == '.' && info.directory[1] == '.'))
		info.cur_path = info.directory;
	if (info.cd_flag == 0)
	{
		if (info.directory[0] == '.'
			|| (info.directory[0] == '.' && info.directory[1] == '.'))
			set_curpath_pwd(&info, minishell);
		parse_dots(&info, minishell);
	}
	else
		minishell->cwd = getcwd(0, 0);
	printf("cwd: %s\n", minishell->cwd);
	system("pwd");
	cleanup(&info, temp_cwd);
	return (0);
}

// void	check()
// {
// 	system("leaks a.out");
// }

int main()
{
	// atexit(check);
	system("echo $CDPATH");
	t_cmd_node	cmd_node;
	t_minishell minishell;
	char *input_str = readline(0);
	cmd_node.str = string_parser(input_str, &minishell);
	
	minishell.cwd = getcwd(0,0);
	minishell.execute_name = "minishell";
	minishell.exit_code = ft_cd(&cmd_node, &minishell);
	printf("exit_status: %d\n", minishell.exit_code);
	free(input_str);
	free(minishell.cwd);
	int i = 0;
	while (cmd_node.str[i])
	{
		printf("%p\n", cmd_node.str[i]);
		free(cmd_node.str[i]);
		i++;
	}
	free(cmd_node.str);
}