/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:29:22 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/29 12:34:46 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	sigint_handler()
{
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	set_command_handler()
{
	struct sigaction	sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_flags = 0;
	sact.sa_handler = NULL;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sact, NULL);
}

void	set_signal_handler()
{
	struct sigaction	sact;
	sigset_t			sigset;

	//ahhhhh
	(void) sigset;

	sigemptyset(&sact.sa_mask);
	sact.sa_flags = 0;
	sact.sa_handler = sigint_handler;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sact, NULL);
}
