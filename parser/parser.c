/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:46:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/01 11:49:12 by sunghwki         ###   ########.fr       */
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

char	*get_error_token(char *ptr, int index)
{
	char	*ret;
	int		start;
	int		end;

	index += skip_space(&ptr[index]);
	start = index;
	while (ptr[index] || ft_isspace(ptr[index]) == FALSE || ptr[index] == '|' || ptr[index] == '&')
		index++;
	end = index;
	ret = ft_substr(ptr, start, end - start);
	return (ret);
}

static void	split_node(int end, int new_start, t_ast_node *node, int new_node_flag)
{
	char		*ptr;
	char		*tmp;
	t_ast_node	*old_node;
	t_ast_node	*new_node;
	
	old_node = node;
	new_node = NULL;
	ptr = ft_strdup(node->cmd_node->str[0]);
	if (new_node_flag & LEFTNODE)
	{
		node->left_node = init_ast_node(CMDNODE);
		old_node = node->left_node;
	}
	if (new_node_flag & RIGHTNODE)
	{
		node->right_node = init_ast_node(CMDNODE);
		new_node = node->right_node;
	}
	if (new_node_flag & NEXTNODE)
	{
		node->next_ast_node = init_ast_node(CMDNODE);
		new_node = node->next_ast_node;
	}
	tmp = ft_substr(ptr, 0, end);
	free_2d_str(node->cmd_node->str);
	node->cmd_node->str = NULL;
	old_node->cmd_node->str = init_doub_char(&tmp, 1);
	free(tmp);
	tmp = ft_substr(ptr, new_start, ft_strlen(&ptr[new_start]));
	new_node->cmd_node->str = init_doub_char(&tmp, 1);
	free(tmp);
	free(ptr);
}

static int	pipe_recurv_parser(t_ast_node *head, int str_end,
			int dup_str_start, t_minishell *minishell)
{
	char	*ptr;

	ptr = head->cmd_node->str[0];
	if (str_end <= 0)
		return (syntax_err_message(ptr, dup_str_start, -1, minishell));
	split_node(str_end, dup_str_start, head, NEXTNODE);
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

	ptr = head->cmd_node->str[0];
	if (str_end <= 0)
	{
		head->err_flag = TRUE;
		return (syntax_err_message(ptr, dup_str_start, -1, minishell));
	}
	if (ft_strncmp(&ptr[str_end + 1], "&&", ft_strlen("&&")) == 0)
		head->flag = AND_FLAG;
	else if (ft_strncmp(&ptr[str_end + 1], "||", ft_strlen("||")) == 0)
		head->flag = OR_FLAG;
	else
		head->flag = NO_FLAG;
	split_node(str_end, dup_str_start, head, LEFTNODE | RIGHTNODE);
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
	int			str_flag;
	char		*ptr;

	index = -1;
	str_flag = FALSE;
	ptr = head->cmd_node->str[0]; 
	while (ptr[++index])
	{
		index += skip_space(&ptr[index]); //error occur
		if (ptr[index] == '\0')
			break ;
		if (ptr[index] == '\"' || ptr[index] == '\'')
		{
			tmp = finder(&ptr[index + 1], ptr[index]);
			if (tmp == NOTDEFINED)
			{
				head->err_flag = TRUE;
				return (syntax_err_message(ptr, index + 1, -1, minishell));
			}
			index += tmp + 1;
			continue ;
		}
		if (ptr[index] == '(') //subshell not found error
		{
			tmp = bracket_finder(&ptr[index]);
			if (tmp + index == NOTDEFINED || tmp == index + 1)
			{
				head->err_flag = TRUE;
				return (syntax_err_message(&ptr[index], tmp, -1, minishell));
			}
			if (str_flag == TRUE)
			{
				head->err_flag = TRUE;
				return (syntax_err_message(&ptr[index + 1], tmp - 1, -1, minishell));
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
		str_flag = TRUE;
	}
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
		printf("read_heredoc_str : %s\n", redirection->str);
		if (!line || str_equal(line, redirection->str))
			break ;
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	return (FUNC_SUC);
}

t_ast_node	*parser(char *str, t_minishell *minishell)
{
	t_ast_node	*ret;
	int			err;

	minishell->tmp_file_counter = 0;
	ret = init_ast_node(CMDNODE);
	ret->cmd_node->str = init_doub_char(&str, 1);
	err = recurv_parser(ret, minishell);
	if (err == FUNC_FAIL)
		return (NULL);
	return (ret);
}
