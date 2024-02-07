/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:28:52 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/06 23:07:16 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		ft_isspace(int c)
{
	if (c >= 9 && c <= 12)
		return (1);
	if (c == 32)
		return (1);
	return (0);
}

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

int ft_echo(char *str, int nflag)
{
	t_str_list	str_list;

	init_str_list(&str_list);
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		parse_single_word(&str, &str_list);
	}
	char **str_arr = list_to_char_arr(&str_list);
	print_echo(str_arr, nflag);
	free_2d_str(str_arr);
	return (1);
}

void	print_argv(char **argv, int argc)
{
	int i;

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
    ft_echo("a    b    c", 0);
	print_argv(argv, argc);
}