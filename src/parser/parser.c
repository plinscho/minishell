/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:26:04 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/22 16:00:53 by nzhuzhle         ###   ########.fr       */
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
//	printf("[P_CMD]token: %i\n", temp->token); //erase
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
This function creates a double array of commands, using the tokens allocated in the lexer list.
*/
int	parse_cmd(t_pipe *new, t_lexer *temp, t_mini *sh)
{
	int	i;
	int	j;

	i = count_cmd(temp);
//	printf("[P_CMD]token: %i\n", temp->token); //erase
//	printf("[P_CMD]n of cmds: %i\n", i); //erase
	new->cmd = (char **) malloc(sizeof(char*) * (i + 1));
	if (!new->cmd)
		return (1);
//	temp = sh->lex_lst;
	j = 0;
	while (sh->lex_lst && sh->lex_lst->token < 4)
	{
		if (sh->lex_lst->token != 0)
		{
			new->cmd[j] = sh->lex_lst->cont;
//			printf("[P_CMD] cmd1 [%i]: %s, i - %i\n", j, sh->lex_lst->cont, i); //erase
			j++;
		}
		sh->lex_lst = sh->lex_lst->next;
	}
	temp = sh->lex_lst;
//	printf("[P_CMD]token: %i\n", temp->token); //erase
	while (j < i)
	{
		temp = next_word(temp);
		new->cmd[j++] = temp->cont;
//		printf("[P_CMD] cmd2 [%i]: %s\n", j - 1, temp->cont); //erase
		temp = temp->next;
	}
	new->cmd[j] = NULL;
//	print_arr(new->cmd);
//	printf("[P_CMD] new lex: %p\n", sh->lex_lst); //erase
	return (0);
}

/*
This function creates a file descriptor node and initializes it with the information from lexer and heredoc lists.
*/
int	parse_redir(t_pipe *new, t_lexer *lex, t_fd *hd, t_mini *sh)
{
	t_fd	*fd_new;
	int		check;
	
	fd_new = NULL;
	fd_new = malloc(sizeof(t_fd));
	check = 0;
	if (!fd_new)
		return (1);
	if ((lex->token > 3 && lex->token < 6) || lex->token == 7)
		check = fd_init(fd_new, sh, -2);
	else if (lex->token == 6)
	{
		check = fd_init(fd_new, sh, hd->fd);
		sh->hd_lst = hd->next;
	}
	if (check)
		return (1);
	fd_add(&(new->fd_lst), fd_new);
	return (0);
}

/*
This function reads the list of tokens and group them in the way is needed for execution.
It creates pipe list, the nodes of this list are devided by pipes.
In every node it prses a double array of commands and a list of all file descriptors we have in this pipe. 
To create the pipe nodes it iterates the heredoc list and the lexer list, so it saves the head of the lists 
in the beginning to restore the initial position in sh at the end (or in case of a mistake).
*/
int	parser(t_mini *sh, t_lexer *lex, t_fd *hd, int check)
{
	t_pipe	*new;

	new = NULL;
	while (sh->lex_lst)
	{
		new = malloc(sizeof(t_pipe));
		if (!new)
			return (err_break(sh_restore(&sh, lex, hd), "malloc", NULL, 12));
//		printf("[PARSER]lex 1 -- content: %s, type; %i\n", sh->lex_lst->cont, sh->lex_lst->token); //erase
//		printf("[PARSER]You entered: %i\n", check); //erase
		pipe_init(new);
//		printf("[PARSER]after init: %p\n", new->cmd); //erase
//		printf("[PARSER]before add: %p\n", sh->pipe_lst); //erase
		pipe_add(sh, new);
//		printf("[PARSER]after add: %p\n", sh->pipe_lst); //erase
	// 	return (0); //erase
//		if (sh->lex_lst)
//			printf("[PARSER] lex: %s\n", sh->lex_lst->cont); //erase
		while (sh->lex_lst && sh->lex_lst->token != 8)
		{
//			printf("[PARSER] not 8, lex token: %i\n", sh->lex_lst->token); //erase
			if (sh->lex_lst->token > 3 && sh->lex_lst->token < 8)
				check = parse_redir(new, sh->lex_lst, sh->hd_lst, sh);
			else if (sh->lex_lst->token > 0 && sh->lex_lst->token < 4 && !new->cmd)
				check = parse_cmd(new, sh->lex_lst, sh);
			else
				sh->lex_lst = sh->lex_lst->next;
//			if (sh->lex_lst)
//				printf("[PARSER] lex1: %s\n", sh->lex_lst->cont); //erase
//			printf("[PARSER] new lex2: %p\n", sh->lex_lst); //erase
	//		printf("[PARSER] new pipe_lst->cmd: %p\n", (sh)->pipe_lst->cmd); //erase
//			printf("check: %i\n", check); //erase
			if (check)
				return (err_break(sh_restore(&sh, lex, hd), "malloc", NULL, 12));
		}
		if (sh->lex_lst)
			sh->lex_lst = sh->lex_lst->next;
	}
	sh_restore(&sh, lex, hd);
	return (0);
}