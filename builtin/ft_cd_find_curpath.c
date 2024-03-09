/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_find_curpath.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:05:25 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 23:07:35 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	check_end_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == '\\')
		return (1);
	return (0);
}

static char	*check_slash_cat(char *str1, t_cd *info)
{
	char	*temp_str;

	if (check_end_slash(str1) == FALSE)
	{
		temp_str = easy_cat(str1, "/");
		info->check_str = easy_cat(temp_str, info->directory);
		free(temp_str);
	}
	else
		info->check_str = easy_cat(str1, info->directory);
	return (info->check_str);
}

static int	check_cdpath_dir(t_cd *info, t_minishell *minishell)
{
	if (stat(info->check_str, &info->file_stat) == 0)
	{
		if (S_ISDIR(info->file_stat.st_mode))
		{
			free_2d_str(info->path_arr);
			info->cur_path = info->check_str;
			return (TRUE);
		}
	}
	else if (errno != ENOENT)
	{
		free(info->check_str);
		free_2d_str(info->path_arr);
		shell_error(minishell, info->execute_name, info->directory);
	}
	return (FALSE);
}

static int	check_cdpath(t_cd *info, t_minishell *minishell)
{
	int		i;

	info->path_arr = ft_split(info->cdpath, ':');
	i = -1;
	while (info->path_arr[++i])
	{
		check_slash_cat(info->path_arr[i], info);
		if (check_cdpath_dir(info, minishell) == TRUE)
			return (EXIT_SUCCESS);
		free(info->check_str);
	}
	free_2d_str(info->path_arr);
	return (EXIT_SUCCESS);
}

void	find_curpath(t_cd *info, t_minishell *minishell)
{
	info->cd_flag |= NO_DOT_RELATIVE;
	if (info->cdpath)
		check_cdpath(info, minishell);
	if (!info->cur_path)
		find_local_dir(info, minishell);
}
