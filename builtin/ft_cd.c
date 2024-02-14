/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:21:24 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/14 20:38:41 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

// int	fd_cd_helper(t_cmd_node *cmd_node)
// {
	
// }

int	check_option(char *str)
{
	int	option_num;

	option_num = 0;
	if (ft_strlen(str) > 1 && str[0] == '-' && (str[1] == 'L' || str[1] == 'P'))
		str += 2;
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
	info->option_flag = 0;
	while (cmd_node->str[i])
	{
		option_result = check_option(cmd_node->str[i]);
		if (option_result != NOTDEFINED)
			info->option_flag = option_result;
		else
			break ;
		i++;
	}
	info->directory_index = i;
	info->directory = cmd_node->str[info->directory_index];
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

void	find_local_dir(t_cd *info)
{
	info->check_str = easy_cat("./", info->directory);
	if (stat(info->check_str, &info->file_stat) == -1)
		exit(1);
	if (S_ISDIR(info->file_stat.st_mode))
		info->cur_path = info->check_str;
	else
	printf("No such file or directory");
}

void	check_cdpath(t_cd *info)
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
		if (stat(info->check_str, &info->file_stat) == -1)
			exit(1);
		if (S_ISDIR(info->file_stat.st_mode))
		{
			info->cur_path = info->check_str;
			return ;
		}
		free(info->check_str);
	}
	free_2d_str(info->path_arr);
}

void	find_curpath(t_cd *info)
{

	info->cdpath = getenv("CDPATH");
	if (info->cdpath)
		check_cdpath(info);
	else if (!info->cur_path)
		find_local_dir(info);
}

void	parse_dots(t_cd *info)
{
	int		i;
	char	*cur_path;
	

	i = 0;
	cur_path = info->cur_path;
	while (cur_path[i])
	{
		
	}
}

void	set_curpath_pwd(t_cd *info)
{
	char	*pwd;
	char	*temp_str;

	pwd = getenv("PWD");
	if (check_end_slash(pwd) == FALSE)
	{
		temp_str = easy_cat(pwd, "/");
		info->cur_path = easy_cat(temp_str, info->cur_path);
	}
	else
		info->cur_path = easy_cat(pwd, info->cur_path);
	parse_dots(info);
}

int	ft_cd_helper(t_cmd_node *cmd_node, t_cd *info)
{
	
}

int	ft_cd(t_cmd_node *cmd_node)
{
	t_cd	info;

	init_t_cd(&info, cmd_node);
	if (!info.directory && !info.home_dir)
		return (0);
	else if (!info.directory && info.home_dir)
	{
		if (chdir(info.home_dir) == -1)
			return (errno);
	}
	else if (info.directory[0] == '/' || info.directory[0] == '.'
		|| (info.directory[0] == '.' && info.directory[1] == '.'))
		info.cur_path = info.directory;
	else
		find_curpath(&info);
	if (info.option_flag == 0)
	{
		if (info.directory[0] == '.'
			|| (info.directory[0] == '.' && info.directory[1] == '.'))
			set_curpath_pwd(&info);
	}
	return (0);
}

int main()
{
	t_cmd_node	cmd_node;
	char		*str[] = {"cd", "test_dir"};

	cmd_node.str = str;
	ft_cd(&cmd_node);
}