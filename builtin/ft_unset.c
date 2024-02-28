/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/28 13:01:22 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_unset(t_cmd_node *cmd_node, t_minishell *minishell)
{
	int		index;
	char	*env;
	char	**envp;

	index = 0;
	while (cmd_node->str[++index])
	{
		envp = string_parser(cmd_node->str[index], minishell);
		env = ft_strdup(envp[0]);
		free_2d_str(envp);
		minishell->error = set_error_msg(minishell->execute_name,
				cmd_node->cmd_name,
				env, "not a valid identifier");
		if (ft_isalpha(env[0]) && env[0] != '_')
			return (print_error_msg(minishell->error, 1, FALSE));
		free_error(minishell->error);
		if (ft_unsetenv(minishell->export, cmd_node->str[index]) == FUNC_FAIL)
			return (FUNC_FAIL);
		if (ft_unsetenv(minishell->env, cmd_node->str[index]) == FUNC_FAIL)
			return (FUNC_FAIL);
	}
	return (FUNC_SUC);
}
