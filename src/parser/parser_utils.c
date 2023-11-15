/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:41:40 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/10 00:13:54 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipe_init(t_pipe *pip)
{
	pip->cmd = NULL;
//	pip->paths = NULL;
	pip->fd_lst = NULL;
	pip->in_fd = -2;
	pip->out_fd = -2;
	pip->next = NULL;
//	pip->vars = NULL;
}

void	pipe_add(t_mini *sh, t_pipe *new)
{
	t_pipe	*temp;

	if (!sh->pipe_lst)
	{
		sh->pipe_lst = new;
		return ;
	}
	temp = sh->pipe_lst;
	while (temp -> next)
		temp = temp -> next;
	temp -> next = new;
}

int	pipe_clean(t_pipe **lst)
{
	t_pipe	*temp;

//	printf("[PIPE CLEAN]You entered: PIPE - %p\n", *lst); //erase
	while (*lst)
	{
		temp = (*lst) -> next;
//		printf("[PIPE CLEAN] before hd clean: hd - %p\n", (*lst) -> fd_lst); //erase
		if ((*lst) -> fd_lst)
			fd_clean(&((*lst) -> fd_lst));
//		printf("[PIPE CLEAN] after hd clean: hd - %p\n", (*lst) -> fd_lst); //erase
//		printf("[PIPE CLEAN] before cmd clean: cmd - %p\n", (*lst) -> cmd); //erase
		(*lst)->cmd = arr_clean((*lst)->cmd, 1);
//		printf("[PIPE CLEAN] after cmd clean: cmd - %p\n", (*lst) -> cmd); //erase
		//check if i neet to close in and out fd here
		free(*lst);
		*lst = NULL;
		*lst = temp;
	}
	lst = NULL;
	return (1);
}





