/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:56:29 by plinscho          #+#    #+#             */
/*   Updated: 2023/10/29 18:11:14 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/*
	This structure is to maintain some order in the signals.
	We have to keep in mind that we can exit the program
	with the number of error we desire. We just take it from he struct
*/

typedef struct s_signal
{
	int		sig_int;
	int		sig_quit;
	int		exit_code;
	pid_t	pid;
}t_signal;

//	This makes the sig_list variable accesible to other files.
extern t_signal sig_list;
#endif