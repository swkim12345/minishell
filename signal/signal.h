/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:51:56 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/03 20:38:02 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SIGNAL_H
# define SIGNAL_H

# include "../main.h"

void	set_signal_handler(void);
void	set_signal_dfl(void);
void	set_sigint_ign(void);

#endif