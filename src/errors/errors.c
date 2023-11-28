/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:19:22 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/28 19:06:40 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		quotes_error(t_mini *sh)
{
	ft_putstr_fd("minishell: syntax error: Quotes not closed\n", 2);
	sh->exit = 258;
	return (sh->exit);
}

/*void	syntax_error(t_mini *sh, char *seq)
{
	(void)sh;
	printf("minishell: syntax error near unexpected token '%s'\n", seq);
	return ;
}*/

int	serror(char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (2);
}

/* This one should only be used in the child processes because it exits the process. 
It is a first sketch. We need to change all the structure now of exiting the 
loop and cleaning the struct. */
int	err_exit(t_mini *sh, char *name, char *message, int err)
{
	//	write(2, ": exit!!!\n", ft_strlen("exit!!!\n")); //erase
	printf("[ERR EXIT] errno: %i, message: %s\n", 17, strerror(17)); //erase
	printf("[ERR EXIT] errno: %i, message: %s\n", 18, strerror(18)); //erase
	printf("[ERR EXIT] errno: %i, message: %s\n", 19, strerror(19)); //erase
	printf("[ERR EXIT] errno: %i, message: %s\n", 20, strerror(20)); //erase
	printf("[ERR EXIT] errno: %i, message: %s\n", 21, strerror(21)); //erase
	printf("[ERR EXIT] errno: %i, message: %s\n", 22, strerror(22)); //erase
	printf("[ERR EXIT] errno: %i, message: %s\n", 23, strerror(23)); //erase
	printf("[ERR EXIT] errno: %i, message: %s\n", 24, strerror(24)); //erase
	printf("[ERR EXIT] errno: %i, message: %s\n", 25, strerror(25)); //erase
	printf("[ERR EXIT] errno: %i, message: %s\n", 26, strerror(26)); //erase
	printf("[ERR EXIT] errno: %i, message: %s\n", 27, strerror(27)); //erase
	printf("[ERR EXIT] errno: %i, message: %s\n", 28, strerror(28)); //erase
	printf("[ERR EXIT] errno: %i, message: %s\n", 29, strerror(29)); //erase
//	printf("[ERR EXIT] name: %s,\n message: %s\n", name, message); //erase

	if (name || message)
		ft_putstr_fd("minishell: ", 2);
	if ((err == 1 && *name) || err == 14)
	{
		perror(name);
//		sh_clean(sh, err);
//		exit (err);
	}
	else if (name)
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
	exit (err);
}

/* This one should only be used in the parent process, it doesn't exit.
It is a first sketch. We need to change all the structure now of exiting the 
loop and cleaning the struct */
int	err_break(t_mini *sh, char *name, char *message, int err)
{
	if (name || message)
		ft_putstr_fd("minishell: ", 2);
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
//	sh_clean(sh, err);
	sh->exit = err;
	return(err);
}