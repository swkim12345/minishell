/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:21:24 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/06 21:54:38 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
//Upper case 

int	check_option(char *str)
{
	int	option_num;

	option_num = 0;
	//ft_printf("option_str: %s\n", str);
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

void	init_t_cd(t_cd *info, t_cmd_node *cmd_node, t_minishell *minishell)
{
	int	i;
	int	option_result;

	ft_memset(info, 0, sizeof(t_cd));
	i = 1;
	info->execute_name = cmd_node->cmd_name;
	info->home_dir = ft_getenv(minishell->env, "HOME");
	info->cdpath = ft_getenv(minishell->env, "CDPATH");
	//ft_printf("info->home %s\n", info->home_dir);
	//ft_printf("info->cdpath %s\n", info->cdpath);
	info->cd_flag = 0;
	while (cmd_node->str[i])
	{
		option_result = check_option(cmd_node->str[i]);
		//ft_printf("[%s] option_result: %d\n", cmd_node->str[i], option_result);
		if (option_result != NOTDEFINED)
			info->cd_flag = option_result;
		else
			break ;
		i++;
	}
	info->directory_index = i;
	//ft_printf("directory_index: %d\n", info->directory_index);
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
	//ft_printf("check_str: %s\n", info->check_str);
	if (stat(info->check_str, &info->file_stat) == 0)
		info->cur_path = info->check_str;
	else
	{
		info->cur_path = ft_strdup(info->directory);
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
	//ft_printf("find_curpath\n");
	info->cd_flag |= NO_DOT_RELATIVE;
	if (info->cdpath)
		check_cdpath(info, minishell);
	if (!info->cur_path)
		find_local_dir(info, minishell);
	//ft_printf("cwd_1: %s\n", info->cur_path);
}

void	free_str_stack(t_str_list *stack)
{
	t_str_node	*cur_node;

	while (stack->size > 0)
	{
		cur_node = dequeue(stack);
		free(cur_node->str);
		free(cur_node);
	}
}

char	*stack_to_str(t_str_list *stack)
{
	int			i;
	t_str_node	*cur_node;
	t_parse_str	parse_str;
	char		*return_str;

	init_parse_str(&parse_str);
	cur_node = stack->head;
	while (cur_node)
	{
		i = -1;
		ft_printf("cur_node: [%s]\n", cur_node->str);
		while (cur_node->str[++i])
			append_char(&parse_str, cur_node->str[i]);
		cur_node = cur_node->next;
	}
	return_str = ft_substr(parse_str.str, 0, parse_str.cursor);
	free(parse_str.str);
	return (return_str);
}

char	*stack_to_str_free(t_str_list *stack)
{
	char	*return_str;

	return_str = stack_to_str(stack);
	free_str_stack(stack);
	return (return_str);
}

int	parse_dots(t_cd *info, t_minishell *minishell, t_cmd_node *cmd_node)
{
	int			i;
	int			start;
	t_str_node	*cur;
	char		*temp_str;
	t_str_list	stack;

	(void) minishell;

	i = 0;
	start = 0;
	ft_memset(&stack, 0, sizeof(t_str_list));
	//ft_printf("info curpath: %s\n", info->cur_path);
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
			//ft_printf("here\n");
			temp_str = stack_to_str(&stack);
			if (stat(temp_str, &info->file_stat) == 0)
			{
				if (!S_ISDIR(info->file_stat.st_mode))
				{
					free_str_stack(&stack);
					free(temp_str);
					return (not_a_directory_error(info, minishell, cmd_node->cmd_name, info->home_dir));
				}
			}
			else
			{
				free_str_stack(&stack);
				free(temp_str);
				return (cd_error(info, minishell, info->execute_name, info->directory));
			}
			i += 2;
			start += 3;
			if (stack.size > 1)
			{
				cur = pop(&stack);
				//ft_printf("pop node: %s\n", cur->str);
				free(cur->str);
				free(cur);
			}
			free(temp_str);
		}
		else if (info->cur_path[i] == '/' && (i == 0 || i - start != 0))
		{
			temp_str = ft_substr(info->cur_path, start, i - start + 1);
			//ft_printf("token: %s\n", temp_str);
			//ft_printf("start: [%d], i: [%d]\n", start, i);
			enqueue(&stack, create_node(temp_str));
			start = i + 1;
		}
		else if (info->cur_path[i] == '/' && i - start == 0)
			start += 1;
		i++;
	}
	if (i - start == 2 && info->cur_path[i - 2] == '.'
		&& info->cur_path[i - 1] == '.')
	{
		if (stack.size > 1)
		{
			temp_str = stack_to_str(&stack);
			if (stat(temp_str, &info->file_stat) == 0)
			{
				if (!S_ISDIR(info->file_stat.st_mode))
				{
					free_str_stack(&stack);
					free(temp_str);
					return (not_a_directory_error(info, minishell, cmd_node->cmd_name, info->home_dir));
				}
			}
			else
			{
				free_str_stack(&stack);
				free(temp_str);
				return (cd_error(info, minishell, info->execute_name, info->directory));
			}
			cur = pop(&stack);
			free(temp_str);
			free(cur->str);
			free(cur);
		}
	}
	else if (info->cur_path[i - 1] != '/' 
		&& !(i - start == 1 && info->cur_path[i - 1] == '.'))
	{
		temp_str = ft_substr(info->cur_path, start, i - start + 1);
		enqueue(&stack, create_node(temp_str));
		
	}
	i = ft_strlen(stack.tail->str) - 1;
	if (stack.size > 1 && stack.tail->str[i] == '/')
	{
		//ft_printf("end with /\n");
		stack.tail->str[i] = 0;
	}
	//ft_printf("tail_str: %s\n", stack.tail->str);
	free(info->cur_path);
	info->cur_path = stack_to_str(&stack);
	free_str_stack(&stack);
	return (0);
}

