/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:52:19 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/27 14:07:48 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static char	*parse_value(char *env, int size, int index, t_minishell *minishell)
{
	char	*value;
	char	*tmp;
	char	**tmp_value;

	if (ft_strlen(env) != (size_t)size)
	{
		if (env[index + 1] == '\0')
		{
			value = (char *)malloc(sizeof(char) * 1);
			value[0] = '\0';
		}
		else
		{
			tmp = ft_strdup(&env[index + 1]);
			tmp_value = string_parser(tmp, minishell);
			value = ft_strdup(tmp_value[0]);
			free(tmp);
			free_doub_char(tmp_value);
		}
		env[index] = '=';
	}
	else
		value = NULL;
	return (value);
}

int	parse_env(char *env, char **key, char **value, t_minishell *minishell)
{
	int		index;
	int		size;
	char	**tmp_value;

	index = -1;
	size = ft_strlen(env);
	while (env[++index])
	{
		if (env[index] == '=')
		{
			if (index == 0)
				return (FUNC_FAIL);
			env[index] = '\0';
			break ;
		}
	}
	tmp_value = string_parser(env, minishell);
	*key = ft_strdup(tmp_value[0]);
	free_doub_char(tmp_value);
	*value = parse_value(env, size, index, minishell);
	return (FUNC_SUC);
}

void	exchange_node_key_value(t_tree_node *n, t_tree_node *t)
{
	char	*key;
	char	*value;

	key = n->key;
	value = n->value;
	n->key = t->key;
	n->value = t->value;
	t->key = key;
	t->value = value;
}

char	*key_value_to_str(t_tree_node *node, int quote_flag)
{
	char	*ret;
	char	*tmp;

	if (node->value == NULL)
		ret = ft_strdup(node->key);
	else if (node->value[0] == '\0')
		ret = ft_strjoin(node->key, "=\"\"");
	else if (quote_flag)
	{
		tmp = ft_strjoin(node->key, "=\"");
		ret = ft_strjoin(tmp, node->value);
		free(tmp);
		tmp = ft_strjoin(ret, "\"");
		free(ret);
		ret = tmp;
	}
	else
	{
		tmp = ft_strjoin(node->key, "=");
		ret = ft_strjoin(tmp, node->value);
		free(tmp);
	}
	return (ret);
}
