#include "../../include/minishell.h"


/*
	This fucntion works as a collider of the shell parts.
	We can manage the lexer, parser, env, etc from here.
	If you return 1, the minishell will exit. if it's 0, it will give you a new readline
	trough every loop, there is the sh_clean function.
*/
int	minishell(t_mini *sh)
{
//	sh_loop_init(sh);
	if (env_converter(sh) == -1) // malloc has failed in the char **.
		return (1);
	sh->input = readline("minishell$> ");
	if (!sh->input || ft_strcmp(sh->input, "exit") == 0)
		return (ft_exit(sh));
	print_env(sh->env_sec, NULL);
	if (pre_quotes(sh->input))
		return (quotes_error(sh));
	if (lexer(sh, sh->input)) // it means that a malloc failed, my lex_clean cleaned input and list
		return (1);	// we should clean the heredoc --> do it in the sh_clean
	if (check_syntax(sh->lex_lst)) // This function checks for the syntax errors. It operates using tokens logic.
		return (1);
	if (parser(sh, sh->lex_lst, sh->hd_lst, 0))
		return (1); //we should clean all - I do it in the parser + we should write an error message function 
	if (executor(sh, sh->pipe_lst, -1, -1))
		return (1);
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
		minishell(&sh);
//		print_lexer(&sh);
		if (sh.power_on == 0)
			printf("\nPOWERING OFF...\n");
//		print_parser(&sh);
		add_history(sh.input);
		sh_clean(&sh, 0);
	}
	free_env(&sh);
	return (0);
}
