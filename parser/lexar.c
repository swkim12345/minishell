/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:22:56 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/28 20:02:30 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//trim redirection
// shift index, error found : NOTDEFINED
//static char	*lexar_redirect(t_ast_node *node, int index, t_minishell *minishell)
//{
//	char		*ptr;
//	int			start;
//	t_tmp_file	*tmp_file;
//	t_redirection	*red;

//	ptr = node->cmd_node->str[0]; 
//	red = (t_redirection *)malloc(sizeof(t_redirection));
//	ft_memset((void *)red, 0, sizeof(t_redirection));
//	redirect_node_push(node, red);
//	if (ptr[index] == '<')
//	{
//		printf("ptr[%d]: %c\n", index, ptr[index]);
//		if (ptr[index + 1] == '<')
//		{
//			red->flag = DB_LT_SIGN;
//			index++;
//		}
//		else
//			red->flag = LT_SIGN;
//	}
//	else
//	{
//		if (ptr[index + 1] == '>')
//		{
//			red->flag = DB_GT_SIGN;
//			index++;
//		}
//		else
//			red->flag = GT_SIGN;
//	}
//	index++;
//	//trim redirection
//	//ptr = ft_strjoin(ptr, &ptr[index--]);
//	//free_2d_str(node->cmd_node->str);
//	if (red->flag == DB_LT_SIGN || red->flag == DB_GT_SIGN)
//		index--;

//	//next token to redirection -> file name, trim file name
//	start = index;
//	index += skip_space(&ptr[index]);
//	while (index)
//	{
//		if (ft_isspace(ptr[index]) == TRUE || ptr[index] == '<' || ptr[index] == '>' || ptr[index] == '\0')
//			break ;
//		index++;
//	}
//	red->str = ft_substr(ptr, start, index - start - 1);
//	ft_strlcat(&ptr[start], &ptr[index], ft_strlen(ptr) + ft_strlen(&ptr[index]) + 1);
//	printf("ptr: %s\n", ptr);
//	printf("red->str: %s\n", red->str);
//	//not expend * -> add quote and inner parser
//	//expend $
//	//error in ()
	
//	//strdup filename and strjoin node str
//	//node->cmd_node->str = init_doub_char(&ptr, 1);
//	//free(ptr);
//	//add heredoc, else => not add file name to minishell
//	if (red->flag == DB_LT_SIGN)
//	{
//		//add file name
//		tmp_file = (t_tmp_file *)malloc(sizeof(t_tmp_file));
//		ft_memset((void *)tmp_file, 0, sizeof(t_tmp_file));
//		tmp_file->tmp = ft_strjoin(minishell->tmp_file_name, ft_itoa(minishell->tmp_file_counter));
//		tmp_file->fd = open(tmp_file->tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
//		if (tmp_file->fd == -1) //add file descriptor error
//			return (NULL); //maybe leak inside
//		red->index = minishell->tmp_file_counter;
//		minishell->tmp_file_counter++;
//		tmp_file_list_push(tmp_file, minishell);
//	}
//	return (ptr);
//}

