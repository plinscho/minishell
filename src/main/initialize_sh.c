/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_sh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:13:43 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/19 21:46:42 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Here we initialize the struct for the first time and parse the environment */

int	sh_init(t_mini *sh, char **env)
{
	int	error;

	error = 0;
	sh->env	= NULL;
	sh->env_lst = NULL;
	sh->lex_lst = NULL;
	sh->hd_lst = NULL;
	sh->pipe_lst = NULL;
	sh->input = NULL;
	sh->exit = 0;
	sh->pipes = 0;
	signals(); 					 // This starts the signals Ctrl + C && Ctrl + D.
	if (get_env(sh, env) == -1)  // Loads env into the shell. If malloc fails, delete it.
		return (1);
	if (env_converter(sh) == -1) // malloc has failed in the char **.
		return (1);
	printf("\nShell Initialized\n#########################################\n\n"); //erase
	sh->power_on = 1;
	if (error)
		sh->power_on = 0;
	return (0);
}

/*
This function cleans the sh struct ans makes it ready for the next input.
*/
int	sh_clean(t_mini *sh, int err)
{
//	printf("[CLEAN]You entered: lex - %p\n", sh->lex_lst); //erase
	if (sh->lex_lst)
		lex_clean(&(sh->lex_lst));
//	printf("[CLEAN] after lex clean: lex - %p\n", sh->lex_lst); //erase
//	printf("[CLEAN]before hd clean: hd - %p\n", sh->hd_lst); //erase
	if (sh->hd_lst)
		fd_clean(&(sh->hd_lst));
//	printf("[CLEAN] after hd clean: hd - %p\n", sh->hd_lst); //erase
//	printf("[CLEAN] before input clean: input - %p\n", sh->input); //erase
	if (sh->input) // memdel doesn't set a ptr to null without double pointer
		sh->input = ft_memdel(sh->input);
//	printf("[CLEAN] after input clean: input - %p\n", sh->input); //erase
//	printf("[CLEAN] before pipe clean: pipe - %p\n", sh->pipe_lst); //erase
	if (sh->pipe_lst)
		pipe_clean(&(sh->pipe_lst));
	sh->pipes = 0;
	return (err);
}

/* 
This function restores the initial position of all the lists clean all of 
them after iteration 
*/
t_mini	*sh_restore(t_mini **sh, t_lexer *lex, t_fd *hd)
{
	if (lex)
		(*sh)->lex_lst = lex;
	if (hd)
		(*sh)->hd_lst = hd;
	return (*sh);
}

int	sh_loop_init(t_mini *sh)
{
//	sh->paths = ft_split(ft_get_value(sh, "PATH"), ':');
//	if (!sh->paths)
//	{
//		ft_exit_exe(sh, "malloc", "allocation failed\n", errno);
//		return (1);
//	}
	if (env_converter(sh) == -1) // malloc has failed in the char **.
		return (1);
	return (0);
}