/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 22:10:06 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/21 18:04:56 by nzhuzhle         ###   ########.fr       */
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
	
typedef struct s_envlst
{
	char				*env_full;
	char				*env_val;
	char				*env_key;
	struct s_envlst		*next;
	
} t_env;

typedef struct s_lexer
{
    char    *cont;
    int     token;
    struct s_lexer  *prev;
    struct s_lexer  *next;
} t_lexer;

				/* a list with all the files names with redirections */
				
typedef struct s_fd
{
	int		fd;		// file descriptor
	int		type;	// 4 - infile, 5 - outfile, 6 - here_doc, 7 - outfile append, 9 - heredoc with keyword with ''
	char	*str;	// keyword in heredoc, or the filename
	struct s_fd	*next;
}	t_fd;

				/* a list with commands for child processes */
				
typedef struct s_pipe
{
	char	**cmd;
	char	*paths;
	t_fd	*fd_lst; // the list names of all the files and file descriptors
	int		in_fd; 
	int		out_fd;
	int		builtin;
//	struct s_pipe	*prev;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_exec
{
	int		fdp[2];		//array of 2 fd to use in pipe
	int		pid;		//what we receive by fork
	int		stat;		//the last process exit status

}	t_exec;

typedef struct s_mini
{
	t_lexer	*lex_lst;	//change to lex_lst
	t_env	*env_lst;	//change to env_lst
	t_pipe  *pipe_lst;	//What we have in every child, more structs inside.
	t_fd	*hd_lst;	//Here_doc list. 
	char	*input;		//what we receive by readline
	char	**paths;
	int		exit;		//int designed to exit the readline loop and finish the shell
	int		pipes; 		//How many pipes are there
	t_exec	exe;		//another struct with the variables i use in execution 
	char	**env;		//the env double array used by the execv. Each time "export" is called, rebuild it
	int		power_on;
}	t_mini;

//###########################################################################################

//			--	--	MAIN	--	--
/***** main.c  *********************************/
int		minishell(t_mini *sh);

/***** initialize.c - initializing and cleaning sh!!! *****/
int		sh_init(t_mini *sh, char **env);
void	sh_del(t_mini *sh);	// This is only used when exiting  the shell, we dont want to free the env between readlines
int		sh_clean(t_mini *sh);
t_mini	*sh_restore(t_mini **sh, t_lexer *lex, t_fd *hd); //This function restores the initial position of all the lists clean all of them after iteration
int	sh_loop_init(t_mini *sh); // parses the path and the env each time when a new loop starts

//###########################################################################################

//			--	--	LEXER	--	--

/***** lexer.c - Main and the main lexer cases *****/
int		lexer(t_mini *sh, char *input); //creates the lexer list with tokens
t_lexer *read_redirection(char *in, t_mini *sh, int *i); //defines < > << >> <<< |
t_lexer *read_in_quotes(char *in, int *i); // saves a string in quotes and a type of quotes
t_lexer *read_word(char *in, int *i, char q, int j); 
t_lexer *read_space(char *in, int *i);

/***** lexer_utils.c - dealing with lexer lists *****/
int		lex_clean(t_lexer **lst); // cleans the list and the input
t_lexer	*lex_new(char *content, int token); // creates a new node
void	lex_add(t_lexer **lst, t_lexer *new); // adds a node to the list
int		trim_quotes(t_mini *sh, t_lexer *lex); // to trim quotes after expantion 
char	*word_no_q(t_lexer *lex, int j); // to trim quotes after expantion

/***** check_syntax.c - *****/
int		pre_quotes(char *line);
void	print_lexer(t_mini *sh);
void	print_parser(t_mini *sh);

/***** utils.c - general utils *****/
char	*ft_substr_quotes(char *s, char q, int len, int i); //check if it trims slashes like bash
int		check_chr(char c);
char	**arr_clean(char **cmd, int flag); //frees a double array, if flag=0 - frees all the strings in it, if flag=1 only equals them to NULL (they are not allocated)
int		ft_longer(char *str, char *key); // receives 2 strings and returns the lenth of the longer one
char	*ft_smart_join(char *s1, char *s2, char *s3); // clean strjoin, that can jpoin 3 str

//###########################################################################################

//			--	--	HERE_DOC	--	--

/***** heredoc.c - after checking unclosed quotes *****/
int		ft_heredoc(t_mini *sh, char *in);
int		find_hd(char *in, int i);
char	*keyword_hd(t_fd *new, char *in, int *i);
int		save_hd(char *key, char *str);

/***** fd_utils.c - dealing with fd lists *****/
void	fd_add(t_fd **lst, t_fd *new);
void	fd_clean(t_fd **hd); // returns 2 if malloc fails, 1 if fd fails
void	fd_init(t_fd *new, t_mini *sh, int fd, int type);

//###########################################################################################

//			--	--	PARSER	--	--


/***** parser.c - the updated main with sh struct and  *****/
int	parser(t_mini *sh, t_lexer *lex, t_fd *hd, int check); // cleans all and returns 1 if malloc failed
int	parse_redir(t_pipe *new, t_lexer *lex, t_fd *hd, t_mini *sh); //we have 3 cases:
	//1. its one of the < > >>
	//2. its a heredoc
	//3. its a word so we treat it as a <
int	parse_cmd(t_pipe *new, t_lexer *lex, t_mini *sh); //I dont clean the lex here! 

/***** parser_utils.c - the updated main with sh struct and  *****/
void	pipe_init(t_pipe *pip);
void	pipe_add(t_mini *sh, t_pipe *new);
int		pipe_clean(t_pipe **lst);

//###########################################################################################

//			--	--	SIGNALS	--	--

void	signals(void);
void	sig_handler(int sig);

//###########################################################################################

//			--	--	ENV	--	--

// env.c
int		get_env(t_mini *sh, char **env);
char	*get_key(char *og_env);
char	*get_val(char *og_env);
int		env_converter(t_mini *sh);
void	print_env(t_env *head, char **env);

//	ENV_LIST
int		allocate_env(t_mini *sh, size_t n);
int		ft_envadd_back(t_env **lst, t_env *new);
t_env	*envnode_new(char *env);
t_env	*ft_envlast(t_env *lst);

// FREE
void	free_env_lst(t_mini *sh);
void	free_env_chr(t_mini *sh);
void	free_env(t_mini *sh);

//###########################################################################################


//			--	--	ERRORS	--	--

void	synt_error(t_mini *sh);

//###########################################################################################

#endif