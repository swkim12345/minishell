/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:29:22 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 15:22:25 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	sigint_handler(int signum)
{
	(void)signum;

	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_child_handler(int signum)
{
	printf("%d\n", signum);
}

void	set_signal_handler()
{
	struct sigaction	sact;
	sigset_t			sigset;

	//ahhhhh
	(void) sigset;
	sigemptyset(&sact.sa_mask);
	sact.sa_handler = sigint_handler;
	sact.sa_flags = SA_NOCLDWAIT;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGCHLD, sig_child_handler);
	sigaction(SIGINT, &sact, NULL);
}

void	set_signal_dfl()
{
	struct sigaction	sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_handler = SIG_DFL;
	sact.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGINT, &sact, NULL);
}

void	set_sigint_ign()
{
	struct sigaction	sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_handler = SIG_IGN;
	sact.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGINT, &sact, NULL);
}

void	sigint_heredoc_handle(int signum)
{
	(void)signum;

	printf("\n");
	exit(1);
}

void	set_heredoc_int_handler()
{
	struct sigaction	sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_handler = sigint_heredoc_handle;
	sact.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGINT, &sact, NULL);
}

void	sig_term_handler(int signum)
{
	(void)signum;

	printf("Quit: 3\n");
	exit(131);
}