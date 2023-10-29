/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:32:18 by plinscho          #+#    #+#             */
/*   Updated: 2023/10/29 18:11:09 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_mgr()
{
	printf("[SIGNAL_MGR] Function works\n");
	return ;
}

//	This function initializes everything to 0, so that no conflicts appear.
void	signal_init(void)
{
	sig_list.sig_int = 0;
	sig_list.sig_quit = 0;
	sig_list.exit_code = 0;
	sig_list.pid = 0;
}

void	signal_int(int sig)
{
	(void)sig;

}

void	signal_quit(int sig)
{
	(void)sig;

}