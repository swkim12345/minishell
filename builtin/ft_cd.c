/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:21:24 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/26 17:32:05 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
//Upper case 

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
	info->execute_name = cmd_node->cmd_name;
	info->home_dir = getenv("HOME");
	if (!info->home_dir)
		return ;
	printf("info->home %s\n", info->home_dir);
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
	if (info->directory)
	{
		if (info->directory[0] == '/')
			info->cd_flag |= PATH_TYPE;
		if (info->directory[0] != '/' && info->directory[0] != '.'
			&& !(info->directory[0] == '.' && info->directory[1] == '.'))
			info->cd_flag |= NO_DOT_RELATIVE;
	}
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

// int	check_is_dir(t_cd *info, t_minishell *minishell)
// {
// 	if (stat(info->cur_path, &info->file_stat) == -1)
// 		shell_error(minishell, info->);
// 	if (S_ISDIR(info->file_stat.st_mode))
// 		return (TRUE);
// 	else
// 		return (FALSE);
// }

void	find_local_dir(t_cd *info, t_minishell *minishell)
{
	char	*temp_str;

	temp_str = easy_cat(minishell->cwd, "/");
	info->check_str = easy_cat(temp_str, info->directory);
	printf("check_str: %s\n", info->check_str);
	if (stat(info->check_str, &info->file_stat) == 0)
		info->cur_path = info->check_str;
	else
	{
		info->cur_path = info->directory;
		free(info->check_str);
	}
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
		if (stat(info->check_str, &info->file_stat) == 0)
		{
			if (S_ISDIR(info->file_stat.st_mode))
			{
				free_2d_str(info->path_arr);
				info->cur_path = info->check_str;
				return (0);
			}
		}
		else if (errno != ENOENT)
		{
			free(info->check_str);
			free_2d_str(info->path_arr);
			shell_error(minishell, info->execute_name, info->directory);
		}
		free(info->check_str);
		i++;
	}
	free_2d_str(info->path_arr);
	return (0);
}

void	find_curpath(t_cd *info, t_minishell *minishell)
{
	info->cd_flag |= NO_DOT_RELATIVE;
	info->cdpath = getenv("CDPATH");
	if (info->cdpath)
		check_cdpath(info, minishell);
	if (!info->cur_path)
		find_local_dir(info, minishell);
	printf("cwd_1: %s\n", info->cur_path);
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
		printf("cur_node: [%s]\n", cur_node->str);
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
	printf("info curpath: %s\n", info->cur_path);
	while (info->cur_path[i])
	{
		if (ft_strncmp(&info->cur_path[i], "./", 2) == 0 && i - start == 0)
		{
			start += 2;
			i++;
		}
		else if (ft_strncmp(&info->cur_path[i], "../", 3) == 0
			&& i - start == 0)
		{
			printf("here\n");
			i += 2;
			start += 3;
			if (stack.size > 1)
			{
				cur = pop(&stack);
				printf("pop node: %s\n", cur->str);
				free(cur->str);
				free(cur);
			}
		}
		else if (info->cur_path[i] == '/' && (i == 0 || i - start != 0))
		{
			temp_str = ft_substr(info->cur_path, start, i - start + 1);
			printf("token: %s\n", temp_str);
			printf("start: [%d], i: [%d]\n", start, i);
			enqueue(&stack, create_node(temp_str));
			start = i + 1;
		}
		else if (info->cur_path[i] == '/' && i - start == 0)
			start += 1;
		i++;
	}
	if (info->cur_path[i - 2] == '.' && info->cur_path[i - 1] == '.'
		&& i - start == 2 && stack.size > 1)
	{
		cur = pop(&stack);
		free(cur->str);
		free(cur);
	}
	else if (info->cur_path[i - 1] != '/' && info->cur_path[i - 1] != '.'
		&& i - start > 0)
	{
		temp_str = ft_substr(info->cur_path, start, i - start + 1);
		enqueue(&stack, create_node(temp_str));
	}
	i = ft_strlen(stack.tail->str) - 1;
	if (stack.size > 1
		&& stack.tail->str[ft_strlen(stack.tail->str) - 1] == '/')
	{
		printf("end with /\n");
		stack.tail->str[i] = 0;
	}
	printf("tail_str: %s\n", stack.tail->str);
	minishell->cwd = stack_to_str(&stack);
}

