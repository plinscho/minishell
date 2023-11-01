#ifndef MINISHELL_H
    #define MINISHELL_H

#include "libft/libft.h"
#include "../src/lexer/lexer.h"
#include "../src/parser/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

//	STRUCTS:

typedef struct s_envlst
{
	char				*env_full;
	char				*env_val;
	char				*env_key;
	struct s_envlist	*next;
}t_env;

typedef struct s_mini
{
	t_lexer	**lst_lex;
	t_env	**lst_env;
//	Add other structs

	char 	**og_env;	

}t_mini;

//FUNCTIONS

//		LEXER

//		PARSER

//	ENV_LIST
t_env	**env_head(char **og_env);
t_env	*envnode_new(char *env);
void	env_del(t_env **head);


//		SIGNALS
void	signal_mgr();

void	signal_init(void);
void	signal_int(int sig);
void	signal_quit(int sig);

//		ENV
char	**cpy_env(char **og_env); //dont forget to free it!!!
char	*ft_getenv(char *var, char **env);

#endif