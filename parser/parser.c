/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:46:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/28 20:14:41 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	bracket_parser(char *str, int index, int str_flag, t_minishell *minishell)
{
	char	*ptr;
	int		ret;

	ptr = &str[index];
	if (*ptr == '(')
	{
		if (str_flag == TRUE)
			return (syntax_err_message(ptr, index, -1, minishell));
		else
		{
			ret = bracket_finder(ptr);
			if (ret == NOTDEFINED)
				return (syntax_err_message(ptr, index, -1, minishell));
			else
				return (ret);
		}
	}
	return (index);
}

static int	pipe_recurv_parser(t_ast_node *head, int str_end,
			int dup_str_start, t_minishell *minishell)
{
	char	*ptr;
	char	*tmp;
	int		size;

	ptr = head->cmd_node->str[0];
	if (str_end <= 0)
		return (syntax_err_message(ptr, dup_str_start, -1, minishell));
	size = ft_strlen(ptr);
	head->next_ast_node = init_ast_node(CMDNODE);
	tmp = ft_substr(ptr, dup_str_start, size);
	head->next_ast_node->cmd_node->str = \
		init_doub_char(&tmp, 1);
	free(tmp);
	tmp = ft_substr(ptr, 0, str_end);
	free_2d_str(head->cmd_node->str);
	head->cmd_node->str = \
		init_doub_char(&tmp, 1);
	free(tmp);
	if (recurv_parser(head->next_ast_node, minishell) == FUNC_FAIL)
		return (FUNC_FAIL);
	if (recurv_parser(head, minishell) == FUNC_FAIL)
		return (FUNC_FAIL);
	return (FUNC_SUC);
}

static int	split_recurv_parser(t_ast_node *head, int str_end,
			int dup_str_start, t_minishell *minishell)
{
	char	*ptr;
	char	*tmp;
	int		size;

	ptr = head->cmd_node->str[0];
	if (str_end <= 0)
	{
		head->err_flag = TRUE;
		syntax_err_message(ptr, dup_str_start, -1, minishell);
	}
	size = ft_strlen(ptr);
	if (ft_strncmp(&ptr[str_end + 1], "&&", ft_strlen("&&")) == 0)
		head->flag = AND_FLAG;
	else if (ft_strncmp(&ptr[str_end + 1], "||", ft_strlen("||")) == 0)
		head->flag = OR_FLAG;
	else
		head->flag = NO_FLAG;
	head->left_node = init_ast_node(CMDNODE);
	head->right_node = init_ast_node(CMDNODE);
	tmp = ft_substr(ptr, 0, str_end);
	head->left_node->cmd_node->str = \
		init_doub_char(&tmp, 1);
	free(tmp);
	tmp = ft_substr(ptr, dup_str_start, size);
	head->right_node->cmd_node->str = \
		init_doub_char(&tmp, 1);
	free(tmp);
	free_cmd_node(&(head->cmd_node));
	if (recurv_parser(head->left_node, minishell) == FUNC_FAIL)
		return (FUNC_FAIL);
	if (recurv_parser(head->right_node, minishell) == FUNC_FAIL)
		return (FUNC_FAIL);
	return (FUNC_SUC);
}

int	recurv_parser(t_ast_node *head, t_minishell *minishell)
{
	int			index;
	int			tmp;
	char		*ptr;

	index = -1;
	ptr = head->cmd_node->str[0]; 
	while (ptr[++index])
	{
		index += skip_space(&ptr[index]);
		if (ptr[index] == '\"' || ptr[index] == '\'')
		{
			tmp = finder(&ptr[index + 1], ptr[index]);
			if (tmp == NOTDEFINED)
			{
				head->err_flag = TRUE;
				syntax_err_message(ptr, index + 1, -1, minishell);
			}
			index += tmp + 1;
			continue ;
		}
		if (ptr[index] == '(')
		{
			tmp = bracket_finder(&ptr[index + 1]);
			if (tmp == NOTDEFINED)
			{
				head->err_flag = TRUE;
				syntax_err_message(ptr, index + 1, -1, minishell);
			}
			index += tmp;
			continue ;
		}
		if (ptr[index] == '|' && ptr[index + 1] == '|')
			return (split_recurv_parser(head, index - 1, index + 2, minishell));
		if (ptr[index] == '&' && ptr[index + 1] == '&')
			return (split_recurv_parser(head, index - 1, index + 2, minishell));
		if (ptr[index] == '|')
			return (pipe_recurv_parser(head, index - 1, index + 1, minishell));
	}
	printf("parser ptr: %s\n", ptr);
	tmp = lexar(head, minishell);
	if (tmp == FUNC_FAIL)
		return (FUNC_FAIL);
	return (FUNC_SUC);
}

int	read_heredoc(t_minishell *minishell, t_redirection *redirection
	, t_tmp_file *tmp_file)
{
	int			fd;
	char		*line;

	fd = tmp_file->fd;
	if (fd == -1)
		shell_error(minishell, "heredoc", 0);
	while (1)
	{
		line = readline("> ");
		if (!line || str_equal(line, redirection->str))
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	return (0);
}

t_ast_node	*parser(char *str, t_minishell *minishell)
{
	t_ast_node	*ret;
	int			err;

	ret = init_ast_node(CMDNODE);
	ret->cmd_node->str = init_doub_char(&str, 1);
	err = recurv_parser(ret, minishell);
	if (err == FUNC_FAIL)
	{
		free_ast_tree(ret);
		return (NULL);
	}
	return (ret);
}
