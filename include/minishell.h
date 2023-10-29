#ifndef MINISHELL_H
    #define MINISHELL_H

#include "libft/libft.h"
#include "../include/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

//FUNCTIONS

//		INPUT
void	char_an(const char *full_cmd);

//		SIGNALS
void	signal_mgr();

//		ENV
char	**cpy_env(char **og_env); //dont forget to free it!!!
char	*ft_getenv(char *var, char **env)
	;
#endif
