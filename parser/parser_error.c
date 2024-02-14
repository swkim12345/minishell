/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:05:04 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/14 15:07:37 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	error_syntax_error(char *str)
{
	printf("minishell: syntax error near unexpoected token %s\n", str);
	
	return (TRUE);
}
