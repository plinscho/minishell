#ifndef MINISHELL_H
    #define MINISHELL_H

<<<<<<< HEAD
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "../src/lexer/lexer.h"
#include "../src/parser/parser.h"
=======
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
#include "libft.h"
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd

//	STRUCTS:

typedef struct s_lexer
{
    char    *cont;
    int     token;
    struct s_lexer  *prev;
    struct s_lexer  *next;
} t_lexer;

typedef struct s_envlst
{
	char				*env_full;
	char				*env_val;
	char				*env_key;
<<<<<<< HEAD
	struct s_envlst*	next;
} t_env;

typedef struct s_mini
{
	t_lexer	**lst_lexer;
	t_env	**lst_env;
=======
	struct s_envlst		*next;
}t_env;

typedef struct s_mini
{
	t_lexer	**lst_lex;
	t_env	*lst_env;
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd
//	Add other structs

	int		exit;	

} t_mini;

<<<<<<< HEAD
/* THE LIST OF TOKENS
=======
/*	TOKENS	*/

/* The list of tokens:
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd
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

<<<<<<< HEAD
/*	FUNCTIONS	*/

//	LEXER

/***** lexer.c -   *****/
int		lexer(char *input, t_lexer **head); //creates the lexer list with tokens
t_lexer *read_redirection(char *in, int *i); //defines < > << >> <<< |
t_lexer *read_in_quotes(char *in, int *i); // saves a string in quotes and a type of quotes
t_lexer *read_word(char *in, int *i); 
t_lexer *read_space(char *in, int *i);

/***** lexer_utils.c -   *****/
int		lex_clean(t_lexer **lst); // cleans the list and the input
t_lexer	*lex_new(char *content, int token); // creates a new node
void	lex_add(t_lexer **lst, t_lexer *new); // adds a node to the list
char	*ft_substr_quotes(char *s, char q, int len, int i); //check if it trims slashes like bash

=======
//FUNCTIONS

//		ENV

void	env_del(t_env *head);
t_env	*envnode_new(char *env);
void	ft_envadd_back(t_env **lst, t_env *new);
t_env	*ft_envlast(t_env *lst);
int		get_env(t_mini *sh, char **env);
char	*get_key(char *og_env);
char	*get_val(char *og_env);
void	print_env(t_env *head);

//		LEXER
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd

/***** lexer.c -   *****/
int		lexer(char *input, t_lexer **head); //creates the lexer list with tokens
t_lexer *read_redirection(char *in, int *i); //defines < > << >> <<< |
t_lexer *read_in_quotes(char *in, int *i); // saves a string in quotes and a type of quotes
t_lexer *read_word(char *in, int *i); 
t_lexer *read_space(char *in, int *i);

/***** lexer_utils.c -   *****/
int		lex_clean(t_lexer **lst); // cleans the list and the input
t_lexer	*lex_new(char *content, int token); // creates a new node
void	lex_add(t_lexer **lst, t_lexer *new); // adds a node to the list
char	*ft_substr_quotes(char *s, int start, int len, int i); //check if it trims slashes like bash
void	print_lexer(t_lexer *lex_list);

//		PARSER

<<<<<<< HEAD


=======
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd
//		SIGNALS
void	signal_mgr();

void	signal_init(void);
void	signal_int(int sig);
void	signal_quit(int sig);

<<<<<<< HEAD
//		ENV
char	**cpy_env(char **og_env); //dont forget to free it!!!
char	*ft_getenv(char *var, char **env);
char	*get_key(char *og_env);
char	*get_val(char *og_env);
=======
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd

	//	ENV_LIST
t_env	**env_head(char **og_env);
t_env	*envnode_new(char *env);
void	env_del(t_env **head);
#endif