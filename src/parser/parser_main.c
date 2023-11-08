/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:02:54 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/10/29 17:03:15 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_lexer	*parse_cmd(t_pipe **new, t_lexer *lex)
{
	//we should build a double array of strings until any redirection is met
	//then in echo we will rebuild it
}

t_lexer	*parse_redir(t_pipe **new, t_lexer *lex, t_fd **hd)
{
	//we have 3 cases:
	//1. its one of the < > >>
	//2. its a heredoc
	//3. its a word so we treat it as a <
}

int	parser(t_mini **sh, t_lexer *lex, t_fd *hd)
{
	t_pipe	*new;
//	int		i;

//	i = -1;
	new = NULL;
	while (lex)
	{
		new = malloc(sizeof(t_pipe));
		if (!new)
			return (sh_clean(sh, 2));
		pipe_init(new);
		pipe_add(&((*sh)->pipe_lst), new);
		while (lex && lex->token != 8)
		{
			if ((lex->token > 3 && lex->token < 8) || (new->cmd && \
			lex->token > 0 && lex->token < 4))
				lex = parse_redir(&new, lex, &hd);
			else if (lex->token > 0 && lex->token < 4 && !new->cmd)
				lex = parse_cmd(&new, lex);
			else
				lex = lex->next;
		}
	}


}



int main(int argc, char **argv, char **envp)
{
    char    *input = NULL;
//	t_lexer *lex_list = NULL;
//	t_pipe	*parse = NULL;
//	t_hd	*hd = NULL;
	t_mini	*sh;
//	char	**cp_env = NULL; 
//	int i;

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
//			i = 1;
		if (parser(&sh, sh->lex_lst, &sh->hd_lst))
			break ; //we should clean all - I do it in the parser + we should write an error message function 
    	/*while (lex_list)
    	{
			printf("node %i -- content: %s, type; %i\n", i, lex_list->cont, lex_list->token); //erase
       	 	i++;
        	lex_list = lex_list->next; 
    	}*/
		sh_clean(&sh, 0);
	}
	return (0);
}
