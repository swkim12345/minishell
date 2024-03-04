/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:29:22 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/04 15:53:03 by minsepar         ###   ########.fr       */
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

void	set_signal_handler()
{
	struct sigaction	sact;
	sigset_t			sigset;

	//ahhhhh
	(void) sigset;
	sigemptyset(&sact.sa_mask);
	sact.sa_handler = sigint_handler;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	sigaction(SIGINT, &sact, NULL);
}

void	set_signal_dfl()
{
	struct sigaction	sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sact, NULL);
}

void	set_sigint_ign()
{
	struct sigaction	sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sact, NULL);
}

void	sigint_heredoc_p_handle(int signum)
{
	(void)signum;

	printf("\n");
}

void	set_heredoc_parent()
{
	struct sigaction	sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_handler = sigint_heredoc_p_handle;
	sigaction(SIGINT, &sact, NULL);
}