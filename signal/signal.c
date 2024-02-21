/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:29:22 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/20 23:31:07 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	sigint_handler()
{
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	set_signal_handler()
{
	struct sigaction	sact;
	sigset_t			sigset;

	sigemptyset(&sact.sa_mask);
	sact.sa_flags = 0;
	sact.sa_handler = sigint_handler;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sact, NULL);
}
