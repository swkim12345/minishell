/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:23:12 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/21 17:19:38 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_export(t_cmd_node *cmd_node, t_minishell *minishell)
{
	int		index;
	int		ret;
	char	**env;
	char	*key;
	char	*value;

	index = 0;
	if (cmd_node->cmd_name[1] == NULL)
	{
		env = tree_to_char(minishell->export);
		while (env[index])
		{
			printf("declare -x %s\n", env[index]);
			free(env[index]);
			index++;
		}
		free(env);
		return (FUNC_SUC);
	}
	while (cmd_node->str[++index])
	{
		if (!ft_isalpha(cmd_node->str[index][0]))
			return (err_msg(minishell->execute_name, cmd_node->str[0],
			 cmd_node->str[index], "not a valid identifier"));
		ret = parse_env(cmd_node->str[index], &key, &value);
		if (ret == FUNC_FAIL)
		return (err_msg(minishell->execute_name, cmd_node->str[0],
			 cmd_node->str[index], "not a valid identifier"));
		ret = ft_setexport(&minishell->export, key, value);
		if (ret == FUNC_FAIL)
			return (FUNC_FAIL);
		if (value)
			ret = ft_setenv(&minishell->env, key, value);
		index++;
	}
	return (FUNC_SUC);
}
