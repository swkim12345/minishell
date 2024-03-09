/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:44:02 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/08 21:09:23 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	ft_atol(const char *str, long *ret)
{
	int			sign;
	long long	num;
	long long	temp_num;

	num = 0;
	sign = 1;
	str += skip_space((char *)str);
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		temp_num = num;
		num *= 10;
		num += *str - '0';
		if (temp_num > num)
		{
			if (!str[1] && *str - '0' == 8 && sign == -1)
				break ;
			return (NOTDEFINED);
		}
		str++;
	}
	*ret = num * sign;
	return (0);
}

static int	exit_arg_check(t_cmd_node *cmd_node, t_minishell *minishell)
{
	int		index;
	long	ret;
	t_error	*err;

	index = 0;
	ret = 0;
	err = set_error_msg(minishell->execute_name, cmd_node->str[0],
			cmd_node->str[1], "numeric argument required");
	cmd_node->str[1] = eof_parser(cmd_node->str[1]);
	if (cmd_node->str[1][index] == '+' || cmd_node->str[1][index] == '-')
		index++;
	if (!cmd_node->str[1][index])
		return (print_error_msg(err, 255, 0));
	while (cmd_node->str[1][index])
	{
		if (!ft_isdigit(cmd_node->str[1][index]))
			exit(print_error_msg(err, 255, 0));
		index++;
	}
	if (ft_atol(cmd_node->str[1], &ret) == NOTDEFINED)
		exit(print_error_msg(err, 255, 0));
	free_error(err);
	return (ret);
}

int	ft_exit(t_cmd_node *cmd_node, t_minishell *minishell)
{
	t_error	*err;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!cmd_node->str[1])
	{
		free_t_minishell(minishell);
		exit(minishell->exit_code);
	}
	minishell->exit_code = 255;
	minishell->exit_code = exit_arg_check(cmd_node, minishell);
	if (cmd_node->str[2])
	{
		err = set_error_msg(minishell->execute_name, cmd_node->str[0],
				NULL, "too many arguments");
		print_error_msg(err, 1, 0);
		return (FUNC_FAIL);
	}
	free_t_minishell(minishell);
	exit(minishell->exit_code);
}
