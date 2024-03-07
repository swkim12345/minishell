/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:11:23 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/07 20:11:51 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	err_token_finder(char *ptr, int index)
{
	while (ptr[index] != '\0')
	{
		if (ft_isspace(ptr[index]) == TRUE)
			break ;
		else if (ptr[index] == '\"' || ptr[index] == '\'')
			return (index);
		else if (ptr[index] == '(')
			return (index);
		else if (ptr[index] == '&')
		{
			if (ptr[index + 1] == '&')
				return (index + 1);
			else
				return (index);
		}
		else if (ptr[index] == '|')
		{
			if (ptr[index + 1] == '|')
				return (index + 1);
			else
				return (index);
		}
		else if (ptr[index] == '<' || ptr[index] == '>')
		{
			if (ptr[index + 1] == ptr[index])
				return (index + 1);
			else
				return (index);
		}
		index++;
	}
	return (index);
}
