#include "minishell.h"

void	sh_init(t_mini *sh);
void	minishell_boom(t_mini sh, char *input);

/*
	The main function only works as a initialization function
	and we call the minishell function inside a loop that exits only
	when we want to. 
*/
int main(int argc, char **argv, char **env)
{
	t_mini		sh;
    char		*input = NULL;

	(void)argc;
	(void)argv;
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
	return ;
}

/*
	This function is designed to be safe to free when whe are done
	with the minishell. If we keep all the mallocs inside this struct 
	maybe we wont have a hard time debugging leaks :D
*/
void	sh_init(t_mini *sh)
{
	sh->exit = 0;
	sh->lst_env = NULL;
	sh->lst_lex = NULL;

}