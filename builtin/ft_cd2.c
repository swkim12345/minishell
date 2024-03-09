/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:42:39 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/08 20:59:51 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	check_directory(t_cd *info, t_cmd_node *cmd_node, t_minishell *minishell)
{
	if (stat(info->cur_path, &info->file_stat) == 0)
	{
		if (!S_ISDIR(info->file_stat.st_mode))
		{
			minishell->exit_code = not_a_directory_error(info,
					minishell, cmd_node->cmd_name, info->directory);
		}
	}
	else
	{
		minishell->exit_code
			= cd_error(info, minishell, cmd_node->cmd_name, info->directory);
	}
	return (minishell->exit_code);
}

int	check_cd_option_p(t_cd *info, t_cmd_node *cmd_node, t_minishell *minishell)
{
	if (info->cd_flag & OPTION_FLAG)
	{
		if (chdir(info->cur_path) == -1)
		{
			if (chdir(info->directory))
			{
				minishell->exit_code = cd_error(info,
						minishell, cmd_node->cmd_name, info->cur_path);
			}
		}
		set_pwd_old_pwd(cmd_node, minishell, info);
		return (minishell->exit_code);
	}
	return (-1);
}
