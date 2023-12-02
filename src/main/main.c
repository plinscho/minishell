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
	sh->input = readline("minishell$> ");
	if (!sh->input)
		return (ft_exit(sh));
	add_history(sh->input);
	if (pre_quotes(sh->input))
		return (quotes_error(sh));
	if (lexer(sh, sh->input))
		return (1);
	if (check_syntax(sh->lex_lst))
		return (1);
	if (parser(sh, sh->lex_lst, sh->hd_lst, 0))
		return (1);
	if (executor(sh, sh->pipe_lst, -1, -1))
		return (1);
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
		if (sh.power_on == 0)
			printf("\nPOWERING OFF...\n");
		sh_clean(&sh, 0);
	}
	free_env(&sh);
	return (0);
}
