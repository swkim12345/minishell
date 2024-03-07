/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:29:22 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/07 17:35:21 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signal_handler(void)
{
	struct sigaction	sact;
	sigset_t			sigset;

	(void) sigset;
	sigemptyset(&sact.sa_mask);
	sact.sa_handler = sigint_handler;
	sact.sa_flags = SA_NOCLDWAIT;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sact, NULL);
}

void	sigint_heredoc_handle(int signum)
{
	(void)signum;
	printf("\n");
	exit(1);
}

void	set_heredoc_int_handler(void)
{
	struct sigaction	sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_handler = sigint_heredoc_handle;
	sact.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGINT, &sact, NULL);
}
