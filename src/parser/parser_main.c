/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:02:54 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/11 19:36:48 by plinscho         ###   ########.fr       */
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

/*int main(int argc, char **argv, char **envp)
{
    char    *input = NULL;
//	t_lexer *lex_list = NULL;
//	t_pipe	*parse = NULL;
//	t_hd	*hd = NULL;
	t_mini	*sh;
//	char	**cp_env = NULL; 
	int i;

	if (argc != 1 && argv[0])
		return (1);
//	cp_env = cpy_env(envp);
//	if (!cp_env)
//		return (1);
	sh = malloc(sizeof(t_mini));
	if (!sh)
		return (1); // break the loop with the needed exit status
	mini_init(sh); // parse the envp here????
	while (42)
	{
		sh->input = readline("minishell> ");
        if (!sh->input) // in case we recieved an empty line
            break;
//		Here we add a prelexer that will destroy the input str if any open quote and write the error message
		if (ft_here_doc(&sh, sh->input, &(sh->hd_lst)))
			break ; // break the loop code malloc error return (ft_error)
//		printf("[MAIN]You entered: %s\n\n", input);
//		Here we add a prelexer that checks all the syntax errors and if there is anything except spaces
		if (lexer(input, &sh, &(sh->lex_lst))) // it means that a malloc failed, my lex_clean cleaned input and list
			break ; // we should clean the heredoc 
		i = 1;
//		if (parser(&sh, sh->lex_lst, &sh->hd_lst, 0))
//			break ; //we should clean all - I do it in the parser + we should write an error message function 
    	while (sh->lex_lst)
    	{
			printf("node %i -- content: %s, type; %i\n", i, sh->lex_lst->cont, sh->lex_lst->token); //erase
       	 	i++;
        	sh->lex_lst = sh->lex_lst->next; 
    	}
		sh_clean(&sh, 0);
	}
	return (0);
}*/
