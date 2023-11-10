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

static void	sh_init(t_mini *sh, char **env)
{
	sh->env = NULL;
	if (get_env(sh, env) == -1) // Loads env into the shell. If malloc fails, delete it.
		env_del(sh->env_lst);
	signals();

}

int main(int argc, char **argv, char **env)
{
	t_mini	sh;
	char	*input = NULL;

	(void)argc;
	(void)argv;
	sh_init(&sh, env);
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

