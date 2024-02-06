/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:28:52 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/06 22:15:44 by minsepar         ###   ########.fr       */
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

void	print_echo(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i != 0)
			printf(" ");
		printf("%s", str[i]);
	}
}

void	free_2d_str(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	check()
{
	
}

int ft_echo(char *str)
{
	t_str_list	str_list;

	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		parse_single_word(&str, &str_list);
	}
	char **str_arr = list_to_char_arr(&str_list);
	print_echo(str_arr);
	free_2d_str(str_arr);
	return (1);
}

int main()
{
    ft_echo("\\t");
}