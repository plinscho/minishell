/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 22:10:06 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/21 19:09:39 by nzhuzhle         ###   ########.fr       */
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
# include <limits.h>
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
typedef struct s_exp	t_exp;

typedef struct s_mini
{
	t_env	*env_lst;
	t_lexer	*lex_lst;
	t_pipe  *pipe_lst;	//What we have in every child, more structs inside.
	t_fd	*hd_lst;	//Here_doc list. 
	t_exp	*exp;		//Expantion struct
	char	*input;		//what we receive by readline
	char	**paths;
//	char	**envp; //the original, using for debugging
	int		exit;		//exit status
	int		pipes; 		//How many pipes are there
	t_exec	*exe;		//another struct with the variables i use in execution 
	char	**env;		//the env double array used by the execv. Each time "export" is called, rebuild it
	int		power_on;
}	t_mini;

//###########################################################################################

//	BUILTINS !

int		ft_env(t_mini *sh, t_pipe *p);		// Ready
int		ft_export(t_mini *sh, t_pipe *p);	// Ready
int		ft_pwd(t_mini *sh, t_pipe *p);		// Ready
int		ft_exit(t_mini *sh);	// Ready | check exit value
int		ft_cd(t_mini *sh, t_pipe *p);		// Ready | Leaks!!
int		ft_unset(t_mini *sh, t_pipe *p);	// Reeady
int		ft_echo(t_mini *sh, t_pipe *p);


//###########################################################################################

//			--	--	MAIN	--	--
/***** main.c  *********************************/
int		minishell(t_mini *sh);

/***** initialize.c - initializing and cleaning sh!!! *****/
int		sh_init(t_mini *sh, char **env);
//void	sh_del(t_mini *sh);	// This is only used when exiting  the shell, we dont want to free the env between readlines
void		sh_clean(t_mini *sh);
t_mini	*sh_restore(t_mini **sh, t_lexer *lex, t_fd *hd); //This function restores the initial position of all the lists clean all of them after iteration
int		sh_loop_init(t_mini *sh); // parses the path and the env each time when a new loop starts
int		allocate_exe(t_mini *sh); //allocates a variables struct for execution
/*************************************************/

//			--	--	HERE_DOC	--	--

/***** heredoc.c - after checking unclosed quotes *****/
int		ft_heredoc(t_mini *sh, char *in, int i);
int		find_hd(char *in, int i);
char	*keyword_hd(t_fd *new, char *in, int *i, char q);
int		save_hd(t_mini *sh, char *key, char *str, int type);
int		hd_close(int fd[]);
/*************************************************/

/***** fd_utils.c - dealing with fd lists *****/
void	fd_add(t_fd **lst, t_fd *new);
void	fd_clean(t_fd **hd, int flag); // if flag=1 - hd, close fd, if flag=0 - pipe fd, dont close
int		fd_init(t_fd *new, t_mini *sh, int fd);
int		ft_open_built(t_mini *sh, t_pipe *p, t_fd *fd1, int prev); // opens all the file descriptors
/*************************************************/


//###########################################################################################

//			--	--	SIGNALS	--	--

void	signals(void);
void	sig_handler(int sig);

//###########################################################################################


//			--	--	ERRORS	--	--

int		quotes_error(t_mini *sh);
int		err_char(t_mini *sh, int token);
void	error_option(char *str1, char *str2);


//void	syntax_error(t_mini *sh, char *seq);
//int		serror(char *s);
int		err_break(t_mini *sh, char *name, char *message, int err); //This one should only be used in the parent process
int		err_exit(t_mini *sh, char *name, char *message, int err);
//###########################################################################################

#endif