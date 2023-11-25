/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 22:10:06 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/25 12:56:05 by plinscho         ###   ########.fr       */
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
# include <string.h>

//	0. STRUCTS:
typedef struct s_lexer	t_lexer;
typedef struct s_envlst	t_env;
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
void	sh_del(t_mini *sh);	// This is only used when exiting  the shell, we dont want to free the env between readlines
int		sh_clean(t_mini *sh, int err);
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
char 	int_to_char(int num); //converts int into char
int		ft_isspace(int c); // Detects if "c" is a space char.

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

//	Check_sequence.c - Checks the syntax sequence based on the tokens
int		w_syntax(t_mini *sh);
//	void	check_sequence(t_mini *sh, char *seq);
int		check_syntax(t_lexer *head);

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
void	fd_init(t_fd *new, t_mini *sh, int fd);


//###########################################################################################

//			--	--	SIGNALS	--	--

void	signals(void);
void	sig_handler(int sig);

//###########################################################################################


//			--	--	ERRORS	--	--

int		quotes_error(t_mini *sh);
void	syntax_error(t_mini *sh, char *seq);

//###########################################################################################

#endif