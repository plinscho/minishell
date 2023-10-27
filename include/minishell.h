#ifndef MINISHELL_H
    #define MINISHELL_H

#include "libft/libft.h"
#include "../src/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

//FUNCTIONS

//		INPUT
void	char_an(const char *full_cmd);

//		SIGNALS
void	signal_mgr();


#endif