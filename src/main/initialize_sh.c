/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_sh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:13:43 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/10 00:13:00 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Here we initialize the struct for the first time and parse the environment???*/
void	mini_init(t_mini *sh)
{
	sh->env	= NULL; // Let's parse here?
	sh->env_lst = NULL; // Let's parse here?
	sh->lex_lst = NULL;
	sh->hd_lst = NULL;
	sh->pipe_lst = NULL;
	sh->input = NULL;
	sh->exit = 0;
	sh->pipes = 0;
}

int	sh_clean(t_mini **sh, int err)
{
	if ((*sh)->lex_lst)
		lex_clean(&((*sh)->lex_lst));
	if ((*sh)->hd_lst)
		hd_clean(&((*sh)->hd_lst));
	if ((*sh)->input)
	{
		free((*sh)->input);
		(*sh)->input = NULL;
	}
	// here will be pipe clean:
	/*if ((*sh)->pipe_lst)
		pipe_clean(&((*sh)->pipe_lst), in, 0);*/
	return (err);
}