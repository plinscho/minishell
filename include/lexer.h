/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:58:38 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/15 20:59:24 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
 #define LEXER_H

#include "minishell.h"

typedef struct s_lexer
{
    char    *cont;
    int     token;
    struct s_lexer  *prev;
    struct s_lexer  *next;
} t_lexer;

//###########################################################################################

//			--	--	LEXER	--	--

// lexer_main.c - Main and the main lexer cases //
int 	lexer(char *input, t_mini *sh); //creates the lexer list with tokens
t_lexer *read_redirection(char *in, t_mini *sh, int *i); //defines < > << >> <<< |
t_lexer *read_in_quotes(char *in, int *i); // saves a string in quotes and a type of quotes
t_lexer *read_word(char *in, int *i); 
t_lexer *read_space(char *in, int *i);

// lexer_utils.c - dealing with lexer lists //
int		pre_quotes(char *line);
int		lex_clean(t_lexer **lst); // cleans the list and the input
t_lexer	*lex_new(char *content, int token); // creates a new node
void	lex_add(t_lexer **lst, t_lexer *new); // adds a node to the list
char	*ft_substr_quotes(char *s, char q, int len, int i); //check if it trims slashes like bash
int		check_chr(char c);
void	print_lexer(t_mini *sh);

// heredoc.c
int		find_hd(char *in, int i);
int		ft_here_doc(t_mini *sh, char *in, t_fd **hd);
char	*keyword_hd(char *in, int *i);
int		save_hd(char *key, char *str);

/* Error codes:
2 - malloc fails
1 - fd fails
*/

// heredoc_utils.c
void	hd_add(t_fd **lst, t_fd *new);
void	hd_clean(t_fd **hd);
int		ft_longer(char *str, char *key);

//###########################################################################################



#endif