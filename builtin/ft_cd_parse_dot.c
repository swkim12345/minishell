/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_parse_dot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:51:19 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/08 15:18:07 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	init_parse_dot_var(t_cd *info)
{
	info->i = 0;
	info->start = 0;
}

static int	dbl_dot_check_root(t_cmd_node *cmd_node, t_cd *info,
		t_str_list *stack, t_minishell *minishell)
{
	t_str_node	*cur;

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
	cur = pop(stack);
	free(info->check_str);
	free(cur->str);
	free(cur);
	return (0);
}

static void	clear_end_slash(t_cd *info, t_str_list *stack)
{
	info->i = ft_strlen(stack->tail->str) - 1;
	if (stack->size > 1 && stack->tail->str[info->i] == '/')
		stack->tail->str[info->i] = 0;
	free(info->cur_path);
	info->cur_path = stack_to_str(stack);
	free_str_stack(stack);
}

int	parse_dots(t_cd *info, t_minishell *minishell, t_cmd_node *cmd_node)
{
	t_str_list	stack;

	init_parse_dot_var(info);
	ft_memset(&stack, 0, sizeof(t_str_list));
	if (parse_dot_loop(cmd_node, info, &stack, minishell))
		return (1);
	if (info->i - info->start == 2 && info->cur_path[info->i - 2] == '.'
		&& info->cur_path[info->i - 1] == '.')
	{
		if (stack.size > 1)
		{
			if (dbl_dot_check_root(cmd_node, info, &stack, minishell))
				return (1);
		}
	}
	else if (info->cur_path[info->i - 1] != '/'
		&& !(info->i - info->start == 1 && info->cur_path[info->i - 1] == '.'))
	{
		info->check_str
			= ft_substr(info->cur_path, info->start, info->i - info->start + 1);
		enqueue(&stack, create_node(info->check_str));
	}
	clear_end_slash(info, &stack);
	return (0);
}
