/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:19:22 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/21 19:05:52 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		quotes_error(t_mini *sh)
{
	ft_putstr_fd("minishell: syntax error: Quotes not closed\n", 2);
	sh->exit = 258;
	return (1);
}

/*void	syntax_error(t_mini *sh, char *seq)
{
	(void)sh;
	printf("minishell: syntax error near unexpected token '%s'\n", seq);
	return ;
}
*/

/*
# define TRUNC 4		>
# define PIPE 5			|
# define INPUT 6		<
*/

int	err_char(t_mini *sh, int token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (token == 4)
		ft_putendl_fd("<\n", 2);
	else if (token == 5)
		ft_putendl_fd(">\n", 2);
	else if (token == 6)
		ft_putendl_fd("<<\n", 2);
	else if (token == 7)
		ft_putendl_fd(">>\n", 2);
	else if (token == 8)
		ft_putendl_fd("|\n", 2);
	else
		ft_putendl_fd("newline\n", 2);
	sh->exit = 258;
	return (1);	
}

/*int	serror(char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (2);
}*/

/* This one should only be used in the child processes because it exits the process. 
It is a first sketch. We need to change all the structure now of exiting the 
loop and cleaning the struct. */
int	err_exit(t_mini *sh, char *name, char *message, int err)
{
	//	write(2, ": exit!!!\n", ft_strlen("exit!!!\n")); //erase
//	printf("[ERR EXIT] name: %s,\n message: %s\n", name, message); //erase
//	if (!sh->pipes && sh->pipe_lst->builtin && err == 1)
//		return (err_break(sh, name, message, err));
	if (name || message)
		ft_putstr_fd("minishell: ", 2);
	if ((err == 1 && *name && !message) || err == 14 || err == 12)
		perror(name);
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
	sh_clean(sh);
	exit (err);
}

/* This one should only be used in the parent process, it doesn't exit.
It is a first sketch. We need to change all the structure now of exiting the 
loop and cleaning the struct */
int	err_break(t_mini *sh, char *name, char *message, int err)
{
	if (name || message)
		ft_putstr_fd("minishell: ", 2);
	if ((err == 1 && *name && !message) || err == 14 || err == 12)
		perror(name);
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
	sh->exit = err;
	return(err);
}