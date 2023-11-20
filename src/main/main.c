#include "../../include/minishell.h"


/*
	This fucntion works as a collider of the shell parts.
	We can manage the lexer, parser, env, etc from here.
	If you return 1, the minishell will exit. if it's 0, it will give you a new readline
	trough every loop, there is the sh_clean function.
*/
int	minishell(t_mini *sh)
{
	char	*input = NULL;

	sh->input = readline("minishell$> ");
	if (!sh->input)
	{
		exit (1);		//  need to change it into our exit builtin function.
	}
	if (pre_quotes(sh->input))
	{
		synt_error(sh);
		free(sh->input);
		return (sh->exit);
	}

//	if (ft_here_doc(sh, sh->input, &(sh->hd_lst)))
//		return (1);	// break the loop code malloc error return (ft_error)

//		Here we add a prelexer that checks all the syntax errors and if there is anything except spaces

	if (lexer(sh, sh->input)) // it means that a malloc failed, my lex_clean cleaned input and list
		return (1);	// we should clean the heredoc --> do it in the sh_clean

//	print_env(sh->env_lst, sh->env);
//	print_lexer(sh);
	



//	if (parser(&sh, sh->lex_lst, sh->hd_lst, 0))
//		return (1); //we should clean all - I do it in the parser + we should write an error message function 
	if (sh->input)
		free(input);
	return (0);	
}

int main(int argc, char **argv, char **env)
{
	t_mini	sh;
//	t_pipe	*parse = NULL;
//	t_hd	*hd = NULL;

	(void)argc;
	(void)argv;
	
	if (sh_init(&sh, env))
		return (1);
	while (sh.power_on)
	{
		if (minishell(&sh))
			continue;
//		print_lexer(&sh);
		if (sh.power_on == 0)
			printf("\nPOWERING OFF...\n");
//		print_parser(&sh);
		sh_clean(&sh, 0);
	}
	free_env(&sh);
	return (0);
}
