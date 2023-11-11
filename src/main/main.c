#include "../../include/minishell.h"




//	This fuinction is meant to erase the cases that input in wrong. Lexer and parser to begin with
//	We can add more functions later.
int	minishell(t_mini *sh)
{
	char	*input = NULL;
	(void)sh;
	input = readline("minishell$> ");
	if (!input || *input == '\0')
		return (1);
//	if (ft_here_doc(sh, sh->input, &(sh->hd_lst)))
//		return (1);	// break the loop code malloc error return (ft_error)

//		Here we add a prelexer that checks all the syntax errors and if there is anything except spaces

	ft_printf("Input passed\n");
//	if (lexer(sh->input, sh, &(sh->lex_lst))) // it means that a malloc failed, my lex_clean cleaned input and list
//		return (1);	// we should clean the heredoc 

//	if (parser(&sh, sh->lex_lst, sh->hd_lst, 0))
//		return (1); //we should clean all - I do it in the parser + we should write an error message function 


	//sh->power_on = 0;	//powers off the while and exits.
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
			sh.power_on = 0;
		print_lexer(&sh);
		if (sh.power_on == 0)
			printf("\nAPAGANDO...\n");
//		print_parser(&sh);
		sh_clean(&sh, 0);
	}
	free_env(&sh);
	return (0);
}
