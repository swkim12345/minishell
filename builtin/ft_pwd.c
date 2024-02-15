/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:50:45 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/15 16:26:54 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_pwd(t_minishell *minishell)
{
	//printf("%s\n",minishell->cur_dir) //t_minishell업데이트 이후 설정 필요.
	return (TRUE);
}

int main()
{
	t_cmd_node	cmd_node;
	char		*str[] = {"cd", "test_dir"};

	cmd_node.str = str;
	ft_pwd(&cmd_node);
}
