/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:32:18 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/23 17:32:36 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sig_handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	(void) sig;
}

// SIGINT == ctrl + C
// SIGQUIT == ctrl + D
void	signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
