/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:52:19 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/06 21:33:50 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static char	*parse_value(char *env, int size, int index, t_minishell *minishell)
{
	char	*value;
	char	**dup_str;
	char	*tmp;

	if (ft_strlen(env) != (size_t)size)
	{
		if (env[index + 1] == '\0')
			value = (char *)ft_calloc(sizeof(char), 1);
		else
		{
			tmp = ft_strdup(&env[index + 1]);
			dup_str = string_parser(tmp, minishell);
			if (dup_str[0])
				value = ft_strdup(dup_str[0]);
			else
				value = NULL;
			free_2d_str(dup_str);
			free(tmp);
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
	char	**tmp;

	index = -1;
	size = ft_strlen(env);
	while (env[++index])
	{
		if (skip_space(&env[index]))
		{
			return (FUNC_FAIL);
		}
		if (env[index] == '=')
		{
			if (index == 0)
				return (FUNC_FAIL);
			env[index] = '\0';
			break ;
		}
	}
	tmp = string_parser(env, minishell);
	*key = ft_strdup(tmp[0]);
	free_2d_str(tmp);
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

//char	*key_value_to_str(t_tree_node *node, int quote_flag)
//{
//	char	*ret;
//	char	*tmp;

//	if (node->value == NULL)
//		return (ft_strdup(node->key));
//	if (quote_flag)
//	{
//		if (node->value[0] == '\0')
//			return (ft_strjoin(node->key, "=\"\""));
//		else
//		{
//			tmp = ft_strjoin(node->key, "=\"");
//			ret = ft_strjoin(tmp, node->value);
//			free(tmp);
//			tmp = ft_strjoin(ret, "\"");
//			free(ret);
//			ret = tmp;
//		}
//	}
//	else
//	{
//		tmp = ft_strjoin(node->key, "=");
//		if (node->value[0] == '\0')
//			return (tmp);
//		else
//		{
//			ret = ft_strjoin(tmp, node->value);
//			free(tmp);
//		}
//	}
//	return (ret);
//}

char	*key_value_to_str(t_tree_node *node, int quote_flag)
{
	char	*ret;
	char	*tmp;

	if (node->value == NULL)
		ret = ft_strdup(node->key);
	else if (quote_flag)
	{
		if (node->value[0] == '\0')
			return (ft_strjoin(node->key, "=\"\""));
		else
		{
			tmp = ft_strjoin(node->key, "=\"");
			ret = ft_strjoin(tmp, node->value);
			free(tmp);
			tmp = ft_strjoin(ret, "\"");
			free(ret);
			ret = tmp;
		}
	}
	else
	{
		if (node->value[0] == '\0')
			return (ft_strjoin(node->key, "="));
		else
		{
			tmp = ft_strjoin(node->key, "=");
			ret = ft_strjoin(tmp, node->value);
			free(tmp);
		}
	}
	return (ret);
}

char 	*env_parse_value(char *str, t_minishell *minishell)
{
	t_parse_str	parse_str;
	t_str_list	str_list;

	init_parse_str(&parse_str);
	while (*str)
	{
		if (*str == '\'')
			parse_single_quote(&parse_str, &str);
		else if (*str == '\"')
			parse_double_quote(&str_list, &parse_str, &str, minishell);
		else if (*str == '$')
			parse_env_var(&str_list, &parse_str, &str, minishell);
		else
			parse_single_char(&str_list, &parse_str, &str, minishell);
	}
	return (parse_str.str);
}
