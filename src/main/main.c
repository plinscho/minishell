#include "../../include/minishell.h"

//	This is a globar variable, I put it here because
//	we will need the information about the struct at all time
//	for instance, when we exit and want to send the error number
//	or if we press Ctrl+C anytime, also the control D exits the shell.

/*
	The main function only works as a initialization function
	and we call the minishell function inside a loop that exits only
	when we want to. 
*/

void	sh_del(t_mini *sh)
{
	if (sh)
		sh_clean(&sh, 0); 	// The 0 represent the error code. Check
	free_env(sh);			// Only free it if sh->exit
}

int		sh_init(t_mini *sh, char **env)
{

	sh->env = NULL;
	sh->lex_lst = NULL;
	sh->hd_lst = NULL;
	sh->pipe_lst = NULL;
	sh->input = NULL;
	sh->exit = 0;
	sh->pipes = 0;
	signals(); 					// This starts the signals Ctrl + C && Ctrl + D.
	if (get_env(sh, env) == -1) // Loads env into the shell. If malloc fails, delete it.
		return (1);
	if (env_converter(sh) == -1) // malloc has failed in the char **.
		return (1);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_mini	sh;
	char	*input = NULL;

	(void)argc;
	(void)argv;
	if (sh_init(&sh, env))
		return (1);
	while (1)
    {
        input = readline("kebab$> ");
        if (!input || *input == '\0') // in case we recieved an empty line
            break;
		printf("[MAIN]You entered: %s\n\n", input);
        free(input);
    }
	if (input)
		free(input);
	sh_del(&sh);
    return (0);
}

