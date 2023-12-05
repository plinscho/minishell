/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_sh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/05 16:38:16 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/minishell.h"

/* Here we initialize the struct for the first time and parse the environment */

//int	allocate_exe(t_mini *sh);

int	sh_init(t_mini *sh, char **env)
{
	sh->env	= NULL;
	sh->env_lst = NULL;
	sh->lex_lst = NULL;
	sh->hd_lst = NULL;
	sh->pipe_lst = NULL;
	sh->input = NULL;
	sh->paths = NULL;
	sh->exit = 0;
	sh->envp = env; // for debugging only
	if (allocate_exe(sh))
		return (err_break(sh, "malloc", NULL, 12));
//	signals(); 					 // This starts the signals Ctrl + C && Ctrl + D.
	if (get_env(sh, env) == -1)  // Loads env into the shell. If malloc fails, delete it.
		return (err_break(sh, "malloc", NULL, 12));
	sh->env = NULL;
	if (env_converter(sh) == -1) // malloc has failed in the char **.
		return (err_break(sh, "malloc", NULL, 12));
	printf("\nShell Initialized\n#########################################\n\n"); //erase
	sh->power_on = 1;
	return (0);
}

/*
This function cleans the sh struct ans makes it ready for the next input.
*/
void	sh_clean(t_mini *sh)
{
//	printf("[CLEAN]You entered: lex - %p\n", sh->lex_lst); //erase
	if (sh->lex_lst)
		lex_clean(&(sh->lex_lst));
//	printf("[CLEAN] after lex clean: lex - %p\n", sh->lex_lst); //erase
//	printf("[CLEAN]before hd clean: hd - %p\n", sh->hd_lst); //erase
	if (sh->hd_lst)
		fd_clean(&(sh->hd_lst), 1);
//	printf("[CLEAN] after hd clean: hd - %p\n", sh->hd_lst); //erase
//	printf("[CLEAN] before input clean: input - %p\n", sh->input); //erase
	if (sh->input && *sh->input) // memdel doesn't set a ptr to null without double pointer
		sh->input = ft_memdel(sh->input);
//	printf("[CLEAN] after input clean: input - %p\n", sh->input); //erase
//	printf("[CLEAN] before pipe clean: pipe - %p\n", sh->pipe_lst); //erase
	if (sh->pipe_lst)
		pipe_clean(&(sh->pipe_lst));
//	printf("[CLEAN] before pipe clean: pipe - %p\n", sh->pipe_lst); //erase	
//	printf("[CLEAN] before paths clean: paths - %p\n", sh->paths); //erase
	if (sh->paths)
		sh->paths = arr_clean(sh->paths, 0);
//	printf("[CLEAN] after paths clean: paths - %p\n", sh->paths); //erase
//	printf("[CLEAN] before env clean: env - %p\n", sh->env); //erase
	if (sh->env)
		sh->env = arr_clean(sh->env, 0);
//	printf("[CLEAN] after env clean: env - %p\n", sh->env); //erase
//	sh->exit = err; // this is incorrect
	sh->pipes = 0;
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
//	printf("\n[LOOP INIT] path: %s\n", ft_get_value(sh, "PATH")); //erase
	if (!sh->paths)
		sh->paths = ft_split(ft_get_value(sh, "PATH"), ':');
	if (!sh->paths)
		return(err_break(sh, "malloc", NULL, 12));
	if (!sh->env)
	{
		if (env_converter(sh) == -1) // malloc has failed in the char **.
			return (err_break(sh, "malloc", NULL, 12));
	}
	return (0);
}

int	allocate_exe(t_mini *sh)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return (1);
	new->fdp[0] = -2;
	new->fdp[1] = -2;
	sh->exe = new;
	return (0);
}