void	set_curpath_pwd(t_cd *info, t_minishell *minishell)
{
	char	*temp_str;
	char	*cur_path_old;

	if (minishell->cwd[ft_strlen(minishell->cwd) - 1] != '/')
		temp_str = easy_cat(minishell->cwd, "/");
	else
		temp_str = ft_strdup(minishell->cwd);
	cur_path_old = info->cur_path;
	info->cur_path = easy_cat(temp_str, info->cur_path);
	free(cur_path_old);
	free(temp_str);
}

void	cleanup(char *temp_cwd)
{
	free(temp_cwd);
}

void	set_pwd_old_pwd(t_cmd_node *cmd_node, t_minishell *minishell, t_cd *info)
{
	char	*old_pwd;

	old_pwd = minishell->cwd;
	//ft_printf("%s\n", old_pwd);
	if (info->cd_flag & OPTION_FLAG)
	{
		//ft_printf("option flag -P\n");
		minishell->cwd = getcwd(0,0);
		if (!minishell->cwd)
			minishell->exit_code = builtin_error(minishell, cmd_node->cmd_name, 0);
	}
	else if (info->cur_path)
		minishell->cwd = ft_strdup(info->cur_path);
	else
		minishell->cwd = ft_strdup(info->home_dir);
	ft_setenv(minishell->export, "OLDPWD", old_pwd);
	ft_setenv(minishell->env, "OLDPWD", old_pwd);
	ft_setenv(minishell->export, "PWD", minishell->cwd);
	ft_setenv(minishell->env, "PWD", minishell->cwd);
	if (info->cur_path)
		free(info->cur_path);
	free(old_pwd);
}

//change shell error to msg
int	ft_cd(t_cmd_node *cmd_node, t_minishell *minishell)
{
	t_cd	info;

	init_t_cd(&info, cmd_node, minishell);
	//ft_printf("directory: [%p] [%s], home_dir: [%s]\n", info.directory, info.directory, info.home_dir);
	if (!info.directory && !info.home_dir)
		return (home_not_set_error(minishell, cmd_node->cmd_name, 0));
	else if (!info.directory && info.home_dir)
	{
		info.cur_path = ft_strdup(info.home_dir);
		if (chdir(info.cur_path) == -1)
			return (cd_error(&info, minishell, cmd_node->cmd_name, info.home_dir));
		set_pwd_old_pwd(cmd_node, minishell, &info);
		return (minishell->exit_code);
	}
	if (info.directory[0] == '/' || info.directory[0] == '.'
		|| (info.directory[0] == '.' && info.directory[1] == '.'))
		info.cur_path = ft_strdup(info.directory);
	if (info.cd_flag & NO_DOT_RELATIVE)
		find_curpath(&info, minishell);
	if (info.cd_flag & OPTION_FLAG)
	{
		if (chdir(info.cur_path) == -1)
		{
			if (chdir(info.directory))
				return (cd_error(&info, minishell, cmd_node->cmd_name, info.cur_path));
		}
		//export temp_cwd to oldpwd
		set_pwd_old_pwd(cmd_node, minishell, &info);
		//system("pwd");
		return (minishell->exit_code);
	}
	if (info.cur_path[0] != '/')
		set_curpath_pwd(&info, minishell);
	if (parse_dots(&info, minishell, cmd_node) == 1)
		return (1);
	// 바로 찍으면 안됨 chdir 하기전에 체크해주는 함수를 한개 만드는게 좋아보임
	if (stat(info.cur_path, &info.file_stat) == 0)
	{
		if (!S_ISDIR(info.file_stat.st_mode))
			return (not_a_directory_error(&info, minishell, cmd_node->cmd_name, info.directory));
	}
	else
		return (cd_error(&info, minishell, cmd_node->cmd_name, info.directory));
	if (chdir(info.cur_path) == -1)
		return (cd_error(&info, minishell, cmd_node->cmd_name, info.directory));
	set_pwd_old_pwd(cmd_node, minishell, &info);
	//ft_printf("minishell->cwd: [%s]\n", minishell->cwd);
	//system("pwd");
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
