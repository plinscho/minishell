/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 22:10:06 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/15 20:59:30 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

//	0. STRUCTS:
// We need to define the structs in here, but onnly like this:

typedef struct s_lexer	t_lexer;
typedef struct s_envlst	t_env;
typedef struct s_pipe	t_pipe;
typedef struct s_fd		t_fd;

typedef struct s_mini
{
	t_lexer	*lex_lst;  
	t_env	*env_lst;  
	t_pipe  *pipe_lst;  //What we have in every child, more structs inside.
	t_fd	*hd_lst;	 //Here_doc list. 
	char	*input;		//what we receive by readline
	int		exit;		 //int designed to exit the readline loop and finish the shell
	int		pipes; 		 //How many pipes are there
	char	**env;		 //the env double array used by the execv. Each time "export" is called, rebuild it

	char	power_on;
	
}	t_mini;

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

//###########################################################################################

//			--	--	MAIN	--	--

int		sh_init(t_mini *sh, char **env);
void	sh_del(t_mini *sh);	// This is only used when exiting  the shell, we dont want to free the env between readlines
int		sh_clean(t_mini *sh, int err);

//###########################################################################################

//			--	--	SIGNALS	--	--

void	signals(void);
void	sig_handler(int sig);


//###########################################################################################

//			--	--	ERRORS	--	--

void	synt_error(t_mini *sh);

//###########################################################################################

#endif