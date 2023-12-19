#include "../../include/minishell.h"


/*
	This fucntion works as a collider of the shell parts.
	We can manage the lexer, parser, env, etc from here.
	If you return 1, the minishell will exit. if it's 0, it will give you a new readline
	trough every loop, there is the sh_clean function.
*/
int	minishell(t_mini *sh)
{
	sh_loop_init(sh);
	sh->input = readline("kebab$> ");
	if (!sh->input)
		return (ft_exit(sh));
	if (check_input(sh->input)) // It's not a mistake, just empty line
		return (0);
//	printf("[MAIN] After check input: %i\n", sh->exit); //erase
  	add_history(sh->input);
	if (pre_quotes(sh->input))
		return (quotes_error(sh));
//	printf("[MAIN] After prequotes: %i\n", sh->exit); //erase
	if (ft_heredoc(sh, sh->input))
		return (1);	// break the loop code malloc error return (ft_error)
	if (lexer(sh, sh->input)) // it means that a malloc failed, my lex_clean cleaned input and list
		return (1);	// we should clean the heredoc --> do it in the sh_clean
//	print_lexer(sh); //erase
	if (expanser(sh, sh->lex_lst))
    	return (1);
//	printf("[MAIN] After expansion: %i\n", sh->exit); //erase
	if (check_syntax(sh, sh->lex_lst))
		return (1);
//	printf("--------------------\n"); //erase	
//	if (trim_quotes(sh, sh->lex_lst))
//		return (1);
///	printf("after check syntax: %s\n", "4"); //erase
//	print_lexer(sh);
	if (parser(sh, sh->lex_lst, sh->hd_lst, 0))
		return (1); //we should clean all - I do it in the parser + we should write an error message function 
//	printf("[MAIN] After parsing: %i\n", sh->exit); //erase
//	print_parser(sh->pipe_lst);
	if (executor(sh, sh->pipe_lst, -1, -1))
		return (1);
//	printf("[MAIN] After execution: %i\n", sh->exit); //erase
//	printf("After exec exit status: %i\n", sh->exit); //erase
	return (0);	
}

int main(int argc, char **argv, char **env)
{
	t_mini	sh;
	(void)argc;
	(void)argv;

	if (sh_init(&sh, env))
		return (1);
	while (sh.power_on)
	{
		minishell(&sh);
//		print_lexer(&sh);
//		if (sh.power_on == 0)
//			printf("\nPOWERING OFF...\n");
//		print_parser(&sh);
//		printf("\n[MAIN] clean in main:\n------------%i----------\n", 2); //erase
//		print_exp(sh.exp);
		sh_clean(&sh);
//		printf("\n\n[MAIN] ------------   %s   ----------\n\n", "AFTER CLEAN"); //erase
	}
	free_env(&sh);
	return (sh.exit);
}
