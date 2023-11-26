/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_dina.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:01:35 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/26 20:05:27 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"
#include "../../include/minishell.h"

/* This one should only be used in the child processes because it exits the process. 
It is a first sketch. We need to change all the structure now of exiting the 
loop and cleaning the struct. */
int	ft_exit_exe(t_mini *sh, char *name, char *message, int err)
{
	ft_putstr_fd("minishell: ", 2);
//	write(2, ": exit!!!\n", ft_strlen("exit!!!\n")); //erase
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (message)
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
	}
	sh_clean(sh, err);
	exit(err);
}

/* This one should only be used in the parent process, it doesn't exit.
It is a first sketch. We need to change all the structure now of exiting the 
loop and cleaning the struct */
int	ft_error_break(t_mini *sh, char *name, char *message, int err)
{
	if (!name && message)
		printf("minishell: %s\n", message);
	if (name && message)
		printf("minishell: %s: %s\n", name, message);
	sh_clean(sh, err);
	return(err);
}