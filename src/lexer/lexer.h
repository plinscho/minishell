/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:34:27 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/10/29 19:49:45 by nzhuzhle         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "../../include/libft/libft.h"
# include "../parser/parser.h"
//# include "../../include/minishell.h"

typedef struct s_lexer
{
    char    *cont;
    int     token;
    struct s_lexer  *prev;
    struct s_lexer  *next;
} t_lexer;

/* heredoc list  -  do not forget to free if any syntax error found! */
typedef struct s_hd
{
	int		fd; // file descriptor
	char	*str; // string you get in heredoc to compare it with the key word
	struct s_hd	*next;
}	t_hd;

/***** lexer.c -   *****/
int		lexer(char *input, t_lexer **head); //creates the lexer list with tokens
t_lexer *read_redirection(char *in, int *i); //defines < > << >> <<< |
t_lexer *read_in_quotes(char *in, int *i); // saves a string in quotes and a type of quotes
t_lexer *read_word(char *in, int *i); 
t_lexer *read_space(char *in, int *i);

/***** lexer_utils.c -   *****/
int	lex_clean(t_lexer **lst, char **in); // cleans the list and the input
t_lexer	*lex_new(char *content, int token); // creates a new node
void	lex_add(t_lexer **lst, t_lexer *new); // adds a node to the list
char	*ft_substr_quotes(char *s, char q, int len, int i); //check if it trims slashes like bash
int		check_chr(char c);

/***** here_doc.c - after checking unclosed quotes  *****/
int		ft_here_doc(char *in, t_hd **hd);
int		find_hd(char *in, int i);
char	*keyword_hd(char *in, int *i);
int		save_hd(char *key, char *str);
int		free_hd(t_hd **hd, int err); // returns -2 if malloc fails, -1 if fd fails

/***** here_doc_utils.c - dealing with here_doc list  *****/
void	hd_add(t_hd **lst, t_hd *new);
int		ft_longer(char *str, char *key);


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

#endif
