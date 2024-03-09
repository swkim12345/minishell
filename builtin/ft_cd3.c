/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:15:09 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/09 13:38:52 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	find_local_dir(t_cd *info, t_minishell *minishell)
{
	char	*temp_str;

	temp_str = easy_cat(minishell->cwd, "/");
	info->check_str = easy_cat(temp_str, info->directory);
	if (stat(info->check_str, &info->file_stat) == 0)
		info->cur_path = info->check_str;
	else
	{
		info->cur_path = ft_strdup(info->directory);
		free(info->check_str);
	}
	free(temp_str);
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

void	set_pwd_old_pwd(t_cmd_node *cmd_node,
			t_minishell *minishell, t_cd *info)
{
	char	*old_pwd;

	old_pwd = minishell->cwd;
	if (info->cd_flag & OPTION_FLAG)
	{
		minishell->cwd = getcwd(0, 0);
		if (!minishell->cwd)
		{
			minishell->exit_code
				= builtin_error(minishell, cmd_node->cmd_name, 0);
		}
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
