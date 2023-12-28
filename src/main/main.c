/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 22:46:41 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/28 14:46:37 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	This fucntion works as a collider of the shell parts.
	We can manage the lexer, parser, env, etc from here.
	If you return 1, the minishell will exit. if it's 0, it will give you a 
	new readline trough every loop, there is the sh_clean function.
*/
int	minishell(t_mini *sh)
{
	init_signals(NORM);
	do_sigign(SIGQUIT);
	sh->input = readline("kebab$> ");
	if (!sh->input)
		return (ft_exit(sh));
	do_sigign(SIGINT);
	add_history(sh->input);
	if (check_input(sh->input))
		return (0);
	if (pre_quotes(sh->input))
		return (quotes_error(sh));
	if (ft_heredoc(sh, sh->input, 0))
		return (1);
	if (lexer(sh, sh->input))
		return (1);
	if (expanser(sh, sh->lex_lst, 0))
		return (1);
	if (!sh->lex_lst || check_syntax(sh, sh->lex_lst, -1))
		return (1);
	if (!sh->lex_lst || parser(sh, sh->lex_lst, sh->hd_lst, NULL))
		return (1);
	if (executor(sh, sh->pipe_lst, -1, -1))
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	sh;

	(void)argc;
	(void)argv;
	g_sig_rec = 0;
	sh_init(&sh, env);
	while (sh.power_on)
	{
		if (!sh_loop_init(&sh))
			minishell(&sh);
		sh_clean(&sh);
		if (g_sig_rec == 1)
		{
			sh.exit = 1;
			g_sig_rec = 0;
		}
	}
	free_env(&sh);
	return (sh.exit);
}
