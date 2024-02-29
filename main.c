/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:27 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/29 18:04:29 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_shell(t_minishell *shell, char **envp, char **argv)
{
	ft_memset(shell, 0, sizeof(t_minishell));
	shell->stdin_fd = dup(0);
	shell->stdout_fd = dup(1);
	shell->cwd = getcwd(0, 0);
	shell->envp = envp;
	shell->tmp_file_name = "/tmp/minishell_tmp_";
	shell->env = ft_initenv(envp, shell);
	shell->export = ft_initenv(envp, shell);
	if (ft_strncmp(argv[0], "./", 2) == 0)
		shell->execute_name = ft_substr(argv[0], 2, ft_strlen(argv[0]));
	else
		shell->execute_name = ft_strdup(argv[0]);
	shell->tmp_list = (t_tmp_list *)ft_calloc(sizeof(t_tmp_list), 1);
}

void	free_t_minishell(t_minishell *shell)
{
	(void) shell;
	free(shell->input_str);
	free(shell->cwd);
	free(shell->execute_name);
	free_tmp_list(shell->tmp_list, shell);
	free_tree_delete(shell->env);
	free_tree_delete(shell->export);
}

void	exit_handle(t_minishell *shell, int status)
{
	(void) shell;
	free_t_minishell(shell);
	printf("exit\n");
	exit(status);
}

void	set_term(void)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

void	check()
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	// atexit(check);
	t_minishell	shell;
	t_ast_node	*head;

	// atexit(check);
	init_shell(&shell, envp, argv);
	set_signal_handler();
	set_term();
	(void) argc;
	(void) argv;

	// int i = 0;
	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	while (1)
	{
		shell.input_str = readline("minishell-1.0$ ");
		set_command_handler();
		if (!shell.input_str)
			exit_handle(&shell, 134);
		head = parser(shell.input_str, &shell);
		if (!shell.input_str)
			exit_handle(&shell, EXIT_SUCCESS);
		else if (ft_strlen(shell.input_str) > 0)
		{
			traverse(head, &shell, 1);
			clear_tmp_list(shell.tmp_list, &shell);
		}
		// set_signal_handler();
		if (ft_strlen(shell.input_str) != 0)
			add_history(shell.input_str);
		free(shell.input_str);
		printf("end of main\n");
	}

}