static int	lexar_redirect(t_ast_node *node, t_minishell *minishell, int index)
{
	char			*ptr;
	int				start;
	int				i;
	t_tmp_file		*tmp_file;
	t_redirection	*red;

	ptr = node->cmd_node->str[0]; 
	red = (t_redirection *)malloc(sizeof(t_redirection));
	ft_memset((void *)red, 0, sizeof(t_redirection));
	redirect_node_push(node, red);
	if (ptr[index] == '<')
	{
		ptr[index] = '\0';
		printf("ptr[%d]: %c\n", index, ptr[index]);
		if (ptr[index + 1] == '<')
		{
			red->flag = DB_LT_SIGN;
			index++;
		}
		else
			red->flag = LT_SIGN;
	}
	else
	{
		ptr[index] = '\0';
		if (ptr[index + 1] == '>')
		{
			red->flag = DB_GT_SIGN;
			index++;
		}
		else
			red->flag = GT_SIGN;
	}
	index++;
	start = index;
	index += skip_space(&ptr[index]);
	//syntax error newline
	if (ptr[index] == '\0')
	{
		node->err_flag = TRUE;
		syntax_err_message("newline", NOTDEFINED, NOTDEFINED, minishell);
	}
	while (ptr[index] != '\0')
	{
		if (ft_isspace(ptr[index]) == TRUE || ptr[index] == '<' || ptr[index] == '>' || ptr[index] == '\0' || ptr[index] == ' ')
			break ;
		index++;
	}
	//printf("ptr: %s\n", ptr);
	//printf("ptr after index : %s\n", &ptr[index]);
	//printf("start: %d, index: %d\n", start, index);
	//printf("%s\n", &ptr[start]);
	red->str = ft_substr(&ptr[start], 0, index - start);
	i = -1;

	ft_strlcat(ptr, &ptr[index], ft_strlen(ptr) + ft_strlen(&ptr[index]) + 1);
	//printf("ptr after strlcat: %s\n", ptr);
	//printf("red->str: %s\n", red->str);
	
	if (red->flag == DB_LT_SIGN)
	{
		//add file name
		tmp_file = (t_tmp_file *)malloc(sizeof(t_tmp_file));
		ft_memset((void *)tmp_file, 0, sizeof(t_tmp_file));
		tmp_file->tmp = ft_strjoin(minishell->tmp_file_name, ft_itoa(minishell->tmp_file_counter));
		tmp_file->fd = open(tmp_file->tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (tmp_file->fd == -1) //add file descriptor error
			return (NOTDEFINED); //maybe leak inside
		red->index = minishell->tmp_file_counter;
		minishell->tmp_file_counter++;
		tmp_file_list_push(tmp_file, minishell);
	}
	if (red->flag == DB_LT_SIGN || red->flag == DB_GT_SIGN)
		return (start - 3);
	else
		return (start - 2);
}

//check redirection, ()
int	lexar(t_ast_node *node, t_minishell *minishell)
{
	char		*ptr;
	char		**cmd_str;
	int			index;
	int			str_flag;
	int			tmp;
	
	index = -1;
	str_flag = FALSE;
	ptr = node->cmd_node->str[0];
	printf("lexar ptr: %s\n", ptr);
	while (ptr[++index])
	{
		//skip discard token
		index += skip_space(&ptr[index]);
		if (ptr[index] == '\"' || ptr[index] == '\'')
		{
			tmp = finder(&ptr[index + 1], ptr[index]);
			if (tmp == NOTDEFINED)
				return (syntax_err_message(ptr, NOTDEFINED, -1, minishell));
			index += tmp + 1;
			continue ;
		}
		//check for redirection
		if (ptr[index] == '<' || ptr[index] == '>')
		{
			index = lexar_redirect(node, minishell, index);
			if (index == NOTDEFINED) //error
			{
				return (syntax_err_message(ptr, index, -1, minishell));
			}
			continue ;
		}
		//check for subshell
		if (ptr[index] == '(')
		{
			if (str_flag == FALSE) //trim bracket and recurv in subshell
			{
				tmp = bracket_finder(&ptr[index]);
				if (tmp == NOTDEFINED)
					return (NOTDEFINED);
				ptr[tmp + index] = ' ';
				ptr[index] = ' ';
				recurv_parser(node, minishell);
				continue ;
			}
			tmp = bracket_finder(&ptr[index]);
			if (tmp == NOTDEFINED)
				return (NOTDEFINED);
			tmp += skip_space(&ptr[index + tmp]);
		}
	}
	//use inner parser to string
	cmd_str = string_parser(ptr, minishell);
	free_2d_str(node->cmd_node->str);
	node->cmd_node->str = cmd_str;
	index = -1;
	while (cmd_str[++index])
		printf("cmd_str[%d]: %s\n", index, cmd_str[index]);
	return (FUNC_SUC);
}
