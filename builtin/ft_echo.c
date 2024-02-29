/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:28:52 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/29 13:28:15 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	print_echo(char **str, int nflag)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i != 0)
			printf(" ");
		printf("%s", str[i]);
	}
	if (!nflag)
		printf("\n");
}

int	is_nflag(char *str)
{
	if (ft_strlen(str) > 1 && str[0] == '-' && str[1] == 'n')
		str += 2;
	else
		return (0);
	while (str && *str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int	ft_echo(t_cmd_node *cmd_node)
{
	int		nflag;
	int		index;

	index = 1;
	nflag = 0;
	while (cmd_node->str[index])
	{
		if (is_nflag(cmd_node->str[index]))
			nflag = 1;
		else
			break ;
		index++;
	}
	print_echo(&cmd_node->str[index], nflag);
	return (0);
}

void	print_argv(char **argv, int argc)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		printf("%s ", argv[i]);
	}
}
