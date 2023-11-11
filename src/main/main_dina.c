#include "../../include/minishell.h"

/*  we initialize the struct for the first time and parse the environment???*/
int	sh_init(t_mini *sh, char **env)
{
	sh->env	= NULL; // Let's parse here?
	sh->env_lst = NULL; // Let's parse here?
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

	sh->power_on = 1;
}

int	sh_clean(t_mini **sh, int err)
{
	if ((*sh)->lex_lst)
		lex_clean(&((*sh)->lex_lst));
	if ((*sh)->hd_lst)
		hd_clean(&((*sh)->hd_lst));
	if ((*sh)->input)
	{
		free((*sh)->input);
		(*sh)->input = NULL;
	}
	// here will be pipe clean:
	/*if ((*sh)->pipe_lst)
		pipe_clean(&((*sh)->pipe_lst), in, 0);*/
	return (err);
}

//	This fuinction is meant to erase the cases that input in wrong. Lexer and parser to begin with
//	We can add more functions later.
int	minishell(t_mini *sh)
{
	t_lexer *lex_list = NULL;

	sh->input = readline("minishell$> ");
	if (ft_here_doc(&sh, sh->input, &(sh->hd_lst)))
		return (1);	// break the loop code malloc error return (ft_error)

//		Here we add a prelexer that checks all the syntax errors and if there is anything except spaces
	if (lexer(sh->input, &sh, &(sh->lex_lst))) // it means that a malloc failed, my lex_clean cleaned input and list
		return (1);	// we should clean the heredoc 
	if (parser(&sh, sh->lex_lst, sh->hd_lst, 0))
		return (1); //we should clean all - I do it in the parser + we should write an error message function 

	
	//sh->power_on = 0;	//powers off the while and exits.
}

int main(int argc, char **argv, char **env)
{
	t_mini	sh;
	int i;
//	t_pipe	*parse = NULL;
//	t_hd	*hd = NULL;

	(void)argc;
	(void)argv;
	
	if (sh_init(&sh, env))
		return (1);
	while (sh.power_on)
	{
		if (minishell(&sh))
			sh.power_on--;
		print_lexer(&sh);
		print_parser(&sh);
		sh_clean(&sh, 0);
	}
	free_env(&sh);
	return (0);
}
