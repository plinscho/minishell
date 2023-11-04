<<<<<<< HEAD
#include "../../include/minishell.h"
#include <stdlib.h>

void	sh_init(t_mini *sh, char **env);
void	minishell_boom(t_mini sh);
=======
#include "minishell.h"

void	sh_init(t_mini *sh);
void	minishell_boom(t_mini sh, char *input);
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd

/*
	The main function only works as a initialization function
	and we call the minishell function inside a loop that exits only
	when we want to. 
*/
int main(int argc, char **argv, char **env)
{
<<<<<<< HEAD
	t_mini		sh;	//	THE STRUCT!
=======
	t_mini		sh;
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd
    char		*input = NULL;

	(void)argc;
	(void)argv;
<<<<<<< HEAD
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
=======
	sh_init(&sh);
	get_env(&sh, env);
    while (1 == 1)
    {
        input = readline("kebab> ");
		printf("\n[MAIN]\ninput: %s\n\n", input);
        if (!input) // in case we recieved an empty line
            break;
		if (lexer(input, sh.lst_lex)) // it means that a malloc failed, my lex_clean cleaned input and list
			return (1);
		print_lexer(*sh.lst_lex);
        if (input || *input)
            add_history(input);
        free(input);
    }
	minishell_boom(sh, input);
    return (0);
}

void	minishell_boom(t_mini sh, char *input)	// Terminates shell freeing memory
{
	if (input != NULL)
		free(input);
	env_del(sh.lst_env);
	lex_clean(sh.lst_lex);
	printf("[MS_BOOM] Struct freed!\nExiting...\n");
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd
	return ;
}

/*
	This function is designed to be safe to free when whe are done
	with the minishell. If we keep all the mallocs inside this struct 
	maybe we wont have a hard time debugging leaks :D
*/
<<<<<<< HEAD
void	sh_init(t_mini *sh, char **env)
{
	t_lexer 	**lex_list = NULL;
//	signal_init();
	sh->og_env = env;
	sh->lst_env = env_head(env);
	sh->lst_lexer = lex_list;
	
=======
void	sh_init(t_mini *sh)
{
	sh->exit = 0;
	sh->lst_env = NULL;
	sh->lst_lex = NULL;
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd

}