#include "../include/minishell.h"

//	This is a globar variable, I put it here because
//	we will need the information about the struct at all time
//	for instance, when we exit and want to send the error number
//	or if we press Ctrl+C anytime

t_signal	*sig_list;

/*
	The main function only works as a initialization function
	and we call the minishell function inside a loop that exits only
	when we want to. 
*/
int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
    char		*input = NULL;
	t_mini		*sh = NULL;	//	THE STRUCT!
    t_lexer 	*lex_list = NULL;

	signal_init();

    while (1)
    {
        input = readline("kebab> ");
        if (!input || *input != '\0') // in case we recieved an empty line
            break;
		printf("[MAIN]You entered: %s\n\n", input);
        lex_list = lexer(input);
        if (input && *input)
            add_history(input);
		char_an(input);
		signal_mgr();
        free(input);
    }
    return (0);
}

void	minishell(t_mini sh)
{


}