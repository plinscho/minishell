#include "../../include/minishell.h"

//	This is a globar variable, I put it here because
//	we will need the information about the struct at all time
//	for instance, when we exit and want to send the error number
//	or if we press Ctrl+C anytime, also the control D exits the shell.

/*
	The main function only works as a initialization function
	and we call the minishell function inside a loop that exits only
	when we want to. 

int main(int argc, char **argv, char **env)
{
	t_mini	sh;
	char	*input = NULL;

	(void)argc;
	(void)argv;
	if (sh_init(&sh, env))
		return (1);
	while (sh.power_on) // Cointrolling the loop with sh->power_on, can be called anytime and exits.
    {
        input = readline("kebab$> ");
        if (!input || *input == '\0') // in case we recieved an empty line
            break;
		printf("[MAIN]You entered: %s\n\n", input);



		minishell(&sh, input);
    }
	if (input)
		free(input);
	sh_del(&sh);
    return (0);
}

*/
