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

int main(int argc, char **argv, char **envp)
{
    char    *input = NULL;
	t_lexer *lex_list = NULL;
	char	**cp_env = NULL; 
   int i;

	if (argc != 1 && argv[0])
		return (1);
	cp_env = cpy_env(envp);
	if (!cp_env)
		return (1);
	while (42)
	{
		input = readline("minishell> ");  
        if (!input) // in case we recieved an empty line
            break;
//		printf("[MAIN]You entered: %s\n\n", input);
		if (lexer(input, &lex_list)) // it means that a malloc failed, my lex_clean cleaned input and list
			return (1);
		i = 1;
    	while (lex_list)
    	{
			printf("node %i -- content: %s, type; %i\n", i, lex_list->cont, lex_list->token); //erase
       	 	i++;
        	lex_list = lex_list->next; 
    	}
	}
	lex_clean(&lex_list, &input);
	return (0);
}
