/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:42:48 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/27 16:42:51 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// exit is also a tricky function. Can be used almost everywhere and with and saves the $? error.
// Im also saving it for the last so that can work with the rest of the code when debugged.

int		ft_exit(t_mini *sh)
{
	sh->power_on = 0;		
	return (1);
}