#include "../main.h"

void	init_shell(t_minishell *shell)
{
	shell->cwd = getcwd(0, 0);
	shell->input_str = 0;
	shell->tmp_file_name = "/tmp/minishell_tmp_file_";
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

// int	get_input_heredoc(t_minishell *shell, int i)
// {
// 	char	*str;

// 	shell->tmp_list[i].tmp = ft_strjoin(shell->tmp_file_name, ft_itoa(i));
// 	shell->tmp_list[i].fd = open(shell->tmp_list[i].tmp, O_RDONLY | O_CREAT);
// 	str = readline("> ");
// 	while (1)
// 	{
// 		if (!str)
// 		{
// 			str = get_next_line(STDIN_FILENO);
// 			continue ;
// 		}
// 		if (is_str_limiter(pipex_args->argv[2], str) == 1)
// 			break ;
// 		if (write(fd, str, ft_strlen(str)) == -1)
// 			shell_error(g_path);
// 		free(str);
// 		write(STDOUT_FILENO, "pipe heredoc> ", 14);
// 		str = get_next_line(STDIN_FILENO);
// 	}
// 	if (str)
// 		free(str);
// }

// int	process_readline(t_minishell *shell)
// {
// 	t_ast_node	*head;
// 	int			i;

// 	i = -1;
// 	head = lexar(shell->input_str);
// 	if (!head)
// 		printf("not in head\n");
// 	while (++i < shell->tmp_file_counter)
// 	{
// 		get_input_heredoc(shell, i);
// 	}
// 	traverse(head, shell, 1);
// 	free_ast_tree(head);
// }

int	main()
{
	t_minishell	shell;
	t_ast_node	*head;

	system("leaks minishell");

	init_shell(&shell);
	while (1)
	{
		shell.input_str = readline("minishell-1.0$ ");
		if (!shell.input_str)
			exit_handle(&shell);
		else if (str_equal(shell.input_str, "exit"))
			exit_handle(&shell);
		// process_readline(&shell);
		head = new_parser(shell.input_str, &shell);
		if (!head)
			return (0);
		traverse(head, &shell, 1);
		// free_ast_tree(head);
		add_history(shell.input_str);
		free(shell.input_str);
	}
	return (0);
}
