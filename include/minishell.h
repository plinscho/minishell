#ifndef MINISHELL_H
    #define MINISHELL_H

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
	struct s_envlst*	next;
} t_env;

typedef struct s_mini
{
	t_lexer	**lst_lexer;
	t_env	**lst_env;
//	Add other structs

	char 	**og_env;	

} t_mini;

/* THE LIST OF TOKENS
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


//		PARSER



//		SIGNALS
void	signal_mgr();

void	signal_init(void);
void	signal_int(int sig);
void	signal_quit(int sig);

//		ENV
char	**cpy_env(char **og_env); //dont forget to free it!!!
char	*ft_getenv(char *var, char **env);
char	*get_key(char *og_env);
char	*get_val(char *og_env);

	//	ENV_LIST
t_env	**env_head(char **og_env);
t_env	*envnode_new(char *env);
void	env_del(t_env **head);
#endif