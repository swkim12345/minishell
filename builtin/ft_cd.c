/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:21:24 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/08 20:52:44 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	check_option(char *str)
{
	int	option_num;

	option_num = 0;
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

static void	cd_check_cmd_str(t_cmd_node *cmd_node, t_cd *info)
{
	int	i;
	int	option_result;

	i = 1;
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
}

static void	init_t_cd(t_cd *info, t_cmd_node *cmd_node, t_minishell *minishell)
{
	ft_memset(info, 0, sizeof(t_cd));
	info->execute_name = cmd_node->cmd_name;
	info->home_dir = ft_getenv(minishell->env, "HOME");
	info->cdpath = ft_getenv(minishell->env, "CDPATH");
	info->cd_flag = 0;
	minishell->exit_code = 0;
	cd_check_cmd_str(cmd_node, info);
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

static int	ft_cd_nodir_arg(t_cd *info,
		t_cmd_node *cmd_node, t_minishell *minishell)
{
	if (!info->directory && !info->home_dir)
	{
		minishell->exit_code
			= home_not_set_error(minishell, cmd_node->cmd_name, 0);
		return (minishell->exit_code);
	}
	else if (!info->directory && info->home_dir)
	{
		info->cur_path = ft_strdup(info->home_dir);
		if (chdir(info->cur_path) == -1)
		{
			minishell->exit_code = cd_error(info,
					minishell, cmd_node->cmd_name, info->home_dir);
		}
		set_pwd_old_pwd(cmd_node, minishell, info);
		return (minishell->exit_code);
	}
	return (-1);
}

int	ft_cd(t_cmd_node *cmd_node, t_minishell *minishell)
{
	t_cd	info;

	init_t_cd(&info, cmd_node, minishell);
	if (ft_cd_nodir_arg(&info, cmd_node, minishell) != -1)
		return (minishell->exit_code);
	if (info.directory[0] == '/' || info.directory[0] == '.'
		|| (info.directory[0] == '.' && info.directory[1] == '.'))
		info.cur_path = ft_strdup(info.directory);
	if (info.cd_flag & NO_DOT_RELATIVE)
		find_curpath(&info, minishell);
	if (check_cd_option_p(&info, cmd_node, minishell) != -1)
		return (minishell->exit_code);
	if (info.cur_path[0] != '/')
		set_curpath_pwd(&info, minishell);
	if (parse_dots(&info, minishell, cmd_node) == 1)
		return (1);
	if (check_directory(&info, cmd_node, minishell) != 0)
		return (minishell->exit_code);
	if (chdir(info.cur_path) == -1)
		return (cd_error(&info, minishell, cmd_node->cmd_name, info.directory));
	set_pwd_old_pwd(cmd_node, minishell, &info);
	return (0);
}
