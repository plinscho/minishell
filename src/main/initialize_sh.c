/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_sh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:13:43 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/15 20:53:49 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/lexer.h"
#include "../../include/env.h"
#include "../../include/parser.h"


/*  we initialize the struct for the first time and parse the environment???*/
int	sh_init(t_mini *sh, char **env)
{
	int	error;
	
	sh->env	= NULL; 
	sh->env_lst = NULL;
	sh->lex_lst = NULL;
	sh->hd_lst = NULL;
	sh->pipe_lst = NULL;
	sh->input = NULL;
	sh->exit = 0;
	sh->pipes = 0;

	error = 0;
	signals(); 					// This starts the signals Ctrl + C && Ctrl + D.
	if (get_env(sh, env) == -1) // Loads env into the shell. If malloc fails, delete it.
		error = 1;
	if (env_converter(sh) == -1) // malloc has failed in the char **.
		error = 1;
	printf("\nShell Initialized\n#########################################\n");
	sh->power_on = 1;
	if (error)
		sh->power_on = 0;
	return (0);
}

int	sh_clean(t_mini *sh, int err)
{
	if (sh->lex_lst)
		lex_clean(&(sh->lex_lst));
	if (sh->hd_lst)
		hd_clean(&(sh)->hd_lst);
	if (sh->input)
		ft_memdel(sh->input);
	// here will be pipe clean:
	/*if (sh)->pipe_lst)
		pipe_clean(&(sh)->pipe_lst), in, 0);*/
	return (err);
}