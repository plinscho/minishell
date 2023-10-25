/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:34:27 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/10/25 18:35:29 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include "./libft/libft.h"

typedef struct s_lexer
{
    char    *cont;
    int     token;
    struct s_lexer  **head;
    struct s_lexer  *prev;
    struct s_lexer  *next;
} t_lexer;

/***** lexer.c -   *****/
t_lexer *lexer(char *input); //creates the lexer list with tokens

/***** lexer_utils.c -   *****/
t_lexer	*lex_new(char *content, int token);

/* The list of tokens:
0 = space; - content is null
1 = word;
2 = ' single quotes string;
3 = " double quotes string; 
4 = < infile redirection; - content is null
5 = > outfile redirection; - content is null
6 = << heredoc sign; - content is a KEYWORD
7 = >> outfile append redirection; - content is null
8 = | pipe; - content is null
*/

#endif
