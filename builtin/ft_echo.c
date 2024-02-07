/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:28:52 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/07 21:53:59 by minsepar         ###   ########.fr       */
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

void	free_2d_str(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr[i]);
	free(arr);
}

void	check()
{
	system("leaks a.out");
}

int	ft_echo(t_cmd_node *cmd_node)
{
	int		nflag;
	char	*first_str;

	first_str = cmd_node->str[1];
	nflag = 0;
	if (str_equal(first_str, "-n"))
		nflag = 1;
	print_echo(cmd_node->str, nflag);
	free_2d_str(cmd_node->str);
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

int main(int argc, char **argv, char **envp)
{
	// atexit(check);
	(void) argc;
}