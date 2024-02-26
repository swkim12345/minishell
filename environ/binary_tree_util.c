/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:52:19 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/26 19:31:46 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static void	parse_value(char *env, char **value, int size, int index)
{
	if (ft_strlen(env) != (size_t)size)
	{
		if (env[index + 1] == '\0')
		{
			*value = (char *)malloc(sizeof(char) * 1);
			*value[0] = '\0';
		}
		else
			*value = ft_strdup(&env[index + 1]);
		env[index] = '=';
	}
	else
		*value = NULL;
}

int	parse_env(char *env, char **key, char **value)
{
	int		index;
	int		size;

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
	*key = ft_strdup(env);
	parse_value(env, value, size, index);
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

char	*key_value_to_str(t_tree_node *node)
{
	char	*ret;
	char	*tmp;

	if (node->value == NULL)
		ret = ft_strdup(node->key);
	else if (node->value[0] == '\0')
		ret = ft_strjoin(node->key, "=\"\"");
	else
	{
		tmp = ft_strjoin(node->key, "=\"");
		ret = ft_strjoin(tmp, node->value);
		free(tmp);
		tmp = ft_strdup(ret);
		free(ret);
		ret = ft_strjoin(tmp, "\"");
		free(tmp);
	}
	return (ret);
}
