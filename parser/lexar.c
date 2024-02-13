/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:28:22 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/12 20:49:52 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	init_shell(t_minishell *shell)
{
	shell->cwd = getcwd(0, 0);
	shell->input_str = 0;
}

void	exit_handle(t_minishell *shell)
{
	free(shell->input_str);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

int	str_equal(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (0);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (!*s1 && !*s2)
		return (1);
	return (0);
}

t_ast_node	*init_ast_node(int child_node)
{
	t_ast_node	*ret;
	t_cmd_node	*node;

	ret = (t_ast_node *)malloc(sizeof(t_ast_node));
	ft_memset((void *)ret, 0, sizeof(ret));
	if (CMDNODE & child_node)
	{
		node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
		ft_memset((void *)node, 0, sizeof(node));
		ret->cmd_node = node;
	}
	if (LEFTNODE & child_node)
		ret->left_node = init_ast_node(CMDNODE);
	if (RIGHTNODE & child_node)
		ret->right_node = init_ast_node(CMDNODE);
	return (ret);
}

static	t_ast_node	*pipe_lexar(t_ast_node *head)
{
	//| pipe -> make next ast node,
	//recurve head, next two node
	long		index;
	char		*ptr;
	t_ast_node	*ret;
	char		*str;
	
	ptr = head->cmd_node->str[0];
	index = find_pipe(ptr);
	if (ptr[index])
	{
		//split ast tree
		ret = init_ast_node(CMDNODE);
		ret->next_ast_node = head;
		ptr[index] = '\0';
		str = ft_strdup(ptr);
		ret->cmd_node->str = init_doub_char(&str, 1);
		str = ft_strdup(&str[index + 1]);
		free_doub_char(head->cmd_node->str);
		head->cmd_node->str = init_doub_char(&str, 1);
		recur_lexar(head);
		return (recur_lexar(ret));
	}
	return (head);
}

// static	long	bracket_lexar(t_ast_node *head)
// {
// 	long		index;
// 	char		*ptr;
// 	long		bracket_count;
// 	long		tmp;

// 	ptr = head->cmd_node->str[0];
// 	index = find_or_and_bracket(ptr);
// 	if (!ft_strncmp(ptr, &BRACKET[0], 1))
// 	{
// 		bracket_count = 1;
// 		tmp = index;
// 		ft_strlcpy(&ptr[index], &ptr[index + 1], ft_strlen(&ptr[index + 1]));
// 		while (TRUE)
// 		{
// 			tmp = find_bracket(&ptr[index]);
// 			if (ptr[tmp] == BRACKET[0])
// 				bracket_count++;
// 			else
// 				bracket_count--;
// 			if (!bracket_count || !ptr[tmp])
// 				break;
// 			tmp++;
// 		}
// 		ft_strlcpy(&ptr[tmp], &ptr[tmp + 1], ft_strlen(&ptr[tmp + 1]));
// 	}
// 	return (index);
// }

static	t_ast_node	*or_and_lexar(t_ast_node *head)
{
	char		*ptr;
	long		index;
	char		*str;
	t_ast_node	*ret;

	//|| && -> left(left_childe cmd_node), right(right_child, cmd_node), head->cmd_node(|| or &&)
	//각각 recurve
	ptr = head->cmd_node->str[0];
	index = find_or_and_bracket(ptr);
	if (!ft_strncmp(&ptr[index], OR, 2) || !ft_strncmp(&ptr[index], AND, 2))
	{
		ret = init_ast_node(RIGHTNODE);
		ret->next_ast_node = head->next_ast_node;
		if (!ft_strncmp(&ptr[index], OR, 2))
			str = ft_strdup(OR);
		else
			str = ft_strdup(AND);
		ret->str = str;
		ptr[index] = '\0';
		str = ft_strdup(&ptr[index + 2]);
		ret->right_node->cmd_node->str = init_doub_char(&str, 1);
		str = ft_strdup(ptr);
		free_doub_char(head->cmd_node->str);
		head->cmd_node->str = init_doub_char(&str, 1);
		ret->left_node = head;
		recur_lexar(ret->left_node);
		recur_lexar(ret->right_node);
		return (ret);
	}
	return (head);
}
 
t_ast_node	*recur_lexar(t_ast_node *head)
{
	t_ast_node	*ret;
	char		*ptr;
	long		index;

	ptr = head->cmd_node->str[0];
	ret = pipe_lexar(head);
	if (ret != head)
		return (ret);
	index = find_or_and_bracket(ptr);
	if (!ptr[index])
		return (head);
	// bracket_lexar(head);
	ret = or_and_lexar(head);
	if (ret != head)
		return (ret);
	return (ret);
}

t_ast_node	*lexar(char *input)
{
	t_ast_node	*head;
	char		*i;

	head = init_ast_node(CMDNODE);
	i = ft_strdup(input);
	head->cmd_node->str = init_doub_char(&i, 1);
	head = recur_lexar(head);	
	return (head);
}

int	main()
{
	t_minishell	shell;
	t_ast_node	*head;

	system("leaks a.out");

	init_shell(&shell);
	while (1)
	{
		shell.input_str = readline("minishell-1.0$ ");
		if (!shell.input_str)
			exit_handle(&shell);
		else if (str_equal(shell.input_str, "exit"))
			exit_handle(&shell);
		head = lexar(shell.input_str);
		// else
		// 	process_input(&shell);
		add_history(shell.input_str);
		free(shell.input_str);
	}
	return (0);
}
