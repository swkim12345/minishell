/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:50:45 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/14 21:05:58 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_pwd(t_cmd_node *cmd_node)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	return (TRUE);
}

int main()
{
	t_cmd_node	cmd_node;
	char		*str[] = {"cd", "test_dir"};

	cmd_node.str = str;
	ft_pwd(&cmd_node);
}
