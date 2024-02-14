/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:15:20 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/14 21:27:33 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_exit(t_cmd_node *cmd_node)
{
	unsigned short	exit_status;

	exit_status = (unsigned short)ft_atoi(cmd_node->str[1]);
	exit(exit_status);
}

int main()
{
	int	pid;
	pid_t	t;
	char	*str[] = {"exit", "100"};
	t_cmd_node	*cmd_node;


	
	pid = fork();
	//parent
	if (pid)
		pid = wait(&pid);
	else
	{
		cmd_node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
		cmd_node->str = str;
		ft_exit(cmd_node);
	}
	printf("parent : %d", pid);
	return (0);
}
