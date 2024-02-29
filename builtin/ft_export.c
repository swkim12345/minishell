/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:23:12 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/29 11:03:22 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static	int	print_export(t_minishell *minishell)
{
	char	**env;
	int		index;

	index = 0;
	env = ft_charenv(minishell->export, TRUE);
	while (env[index])
	{
		printf("declare -x %s\n", env[index]);
		free(env[index]);
		index++;
	}
	free(env);
	env = NULL;
	return (FUNC_SUC);
}

static	int	put_env(t_cmd_node *cmd_node, t_minishell *minishell, int index)
{
	char	*key;
	char	*value;
	
	key = NULL;
	value = NULL;
	minishell->error = set_error_msg(minishell->execute_name,
			cmd_node->str[0], cmd_node->str[index], "not a valid identifier");
	if (parse_env(cmd_node->str[index], &key, &value, minishell) == FUNC_FAIL)
	{
			print_error_msg(minishell->error, 1, TRUE);
			return (FUNC_SUC);
	}
	if (ft_setenv(minishell->export, key, value) == FUNC_FAIL)
	{
		free(key);
		free(value);
		free_error(minishell->error);
		return (FUNC_FAIL);
	}
	if (value && *value)
		ft_setenv(minishell->env, key, value);
	free(key);
	free(value);
	free_error(minishell->error);
	return (FUNC_SUC);
}

int	ft_export(t_cmd_node *cmd_node, t_minishell *minishell)
{
	int		index;

	index = 0;
	if (!cmd_node || !cmd_node->str || !cmd_node->str[1])
		return (print_export(minishell));
	while (cmd_node->str[++index])
	{
		if (put_env(cmd_node, minishell, index) == FUNC_FAIL)
			return (FUNC_FAIL);
	}
	return (FUNC_SUC);
}
