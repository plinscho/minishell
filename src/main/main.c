#include "../../include/minishell.h"
#include <stdlib.h>

void	sh_init(t_mini *sh, char **env);
void	minishell_boom(t_mini sh);

/*
	The main function only works as a initialization function
	and we call the minishell function inside a loop that exits only
	when we want to. 
*/
int main(int argc, char **argv, char **env)
{
	t_mini		sh;	//	THE STRUCT!
    char		*input = NULL;

	(void)argc;
	(void)argv;
	sh_init(&sh, env);
    while (1)
    {
        input = readline("kebab> ");
        if (!input || *input != '\0') // in case we recieved an empty line
            break;
		printf("\n[MAIN]\ninput: %s\n\n", input);


		
        if (input || *input) add_history(input);	// add command in history line

		if (lexer(input, sh.lst_lexer)) // it means that a malloc failed, my lex_clean cleaned input and list
			minishell_boom(sh);
		int i = 1;
    	while (sh.lst_lexer)
    	{
			printf("node %i -- content: %s, type; %i\n", i, sh.lst_lexer->cont, sh.lst_lexer->token); //erase
       	 	i++;
        	lex_list = lex_list->next; 
    	}
	}
	free(input);
	minishell_boom(sh);
    return (0);
}


/*
	Terminates all processes.
*/
void	minishell_boom(t_mini sh)
{

	lex_clean(sh.lst_lexer);
	printf("[MS_BOOM] Exiting...\n");
	return ;
}

/*
	This function is designed to be safe to free when whe are done
	with the minishell. If we keep all the mallocs inside this struct 
	maybe we wont have a hard time debugging leaks :D
*/
void	sh_init(t_mini *sh, char **env)
{
	t_lexer 	**lex_list = NULL;
//	signal_init();
	sh->og_env = env;
	sh->lst_env = env_head(env);
	sh->lst_lexer = lex_list;
	

}