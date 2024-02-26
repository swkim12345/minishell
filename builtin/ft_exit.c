/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:44:02 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/26 10:49:32 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	ft_atol(const char *str, long *ret)
{
	int		sign;
	long	num;

	num = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		num *= 10;
		num += *str - '0';
		str++;
	}
	if (num * -1 == num || num % 10 != *(str - 1) - '0')
		return (NOTDEFINED);
	*ret = num * sign;
	return (0);
}

static int	exit_arg_check(t_cmd_node *cmd_node, t_minishell *minishell)
{
	int		index;
	long	ret;

	index = -1;
	ret = 0;
	while (cmd_node->str[1][++index])
	{
		if (!ft_isdigit(cmd_node->str[1][index]))
		{
			err_no_quote(minishell, minishell->execute_name,
				cmd_node->str[0], "numeric argument required");
			ret = 255;
			break ;
		}
	}
	if (ft_atol(cmd_node->str[1], &ret) == NOTDEFINED)
	{			
		err_no_quote(minishell, minishell->execute_name,
			cmd_node->str[0], "numeric argument required");
		ret = 255;
	}
	return (ret);
}

int	ft_exit(t_cmd_node *cmd_node, t_minishell *minishell)
{
	ft_putstr_fd("exit\n", STDERR_FILENO); //부모 프로세스에서 말할 필요가 있음.
	if (!cmd_node->str[1])
		exit(0);
	if (cmd_node->str[2])
		return (err_no_quote(minishell, minishell->execute_name,
				cmd_node->str[0], "too many arguments"));
	minishell->exit_code = exit_arg_check(cmd_node, minishell);
	exit(minishell->exit_code);
}
