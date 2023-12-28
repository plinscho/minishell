/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:15:43 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/27 22:40:55 by nzhuzhle         ###   ########.fr       */
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
void	fd_clean(t_fd **hd, int flag)
{
	t_fd	*temp;
	t_fd	*iter;

	iter = *hd;
	while (iter)
	{
		temp = iter;
		iter = iter->next;
		if (temp->str && flag)
			temp->str = ft_memdel(temp->str);
		if (temp->fd > 0 && flag)
			close(temp->fd);
		temp = ft_memdel(temp);
	}
	*hd = NULL;
}

/* 
This function initializes the file descriptor from parser node in 3 cases:
1. if type is 0 and token is NOT 6 - the fd is -2, lex->token is the type of
redirection, and then the filename.
2. if type is 0 and token is 6 - the fd is the open fd where the heredoc 
is stored, lex->token is the type of redirection, and then the keyword. 
3. if type is NOT 0 (then it's 4) - the fd is -2, 4 is the type of redirection,
and lex->str is the filename. 
*/
int	fd_init(t_fd *new, t_mini *sh, int fd)
{
	new->exp = 0;
	new->type = sh->lex_lst->token;
	sh->lex_lst = sh->lex_lst->next;
	while (sh->lex_lst && sh->lex_lst->token == 0)
		sh->lex_lst = sh->lex_lst->next;
	if (!sh->lex_lst)
		return (1);
	sh->lex_lst->cont = exp_file(sh, sh->lex_lst->cont, new);
	if (!sh->lex_lst->cont)
		return (1);
	new->str = sh->lex_lst->cont;
	new->fd = fd;
	new->next = NULL;
	if (sh->lex_lst)
		sh->lex_lst = sh->lex_lst->next;
	return (0);
}

/*
prev = -1
*/
int	ft_open_built(t_mini *sh, t_pipe *p, t_fd *fd1, int prev)
{
	while (fd1)
	{
		ft_check_open(p, fd1, prev);
		if (fd1->exp == 1)
			return (err_break(sh, fd1->str, "ambiguous redirect", 1));
		if (fd1->type == 6 || fd1->type == 9)
			p->in_fd = fd1->fd;
		else if (!fd1->str || *fd1->str == '\0')
			return (err_break(sh, "", "No such file or directory", 1));
		else if (fd1->type == 4)
			p->in_fd = open(fd1->str, O_RDONLY);
		else if (fd1->type == 5)
			p->out_fd = open(fd1->str, O_TRUNC | O_CREAT | O_RDWR, 0666);
		else if (fd1->type == 7)
			p->out_fd = open(fd1->str, O_APPEND | O_CREAT | O_RDWR, 0666);
		if (p->in_fd < 0 && (fd1->type == 6 || fd1->type == 9
				|| fd1->type == 4))
			return (err_break(sh, fd1->str, NULL, 1));
		if (p->out_fd < 0 && (fd1->type == 5 || fd1->type == 7))
			return (err_break(sh, fd1->str, NULL, 1));
		prev = fd1->type;
		fd1 = fd1->next;
	}
	return (0);
}
