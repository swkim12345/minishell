/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:27 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/08 21:31:14 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	readline_clean(t_ast_node *head, t_minishell *shell)
{
	free_ast_tree(head);
	clear_tmp_list(shell->tmp_list, shell, TRUE);
	free(shell->input_str);
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
		if (ft_strlen(shell.input_str) > 0 && head)
		{
			traverse(head, &shell, 1);
			if (shell.flag & PIPE_TRAVERSE)
				exit(shell.exit_code);
		}
		if (ft_strlen(shell.input_str) != 0)
			add_history(shell.input_str);
		readline_clean(head, &shell);
	}
}
