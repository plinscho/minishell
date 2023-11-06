#ifndef MINISHELL_H
    #define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "../src/lexer/lexer.h"
#include "../src/env/env.h"
#include "../src/parser/parser.h"

	//STRUCTS:

typedef struct s_mini
{
	t_lexer	*lst_lex;  //change to lex_lst
	t_env	*lst_env;  //change to env_lst
	t_pipe  *pipe_lst;  //What we have in every child, more structs inside.
	t_hd	*hd_lst;	 //Here_doc list. 


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

//FUNCTIONS

/*
		ENV
void	env_del(t_env *head);
t_env	*envnode_new(char *env);
void	ft_envadd_back(t_env **lst, t_env *new);
t_env	*ft_envlast(t_env *lst);
int		get_env(t_mini *sh, char **env);
char	*get_key(char *og_env);
char	*get_val(char *og_env);
void	print_env(t_env *head);


**** lexer.c -
int		lexer(char *input, t_lexer **head); creates the lexer list with tokens
t_lexer *read_redirection(char *in, int *i); defines < > << >> <<< |
t_lexer *read_in_quotes(char *in, int *i);  saves a string in quotes and a type of quotes
t_lexer *read_word(char *in, int *i); 
t_lexer *read_space(char *in, int *i);

***** lexer_utils.c -   *****
int		lex_clean(t_lexer **lst); cleans the list and the input
t_lexer	*lex_new(char *content, int token);  creates a new node
void	lex_add(t_lexer **lst, t_lexer *new);  adds a node to the list
char	*ft_substr_quotes(char *s, int start, int len, int i); check if it trims slashes like bash
void	print_lexer(t_lexer *lex_list);

		PARSER

		SIGNALS
void	signal_mgr();

void	signal_init(void);
void	signal_int(int sig);
void	signal_quit(int sig);
*/
#endif