/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:50:45 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/25 15:58:23 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_pwd(t_cmd_node *node, t_minishell *minishell)
{
	printf("%s\n", minishell->cwd);
	return (FUNC_SUC);
}
