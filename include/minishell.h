/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:02:59 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/07 17:03:07 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "../src/lexer/lexer.h"
# include "../src/signals/signals.h"
# include "../src/parser/parser.h"
# include "../src/lexer/lexer.h"
# include "../src/env/env.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

	//STRUCTS:

typedef struct s_mini
{
	t_lexer	*lex_lst;  //change to lex_lst
	t_env	*env_lst;  //change to env_lst
	t_pipe  *pipe_lst;  //What we have in every child, more structs inside.
	t_fd	*hd_lst;	 //Here_doc list. 
	char	*input;		//what we receive by readline
	int		exit;		 //int designed to exit the readline loop and finish the shell
	int		pipes; 		 //How many pipes are there
	char	**env;		 //the env double array used by the execv. Each time "export" is called, rebuild it

} t_mini;

/*	TOKENS	*/

/* The list of tokens:
0 = space; - content is null
1 = word;
2 = ' single quotes string;
3 = " double quotes string; 
4 = < infile redirection; - content is nullcheckout 
5 = > outfile redirection; - content is null
6 = << heredoc sign; - content is null
7 = >> outfile append redirection; - content is null
8 = | pipe; - content is null
*/

#endif
