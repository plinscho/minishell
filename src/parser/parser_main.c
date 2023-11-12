/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:02:54 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/11 20:22:18 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	parse_cmd(t_pipe *new, t_lexer *lex, t_mini *sh)
{
	t_lexer	*temp;
	int		i;

	i = 0;
	temp = lex;
	printf("[P_CMD]token: %i\n", temp->token); //erase
	while (temp && temp->token < 4)
	{
		if (temp->token != 0)
			i++;
		temp = temp->next;
	}
	printf("[P_CMD]n of cmds: %i\n", i); //erase
	new->cmd = (char **) malloc(sizeof(char*) * (i + 1));
	if (!new->cmd)
		return (1);
	temp = lex;
	i = 0;
	while (lex && lex->token < 4)
	{
		if (lex->token != 0)
		{
			new->cmd[i] = lex->cont;
			printf("[P_CMD] cmd %i: %s\n", i, new->cmd[i]); //erase
			i++;
		}
		lex = lex->next;
	}
	new->cmd[i] = NULL;
	sh->lex_lst = lex;
	printf("[P_CMD] new lex: %p\n", lex); //erase
	return (0);
}

int	parse_redir(t_pipe *new, t_lexer *lex, t_fd *hd, t_mini *sh)
{
	t_fd	*fd_new;
	t_fd	*temp;
	
	fd_new = NULL;
	fd_new = malloc(sizeof(t_fd));
	if (!fd_new)
		return (1);
	if ((lex->token > 3 && lex->token < 6) || lex->token == 7)
		fd_init(fd_new, lex, -2, 0);
	else if (lex->token == 6)
	{
		fd_init(fd_new, lex, hd->fd, 0);
		temp = hd; // not the correct way - try to free it after parsing
		hd = hd->next;
		free(temp);
	}
	else
		fd_init(fd_new, lex, -2, 4);
	hd_add(&(sh->hd_lst), fd_new); //change to add last here
	return (0);
}

int	parser(t_mini **sh, t_lexer *lex, t_fd *hd, int check)
{
	t_pipe	*new;

	new = NULL;
	while (lex)
	{
		new = malloc(sizeof(t_pipe));
		if (!new)
			return (sh_clean(sh, 2));
		printf("[PARSER]You entered: %i\n", check); //erase
		pipe_init(new);
		printf("[PARSER]after init: %p\n", new->cmd); //erase
		printf("[PARSER]before add: %p\n", (*sh)->pipe_lst); //erase
		pipe_add(&((*sh)->pipe_lst), new);
		printf("[PARSER]after add: %p\n", (*sh)->pipe_lst); //erase
		if (lex)
			printf("[PARSER] lex: %s\n", lex->cont); //erase
		while (lex && lex->token != 8)
		{
			if ((lex->token > 3 && lex->token < 8) || (new->cmd && lex->token > 0 && lex->token < 4))
				check = parse_redir(new, lex, hd, *sh);
			else if (lex->token > 0 && lex->token < 4 && !new->cmd)
				check = parse_cmd(new, lex, *sh);
			else
				lex = lex->next;
			if ((*sh)->lex_lst)
				printf("[PARSER] lex1: %s\n", (*sh)->lex_lst->cont); //erase
			printf("[PARSER] new lex2: %p\n", (*sh)->lex_lst); //erase
			printf("check: %i\n", check); //erase
			if (check != 0)
			{
				printf("[check 0] lex: %s\n", lex->cont); //erase
				return (sh_clean(sh, 2));
			}
			lex = (*sh)->lex_lst;
		}
		if (lex)
			lex = lex->next;
	}
	return (0);
}
