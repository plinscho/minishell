#ifndef MINISHELL_H
    #define MINISHELL_H

#include "libft/libft.h"
#include "lexer.h"
#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

//	We can create a struct where we store the head of all
//	the other lists, so we only pass one argument (t_mini)
//	and at the same time pass all the lists
//	
typedef struct s_mini
{
	t_lexer	*head;
//	add other structs

	char 	**env_cpy;	

}t_mini;

//FUNCTIONS

//		INPUT
void	char_an(const char *full_cmd);

//		SIGNALS
void	signal_mgr();
void	signal_init(void);
void	signal_int(int sig);
void	signal_quit(int sig);

#endif