/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:32:18 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/26 20:23:05 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*void	set_out_sig(void)
{
	struct sigaction	what;

	ft_memset(&what, 0, sizeof(what));
	what.sa_handler = &sig_handler;
	sigaction (SIGINT, &what, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	set_in_sig(void)
{
	struct sigaction	what;

	ft_memset(&what, 0, sizeof(what));
	what.sa_handler = &sig_newline;
	sigaction (SIGINT, &what, NULL);
	signal(SIGQUIT, SIG_IGN);
}*/

void	sig_handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	(void) sig;
}

/*void	sig_newline(int sig)
{
	if (sig == SIGQUIT)
	{
		g_last_signal = SIGQUIT;
		ft_dprintf(2, "^\\Quit: %d\n", g_last_signal);
	}
	rl_on_new_line();
}*/

// SIGINT == ctrl + C
// SIGQUIT == ctrl + D
void	signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