void	set_curpath_pwd(t_cd *info, t_minishell *minishell)
{
	char	*temp_str;

	if (minishell->cwd[ft_strlen(minishell->cwd) - 1] != '/')
		temp_str = easy_cat(minishell->cwd, "/");
	else
		temp_str = ft_strdup(minishell->cwd);
	info->cur_path = easy_cat(temp_str, info->cur_path);
	free(temp_str);
}

void	cleanup(t_cd *info, char *temp_cwd)
{
	if (info->cd_flag ^ PATH_TYPE)
		free(info->cur_path);
	free(temp_cwd);
}

//change shell error to msg
int	ft_cd(t_cmd_node *cmd_node, t_minishell *minishell)
{
	t_cd	info;
	char	*temp_cwd;
	char	*temp_str;

	init_t_cd(&info, cmd_node);
	temp_cwd = minishell->cwd;
	printf("directory: [%p], home_dir: [%s]\n", info.directory, info.home_dir);
	if (!info.directory && !info.home_dir)
		return (0);
	else if (!info.directory && info.home_dir)
	{
		if (chdir(info.home_dir) == -1)
			return (0);
		temp_str = getcwd(0, 0);
		if (!temp_str)
			shell_error(minishell, info.execute_name, info.directory);
		free(temp_cwd);
		minishell->cwd = temp_str;
		return (0);
	}
	if (info.directory[0] == '/' || info.directory[0] == '.'
		|| (info.directory[0] == '.' && info.directory[1] == '.'))
		info.cur_path = info.directory;
	printf("1: %s\n", info.cur_path);
	if (info.cd_flag & NO_DOT_RELATIVE)
		find_curpath(&info, minishell);
	if (info.cd_flag & OPTION_FLAG)
	{
		if (chdir(info.cur_path) == -1)
			shell_error(minishell, info.execute_name, info.directory);
		temp_str = getcwd(0, 0);
		if (!temp_str)
			shell_error(minishell, info.execute_name, info.directory);
		minishell->cwd = temp_str;
		//export temp_cwd to oldpwd
		free(temp_cwd);
		system("pwd");
		return (minishell->exit_code);
	}
	printf("2: %s\n", info.cur_path);
	if (info.cur_path[0] != '/')
		set_curpath_pwd(&info, minishell);
	printf("3: %s\n", info.cur_path);
	parse_dots(&info, minishell);
	if (chdir(info.cur_path) == -1)
	{
		if (chdir(info.directory) == -1)
		{
			free(temp_cwd);
			shell_error(minishell, info.execute_name, info.directory);
		}
	}
	printf("minishell->cwd: [%s]\n", minishell->cwd);
	system("pwd");
	cleanup(&info, temp_cwd);
	return (0);
}

// int main()
// {
// 	// atexit(check);
// 	system("echo $CDPATH");
// 	t_cmd_node	cmd_node;
// 	t_minishell minishell;
// 	char *input_str = readline(0);
// 	cmd_node.str = string_parser(input_str, &minishell);
// 	// printf("here: %p\n", cmd_node.str[1]);
	
// 	minishell.cwd = getcwd(0,0);
// 	minishell.execute_name = "minishell";
// 	minishell.exit_code = ft_cd(&cmd_node, &minishell);
// 	printf("exit_status: %d\n", minishell.exit_code);
// 	free(input_str);
// 	free(minishell.cwd);
// 	int i = 0;
// 	while (cmd_node.str[i])
// 	{
// 		printf("%p\n", cmd_node.str[i]);
// 		free(cmd_node.str[i]);
// 		i++;
// 	}
// 	free(cmd_node.str);
// 	system("pwd");
// }
