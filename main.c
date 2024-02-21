/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:27 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/20 23:55:43 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_shell(t_minishell *shell, char **envp)
{
	shell->cwd = getcwd(0, 0);
	shell->input_str = 0;
	shell->envp = envp;
	shell->tmp_file_name = "/tmp/minishell_tmp_";
	shell->tmp_file_counter = 0;
}

void	exit_handle(t_minishell *shell)
{
	free(shell->input_str);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

void	set_term(void)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_minishell	shell;

// 	init_shell(&shell, envp);
// 	set_signal_handler();
// 	set_term();
// 	while (1)
// 	{
// 		shell.input_str = readline("minishell-1.0$ ");
// 		if (!shell.input_str)
// 			exit_handle(&shell);
// 		else if (str_equal(shell.input_str, "exit"))
// 			exit_handle(&shell);
// 		// else
// 		// 	process_input(&shell);
// 		add_history(shell.input_str);
// 		free(shell.input_str);
// 	}
// }
