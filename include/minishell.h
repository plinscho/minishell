/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 22:10:06 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/30 15:09:16 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "env.h"
# include "lexer.h"
# include "parser.h"
# include "expanser.h"
# include "executor.h"

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
# include <string.h>

//	0. STRUCTS:
typedef struct s_envlst	t_env;
typedef struct s_lexer	t_lexer;
typedef struct s_pipe	t_pipe;
typedef struct s_fd		t_fd;
typedef struct s_exec	t_exec;

typedef struct s_mini
{
	t_lexer	*lex_lst;	//change to lex_lst
	t_env	*env_lst;	//change to env_lst
	t_pipe  *pipe_lst;	//What we have in every child, more structs inside.
	t_fd	*hd_lst;	//Here_doc list. 
	char	*input;		//what we receive by readline
	char	**paths;
	char	**envp; //the original, using for debugging
	int		exit;		//int designed to exit the readline loop and finish the shell
	int		pipes; 		//How many pipes are there
	t_exec	*exe;		//another struct with the variables i use in execution 
	char	**env;		//the env double array used by the execv. Each time "export" is called, rebuild it
	int		power_on;
}	t_mini;

//###########################################################################################

//			--	--	MAIN	--	--
/***** main.c  *********************************/
int		minishell(t_mini *sh);

/***** initialize.c - initializing and cleaning sh!!! *****/
int		sh_init(t_mini *sh, char **env);
//void	sh_del(t_mini *sh);	// This is only used when exiting  the shell, we dont want to free the env between readlines
int		sh_clean(t_mini *sh, int err);
t_mini	*sh_restore(t_mini **sh, t_lexer *lex, t_fd *hd); //This function restores the initial position of all the lists clean all of them after iteration
int		sh_loop_init(t_mini *sh); // parses the path and the env each time when a new loop starts
int	allocate_exe(t_mini *sh); //allocates a variables struct for execution

//			--	--	HERE_DOC	--	--

/***** heredoc.c - after checking unclosed quotes *****/
int		ft_heredoc(t_mini *sh, char *in);
int		find_hd(char *in, int i);
char	*keyword_hd(t_fd *new, char *in, int *i);
int		save_hd(char *key, char *str);

/***** fd_utils.c - dealing with fd lists *****/
void	fd_add(t_fd **lst, t_fd *new);
void	fd_clean(t_fd **hd, int flag); // if flag=1 - hd, close fd, if flag=0 - pipe fd, dont close
void	fd_init(t_fd *new, t_mini *sh, int fd);


//###########################################################################################

//			--	--	SIGNALS	--	--

void	signals(void);
void	sig_handler(int sig);

//###########################################################################################


//			--	--	ERRORS	--	--

int		quotes_error(t_mini *sh);
//void	syntax_error(t_mini *sh, char *seq);
int		serror(char *s);
int		err_break(t_mini *sh, char *name, char *message, int err); //This one should only be used in the parent process
int		err_exit(t_mini *sh, char *name, char *message, int err);
//###########################################################################################

#endif