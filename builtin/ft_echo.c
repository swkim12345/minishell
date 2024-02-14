/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:28:52 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/13 20:20:31 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <fcntl.h>
#include <unistd.h>

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
	char	*first_str;

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

int main(int argc, char **argv, char **envp)
{
	// atexit(check);
	t_minishell minishell;

	minishell.exit_code = 0;

	(void) argc;
	char *input_str = readline(0);
	char **cmd_str = string_parser(input_str, &minishell);
	int i = 0;
	int fd = open("test", O_RDONLY);

	printf("input_str: %s\n", input_str);
	while (cmd_str[i])
	{
		printf("parsed_str: [%s]\n", cmd_str[i]);
		i++;
	}
	printf("echo result: ------------\n");
	t_cmd_node	cmd_node;
	cmd_node.str = cmd_str;
	ft_echo(&cmd_node);
}