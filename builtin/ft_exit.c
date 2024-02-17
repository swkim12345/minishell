/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:44:02 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/16 12:46:44 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_atol(const char *str, long *ret)
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

int	ft_exit(t_cmd_node *cmd_node, t_minishell *minishell)
{
	long	exit_status;
	long			size;
	long			index;

	index = -1;
	printf("exit\n");
	if (!cmd_node->str[1])
		exit(0);
	if (!cmd_node->str[2])
	{
		printf("bash exit: too many arguments\n"); //error 메세지 수정 필요. 간이로 설정함.
		return (FUNC_FAIL);
	}
	while (cmd_node->str[1][++index] != '\0')
	{
		if (!ft_isdigit(cmd_node->str[1][index]))
		{
			printf("bash exit: %s: numeric argument required\n",
			cmd_node->str[1]);
			exit(255);
		}
	}
	if (ft_atol(cmd_node->str[1], &exit_status) == NOTDEFINED)
	{			
		printf("bash exit: %s: numeric argument required\n", cmd_node->str[1]);
		exit(255);
	}
	minishell->exit_code = exit_status;
	exit(exit_status);
}

int main()
{
	int	pid;
	pid_t	t;
	char	*str[] = {"exit", "100000000000000000000000000"};
	t_cmd_node	*cmd_node;
	t_minishell mini;


	
	pid = fork();
	//parent
	if (pid)
		pid = wait(&pid);
	else
	{
		cmd_node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
		cmd_node->str = str;
		ft_exit(cmd_node, &mini);
	}
	printf("parent : %d", pid);
	return (0);
}
