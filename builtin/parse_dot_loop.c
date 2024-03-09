/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dot_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:56:51 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/09 12:58:26 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	parse_dots_check_prefix_dir(t_cmd_node *cmd_node, t_cd *info,
			t_str_list *stack, t_minishell *minishell)
{
	info->check_str = stack_to_str(stack);
	if (stat(info->check_str, &info->file_stat) == 0)
	{
		if (!S_ISDIR(info->file_stat.st_mode))
		{
			free_str_stack(stack);
			free(info->check_str);
			return (not_a_directory_error(info, minishell,
					cmd_node->cmd_name, info->home_dir));
		}
	}
	else
	{
		free_str_stack(stack);
		free(info->check_str);
		return (cd_error(info, minishell,
				info->execute_name, info->directory));
	}
	return (0);
}

static void	parse_dots_dbl_dot(t_cmd_node *cmd_node, t_cd *info,
			t_str_list *stack, t_minishell *minishell)
{
	t_str_node	*cur;

	// parse_dots_check_prefix_dir(cmd_node, info, stack, minishell);
	info->i += 2;
	info->start += 3;
	if (stack->size > 1)
	{
		cur = pop(stack);
		free(cur->str);
		free(cur);
	}
	free(info->check_str);
}

static void	add_str_path_node(t_cd *info, t_str_list *stack)
{
	info->check_str
		= ft_substr(info->cur_path, info->start, info->i - info->start + 1);
	enqueue(stack, create_node(info->check_str));
	info->start = info->i + 1;
}

int	parse_dot_loop(t_cmd_node *cmd_node, t_cd *info,
		t_str_list *stack, t_minishell *minishell)
{
	while (info->cur_path[info->i])
	{
		if (ft_strncmp(&info->cur_path[info->i], "./", 2) == 0
			&& info->i - info->start == 0)
		{
			info->start += 2;
			info->i++;
		}
		else if (ft_strncmp(&info->cur_path[info->i], "../", 3) == 0
			&& info->i - info->start == 0)
		{
			if (parse_dots_check_prefix_dir(cmd_node, info, stack, minishell))
				return (1);
			parse_dots_dbl_dot(cmd_node, info, stack, minishell);
		}
		else if (info->cur_path[info->i] == '/'
			&& (info->i == 0 || info->i - info->start != 0))
			add_str_path_node(info, stack);
		else if (info->cur_path[info->i] == '/' && info->i - info->start == 0)
			info->start += 1;
		info->i++;
	}
	return (0);
}
