/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:11:23 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/08 14:04:27 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexar.h"

int	err_token_finder(char *ptr, int index)
{
	while (ptr[index] != '\0')
	{
		if (ft_isspace(ptr[index]) == TRUE)
			break ;
		else if (ptr[index] == '\"' || ptr[index] == '\'' || ptr[index] == '(')
			return (++index);
		else if (ptr[index] == '&' || ptr[index] == '|')
		{
			if (ptr[index] == ptr[index + 1])
				return (++index + 1);
			else
				return (++index);
		}
		else if (ptr[index] == '<' || ptr[index] == '>')
		{
			if (ptr[index + 1] == ptr[index])
				return (++index + 1);
			else
				return (++index);
		}
		index++;
	}
	return (index);
}
