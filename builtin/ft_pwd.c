/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:50:45 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/26 13:54:47 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_pwd(t_cmd_node *node, t_minishell *minishell)
{
	//fuck fuck
	(void) node;
	
	printf("%s\n", minishell->cwd);
	return (FUNC_SUC);
}
