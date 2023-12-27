/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_sh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/27 19:38:31 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/minishell.h"

/* Here we initialize the struct for the first time and parse the environment */

int	sh_init(t_mini *sh, char **env)
{
	sh->env_lst = NULL;
	sh->lex_lst = NULL;
	sh->hd_lst = NULL;
	sh->pipe_lst = NULL;
	sh->exp = NULL;
	sh->input = NULL;
	sh->paths = NULL;
	sh->exit = 0;
	sh->pipes = 0;
	sh->check = 0;
	sh->exe = NULL;
	sh->env	= NULL;
//	sh->envp = env; // for debugging only
	sh->power_on = 0;
//	signals();
	if (env)
		first_env(sh, env);
//	if (first_env(sh, env))
 //   	return (err_break(sh, "malloc", NULL, 12));
	sh->env = env_converter(sh->env_lst);
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
	if (sh->input && *sh->input)
		sh->input = ft_memdel(sh->input);
//	printf("[CLEAN] after input clean: input - %p\n", sh->input); //erase
//	printf("[CLEAN] before pipe clean: pipe - %p\n", sh->pipe_lst); //erase
	if (sh->pipe_lst)
		pipe_clean(&(sh->pipe_lst));
//	printf("[CLEAN] before pipe clean: pipe - %p\n", sh->pipe_lst); //erase	
//	printf("[CLEAN] before paths clean: paths - %p\n", sh->paths); //erase
	if (sh->paths && sh->paths[0] != NULL)
		sh->paths = arr_clean(sh->paths, 0);
//	printf("[CLEAN] after paths clean: paths - %p\n", sh->paths); //erase
//	printf("[CLEAN] before env clean: env - %p\n", sh->env); //erase
//	if (sh->env)
//		sh->env = arr_clean(sh->env, 0);
//	printf("[CLEAN] after env clean: env - %p\n", sh->env); //erase
	if (sh->exe)
		sh->exe = ft_memdel(sh->exe);
	if (sh->exp)
		exp_clean(&sh->exp);
	sh->pipes = 0;
	sh->check = 0;
}

/* 
This function restores the initial position of all the lists clean all of 
them after iteration 
*/
t_mini	*sh_re(t_mini **sh, t_lexer *lex, t_fd *hd)
{
//	printf("\n[SH RESTORE] ---- entered\n"); //erase
	if (lex)
		(*sh)->lex_lst = lex;
	if (hd)
		(*sh)->hd_lst = hd;
//	printf("\n[SH RESTORE] ---- exit\n"); //erase
	return (*sh);
}

int	sh_loop_init(t_mini *sh)
{
//	printf("\n[LOOP INIT] path: %s\n", ft_get_value(sh, "PATH")); //erase
	sh->pipes = 0;
	sh->check = 0;
	if (ft_get_value(sh, "PATH"))
	{
		sh->paths = ft_split(ft_get_value(sh, "PATH"), ':');
		if (!sh->paths)
			return(err_break(sh, "malloc", NULL, 12));
	}
	if (allocate_exe(sh))
		return (err_break(sh, "malloc", NULL, 12));
//	if (sh->env)
//		sh->env = arr_clean(sh->env, 0);
//	sh->env = env_converter(sh->env_lst);
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