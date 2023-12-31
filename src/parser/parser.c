/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:26:04 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/22 17:16:22 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lexer	*next_word(t_lexer *temp)
{
	int	f;

	f = 0;
	while (temp && temp->token != 8)
	{
		if (temp->token > 3 && !f)
			f++;
		else if (temp->token < 4 && temp->token > 0 && f)
			f = 0;
		else if (temp->token < 4 && temp->token > 0 && !f)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	count_cmd(t_lexer *temp)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (temp && temp->token != 8)
	{
		if (temp->token < 4 && temp->token > 0 && !flag)
			i++;
		else if (temp->token < 4 && temp->token > 0 && flag)
			flag = 0;
		else if (temp->token > 3)
			flag++;
		temp = temp->next;
	}
	return (i);
}

/*
This function creates a double array of commands,
using the tokens allocated in the lexer list.
*/
int	parse_cmd(t_pipe *new, t_lexer *temp, t_mini *sh, int j)
{
	int	i;

	i = count_cmd(temp);
	new->cmd = (char **) malloc(sizeof(char *) * (i + 1));
	if (!new->cmd)
		return (1);
	while (sh->lex_lst && sh->lex_lst->token < 4)
	{
		if (sh->lex_lst->token != 0)
		{
			new->cmd[j++] = sh->lex_lst->cont;
		}
		sh->lex_lst = sh->lex_lst->next;
	}
	temp = sh->lex_lst;
	while (j < i)
	{
		temp = next_word(temp);
		new->cmd[j++] = temp->cont;
		temp = temp->next;
	}
	new->cmd[j] = NULL;
	return (0);
}

/*
This function creates a file descriptor node and initializes
it with the information from lexer and heredoc lists.
*/
int	parse_redir(t_pipe *new, t_lexer *lex, t_fd *hd, t_mini *sh)
{
	t_fd	*fd_new;
	int		check;

	fd_new = NULL;
	check = 0;
	fd_new = malloc(sizeof(t_fd));
	if (!fd_new)
		return (1);
	fd_add(&(new->fd_lst), fd_new);
	if ((lex->token > 3 && lex->token < 6) || lex->token == 7)
		check = fd_init(fd_new, sh, -2);
	else if (lex->token == 6)
	{
		check = fd_init(fd_new, sh, hd->fd);
		sh->hd_lst = hd->next;
	}
	if (check)
		return (1);
	return (0);
}

/*
This function reads the list of tokens and group them in the way is needed for 
execution.
It creates pipe list, the nodes of this list are devided by pipes.
In every node it prses a double array of commands and a list of all file 
descriptors we have in this pipe. 
To create the pipe nodes it iterates the heredoc list and the lexer list,
so it saves the head of the lists 
in the beginning to restore the initial position in sh at the end 
(or in case of a mistake).
*/
int	parser(t_mini *sh, t_lexer *lex, t_fd *hd, t_pipe *new)
{
	while (sh->lex_lst)
	{
		new = malloc(sizeof(t_pipe));
		if (!new)
			return (err_break(sh_re(&sh, lex, hd), "malloc", NULL, 12));
		pipe_init(new);
		pipe_add(sh, new);
		while (sh->lex_lst && sh->lex_lst->token != 8)
		{
			if (sh->lex_lst->token > 3 && sh->lex_lst->token < 8)
				sh->check = parse_redir(new, sh->lex_lst, sh->hd_lst, sh);
			else if (sh->lex_lst->token > 0 && sh->lex_lst->token < 4 && \
			!new->cmd)
				sh->check = parse_cmd(new, sh->lex_lst, sh, 0);
			else
				sh->lex_lst = sh->lex_lst->next;
			if (sh->check)
				return (err_break(sh_re(&sh, lex, hd), "malloc", NULL, 12));
		}
		if (sh->lex_lst)
			sh->lex_lst = sh->lex_lst->next;
	}
	sh_re(&sh, lex, hd);
	return (0);
}
