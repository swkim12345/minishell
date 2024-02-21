#include "../main.h"

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

int	get_input_heredoc(t_minishell *shell, t_tmp_file *file)
{
	char	*str;

	file->tmp = ft_strjoin(shell->tmp_file_name, ft_itoa(shell->tmp_file_counter));
	file->fd = open(file->tmp, O_WRONLY | O_TRUNC | O_CREAT);
	str = readline("> ");
	while (1)
	{
		if (!str)
		{
			str = readline("> ");
			continue ;
		}
		//change pipex_args->argv[2] to eof
		if (str_equal("eof", str) == 1)
			break ;
		if (write(file->fd, str, ft_strlen(str)) == -1)
			exit(0);
			// shell_error(file->tmp); // change to custom error
		free(str);
		str = readline("> ");
	}
	if (str)
		free(str);
	return (0);
}


int	process_readline(t_minishell *shell)
{
	t_ast_node	*head;
	int			i;

	i = -1;
	head = lexar(shell->input_str);
	if (!head)
		printf("not in head\n");
	traverse(head, shell, 1);
	free_ast_tree(head);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_ast_node	*head;

	init_shell(&shell, envp);
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
