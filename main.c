/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:27 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 12:50:42 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_ast_node	*head;

	init_shell(&shell, envp, argv, argc);
	while (1)
	{
		shell.input_str = readline(shell.print_str);
		if (!shell.input_str)
			exit_handle(&shell, EXIT_SUCCESS);
		head = parser(shell.input_str, &shell);
		if (ft_strlen(shell.input_str) > 0 && head)
		{
			shell.exit_code = 0;
			traverse(head, &shell, 1);
		}
		if (ft_strlen(shell.input_str) != 0)
			add_history(shell.input_str);
		free_ast_tree(head);
		clear_tmp_list(shell.tmp_list, &shell, TRUE);
		free(shell.input_str);
	}
}
