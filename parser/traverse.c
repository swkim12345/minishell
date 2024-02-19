/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:25:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/19 11:52:18 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	recur_traverse(t_ast_node *head, t_minishell *minishell) //fork로 실행, wait를 통해 wait, 이후 pipe관련 처리
{
	int	ret;

	if (!head)
		return (TRUE); //fix 필요(true만 리턴하면 안됨.)
	ret = traverse(head->left_node, minishell, 1);
	if (head->cmd_node)
	{
		printf("cmd_node : %s\n", head->cmd_node->str[0]);
		printf("cmd redirection : %s\n", head->cmd_node->redirect);
		return (TRUE);
	}
	if (head->str)
		printf("str : %s\n", head->str);
	if ((!str_cmp(head->str, AND) && ret) ||
	(!str_cmp(head->str, OR) && !ret))
		ret = traverse(head->right_node, minishell, 1);
	return (ret);
}

int	subshell_traverse(t_ast_node *head, t_minishell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		lexar(head->str);
		traverse(head, minishell, 1);
	}
	else
		waitpid(pid, &minishell->exit_code, 0);
	return (WEXITSTATUS(minishell->exit_code));
}

int	get_num_pipe(t_ast_node *head)
{
	t_ast_node	*cur;
	int			num_pipe;

	num_pipe = 0;
	cur = head;
	while (cur)
	{
		cur = cur->next_ast_node;
		num_pipe++;
	}
	return (num_pipe);
}

int	wait_processes(pid_t last_pid, pid_t first_pid)
{
	int	wstatus;
	int	status_code;

	last_pid = waitpid(last_pid, &wstatus, 0);
	//if heredoc wait for first to finish and delete heredoc file
	// if (cmd->here_doc_flag)
	// {
	// 	if (waitpid(first_pid, NULL, 0) == -1)
	// 		unlink(g_path);
	// }
	if (WIFEXITED(wstatus))
	{
		status_code = WEXITSTATUS(wstatus);
	}
	while (1)
	{
		if (wait(NULL) == -1 && errno == ECHILD)
			break ;
	}
	return (status_code);
}

int	pipe_traverse(t_ast_node *head, t_minishell *minishell)
{
	int		ret;
	int		num_pipe;
	int		current_pipe;
	pid_t	pid;
	pid_t	first_pid;

	current_pipe = -1;
	num_pipe = get_num_pipe(head);
	printf("num_pipe: %d\n", num_pipe);
	while (++current_pipe < num_pipe)
	{
		printf("current pipe: %d\n", current_pipe);
		pid = fork();
		if (pid == 0)
		{
			ret = traverse(head, minishell, 0);
			exit(ret);
		}
		if (current_pipe == 0)
			first_pid = pid;
		head = head->next_ast_node;
	}
	ret = wait_processes(pid, first_pid);
	return (ret);
}

int	traverse(t_ast_node *head, t_minishell *minishell, int check_pipe)
{
	int	ret;

	if (!head)
		return (TRUE);
	else if (check_pipe && head->next_ast_node)
	{
		printf("find next pipe\n");
		ret = pipe_traverse(head, minishell);
	}
	else if (head->flag | BRACKET_FLAG)
		ret = subshell_traverse(head, minishell);
	else
		ret = recur_traverse(head, minishell);
	return (ret);
}
