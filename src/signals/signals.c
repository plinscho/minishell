/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:32:18 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/10 00:45:24 by plinscho         ###   ########.fr       */
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
	return ;
}

void	signal_int(int sig)
{
	(void)sig;

}

void	signal_quit(int sig)
{
	(void)sig;

}