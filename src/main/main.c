#include "../include/minishell.h"

//	This is a globar variable, I put it here because
//	we will need the information about the struct at all time
//	for instance, when we exit and want to send the error number
//	or if we press Ctrl+C anytime

/*
	The main function only works as a initialization function
	and we call the minishell function inside a loop that exits only
	when we want to. 
*/
int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
    char		*input = NULL;

    while (1)
    {
        input = readline("kebab> ");
        if (!input || *input == '\0') // in case we recieved an empty line
            break;
		printf("[MAIN]You entered: %s\n\n", input);
        free(input);
    }
    return (0);
}
