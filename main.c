/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:27 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/13 14:07:43 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	readline_clean(t_ast_node *head, t_minishell *shell)
{
	free_ast_tree(head);
	clear_tmp_list(shell->tmp_list, shell, TRUE);
	free(shell->input_str);
}

void	red_tester(t_redirection *red)
{
	if (!red)
		return ;
	printf("==============REDIRECTION START================\n");
	printf("red->index: %d\n", red->index);
	printf("red->flag: %d\n", red->flag);
	printf("red->str : %s\n", red->str);
	printf("red->next: %p\n", red->next);
	printf("==============REDIRECTION END==================\n\n\n");
	
	red_tester(red->next);
}

//check traverse
void	trav_tester(t_ast_node *head, t_minishell *shell)
{
	//print
	printf("=================AST NODE START=================\n");
	printf("left_node: %p\n", head->left_node);
	printf("right_node: %p\n", head->right_node);
	printf("next_node: %p\n", head->next_ast_node);
	printf("cmd_node: %p\n", head->cmd_node);
	printf("flag : %d\n", head->flag);
	printf("flag, OR_FLAG: %d\n", head->flag & OR_FLAG);
	printf("flag, AND_FLAG: %d\n", head->flag & AND_FLAG);
	printf("flag BLACKET_FLAG: %d\n", head->flag & BRACKET_FLAG);
	printf("redirection: %p\n", head->red);
	printf("====================AST NODE END=================\n\n\n");
	//priority
	if (head->cmd_node)
	{
		printf("cmd_node go\n");
		printf("==============CMD_NODE START===================\n");
		printf("cmd_name: %s\n", head->cmd_node->str[0]);
		printf("==============CMD_NODE END=====================\n\n\n");
	}
	if (head->red)
	{
		printf("redirection go : %p\n\n\n", head->red);
		red_tester(head->red);
	}
	if (head->left_node)
	{
		printf("left_node go : %p\n\n\n", head->left_node);
		trav_tester(head->left_node, shell);
	}
	if (head->right_node)
	{
		printf("right_node go : %p\n\n\n", head->right_node);
		trav_tester(head->right_node, shell);
	}
	if (head->next_ast_node)
	{
		printf("next_node go : %p\n\n\n", head->next_ast_node);
		trav_tester(head->next_ast_node, shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_ast_node	*head;

	init_shell(&shell, envp, argv, argc);
	while (1)
	{
		shell.input_str = readline(shell.print_str);
		if (!shell.input_str)
		{
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);
			exit(shell.exit_code);
		}
		head = parser(shell.input_str, &shell);
		//trav_tester(head, &shell);
		if (ft_strlen(shell.input_str) > 0 && head)
		{
			traverse(head, &shell, 1, 3);
			if (shell.flag & PIPE_TRAVERSE)
				exit(shell.exit_code);
		}
		if (ft_strlen(shell.input_str) != 0)
			add_history(shell.input_str);
		readline_clean(head, &shell);
	}
}
