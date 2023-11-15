/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:41:40 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/15 20:44:15 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/lexer.h"

void	pipe_init(t_pipe *pip)
{
	pip->cmd = NULL;
//	pip->paths = NULL;
	pip->fd_lst = NULL;
	pip->in_fd = -2;
	pip->out_fd = -2;
//	pip->vars = NULL;
}

void	pipe_add(t_pipe **lst, t_pipe *new)
{
	t_pipe	*temp;

	if (!*lst)
		*lst = new;
	temp = *lst;
	while (temp -> next)
		temp = temp -> next;
	temp -> next = new;
}

/* This function initializes the file descriptor node in 3 cases:
1. if type is 0 and token is NOT 6 - the fd is -2, lex->token is the type of redirection, and then 
the filename.
2. if type is 0 and token is 6 - the fd is the open fd where the heredoc is stored, 
lex->token is the type of redirection, and then the keyword. 
3. if type is NOT 0 (then it's 4) - the fd is -2, 4 is the type of redirection, and lex->str is 
the filename. 

It also frees the used nodes */

void	fd_init(t_fd *new, t_lexer *lex, int fd, int type)
{
	t_lexer	*temp;

	temp = lex;
	if (!type)
	{
		new->type = lex->token;
		lex = lex->next;
		free(temp);
		temp = lex;
		if (lex->token == 0)
		{
			lex = lex->next;
			free (temp);
			temp = lex;
		}
	}
	else
		new->type = type;
	new->str = lex->cont;
	new->fd = fd;
	new->next = NULL;
	lex = lex->next;
	free(temp);
}

void	print_parser(t_mini *sh)
{
	t_pipe	*tmp = NULL;
	int	i;

	tmp = sh->pipe_lst;
	i = 0;
	while (tmp)
   	{
		printf("pipe %i -- cmd: %p, fd: %p\n", i, tmp->cmd, tmp->fd_lst);
	 	i++;
       	tmp = tmp->next; 
    }
}