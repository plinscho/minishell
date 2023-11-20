/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:15:43 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/10 00:44:09 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
This function adds an fd node add the back of the fd list 
*/
void	fd_add(t_fd **lst, t_fd *new)
{
	t_fd	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp -> next)
		temp = temp -> next;
	temp -> next = new;
}

/* 
This function cleans the fd list and closes the file descriptors 
if they are bigger than 0 
*/
void	fd_clean(t_fd **hd)
{
	t_fd	*temp;
	t_fd	*iter;

	iter = *hd;
	while (iter)
	{
		temp = iter;
		iter = iter->next;
		if (temp->str)
		{
			free(temp->str);
			temp->str = NULL;
		}
		if (temp->fd > 0)
			close(temp->fd);
		free(temp);
		temp = NULL;
	}
	*hd = NULL;
}

/* 
This function initializes the file descriptor from parser node in 3 cases:
1. if type is 0 and token is NOT 6 - the fd is -2, lex->token is the type of redirection, and then 
the filename.
2. if type is 0 and token is 6 - the fd is the open fd where the heredoc is stored, 
lex->token is the type of redirection, and then the keyword. 
3. if type is NOT 0 (then it's 4) - the fd is -2, 4 is the type of redirection, and lex->str is 
the filename. 
*/
void	fd_init(t_fd *new, t_mini *sh, int fd, int type)
{
//	printf("[FD_INIT]You entered, fd: %i -- type: %i\n", fd, type); //erase
	if (!type)
	{
		new->type = sh->lex_lst->token;
		sh->lex_lst = sh->lex_lst->next;
		if (sh->lex_lst && sh->lex_lst->token == 0)
			sh->lex_lst = sh->lex_lst->next;
		else if (!sh->lex_lst) // en realidad es un caso de error de syntax
			return ;
	}
	else
		new->type = type;
//	printf("[FD_INIT] new fd: %i -- type: %i\n", fd, type); //erase
	new->str = sh->lex_lst->cont;
	new->fd = fd;
	new->next = NULL;
	if (sh->lex_lst) // en realidad es un error de syntax este if
		sh->lex_lst = sh->lex_lst->next;
}