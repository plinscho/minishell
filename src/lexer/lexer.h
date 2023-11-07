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
# include "../../include/minishell.h"

typedef struct s_lexer
{
    char    *cont;
    int     token;
    struct s_lexer  *prev;
    struct s_lexer  *next;
} t_lexer;

/* a list with all the files names with redirections */
typedef struct s_fd
{
	int		fd; // file descriptor
	int		type; // 4 - infile, 5 - outfile, 6 - here_doc, 7 - outfile append
	char	*str; // keyword in heredoc, or the filename
	struct s_fd	*next;
}	t_fd;

/***** lexer_main.c - Main and the main lexer cases *****/
int		lexer(char *input, t_mini **sh, t_lexer **head); //creates the lexer list with tokens
t_lexer *read_redirection(char *in, t_mini *sh, int *i); //defines < > << >> <<< |
t_lexer *read_in_quotes(char *in, int *i); // saves a string in quotes and a type of quotes
t_lexer *read_word(char *in, int *i); 
t_lexer *read_space(char *in, int *i);

/***** lexer_utils.c - dealing with lexer lists *****/
int	lex_clean(t_lexer **lst); // cleans the list and the input
t_lexer	*lex_new(char *content, int token); // creates a new node
void	lex_add(t_lexer **lst, t_lexer *new); // adds a node to the list
char	*ft_substr_quotes(char *s, char q, int len, int i); //check if it trims slashes like bash
int		check_chr(char c);

/***** here_doc.c - after checking unclosed quotes *****/
int		ft_here_doc(t_mini **sh, char *in, t_fd **hd);
int		find_hd(char *in, int i);
char	*keyword_hd(char *in, int *i);
int		save_hd(char *key, char *str);

/***** here_doc_utils.c - dealing with here_doc list *****/
void	hd_add(t_fd **lst, t_fd *new);
void		hd_clean(t_fd **hd); // returns 2 if malloc fails, 1 if fd fails
int		ft_longer(char *str, char *key);

/* Error codes:
2 - malloc fails
1 - fd fails
*/

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
