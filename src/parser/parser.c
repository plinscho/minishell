/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:26:04 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/15 20:26:59 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int	parse_cmd(t_pipe *new, t_lexer *temp, t_mini *sh)
{
	int		i;

	i = 0;
//	printf("[P_CMD]token: %i\n", temp->token); //erase
	while (temp && temp->token < 4)
	{
		if (temp->token != 0)
			i++;
		temp = temp->next;
	}
//	printf("[P_CMD]n of cmds: %i\n", i); //erase
	new->cmd = (char **) malloc(sizeof(char*) * (i + 1));
	if (!new->cmd)
		return (1);
	temp = sh->lex_lst;
	i = 0;
	while (sh->lex_lst && sh->lex_lst->token < 4)
	{
		if (sh->lex_lst->token != 0)
		{
			new->cmd[i] = sh->lex_lst->cont;
			i++;
		}
		sh->lex_lst = sh->lex_lst->next;
	}
	new->cmd[i] = NULL;
//	printf("[P_CMD] new lex: %p\n", sh->lex_lst); //erase
	return (0);
}

int	parse_redir(t_pipe *new, t_lexer *lex, t_fd *hd, t_mini *sh)
{
	t_fd	*fd_new;
	
	fd_new = NULL;
	fd_new = malloc(sizeof(t_fd));
	if (!fd_new)
		return (1);
	if ((lex->token > 3 && lex->token < 6) || lex->token == 7)
		fd_init(fd_new, sh, -2, 0);
	else if (lex->token == 6)
	{
		fd_init(fd_new, sh, hd->fd, 0);
		sh->hd_lst = hd->next;
	}
	else
		fd_init(fd_new, sh, -2, 4);
	fd_add(&(new->fd_lst), fd_new);
	return (0);
}
/*
This function reads the list of tokens and group them in the way is needed for execution.
It creates pipe list, the nodes of this list are devided by pipes.
In every 
*/
int	parser(t_mini *sh, t_lexer *lex, t_fd *hd, int check)
{
	t_pipe	*new;

	new = NULL;
	while (sh->lex_lst)
	{
		new = malloc(sizeof(t_pipe));
		if (!new)
			return (sh_clean(sh_restore(&sh, lex, hd), 2));
//		printf("[PARSER]lex 1 -- content: %s, type; %i\n", sh->lex_lst->cont, sh->lex_lst->token); //erase
//		printf("[PARSER]You entered: %i\n", check); //erase
		pipe_init(new);
//		printf("[PARSER]after init: %p\n", new->cmd); //erase
//		printf("[PARSER]before add: %p\n", sh->pipe_lst); //erase
		pipe_add(sh, new);
//		printf("[PARSER]after add: %p\n", sh->pipe_lst); //erase
	// 	return (0); //erase
		if (sh->lex_lst)
//			printf("[PARSER] lex: %s\n", sh->lex_lst->cont); //erase
		while (sh->lex_lst && sh->lex_lst->token != 8)
		{
//			printf("[PARSER] not 8, lex token: %i\n", sh->lex_lst->token); //erase
			if ((sh->lex_lst->token > 3 && sh->lex_lst->token < 8) || (new->cmd && sh->lex_lst->token > 0 && sh->lex_lst->token < 4))
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
			{
//				printf("[check 0] lex: %s\n", (sh)->lex_lst->cont); //erase
				return (sh_clean(sh_restore(&sh, lex, hd), 2));
			}
		}
		if (sh->lex_lst)
			sh->lex_lst = sh->lex_lst->next;
	}
	sh_restore(&sh, lex, hd);
	return (0);
}