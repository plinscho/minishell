/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:58:38 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/22 15:53:33 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
 #define LEXER_H

#include "minishell.h"

typedef struct s_exp	t_exp;

typedef struct s_lexer
{
    char    *cont;
    int     token;
    struct s_lexer  *prev;
    struct s_lexer  *next;
} t_lexer;

//###########################################################################################

//			--	--	LEXER	--	--

/***** lexer.c - Main and the main lexer cases *****/
int		lexer(t_mini *sh, char *input); //creates the lexer list with tokens
t_lexer *read_redirection(char *in, t_mini *sh, int *i); //defines < > << >> <<< |
t_lexer *read_in_quotes(char *in, int *i); // saves a string in quotes and a type of quotes
t_lexer *read_word(char *in, int *i, char q, int j); 
t_lexer *read_space(char *in, int *i);
/***************************************************/

/***** lexer_utils.c - dealing with lexer lists *****/
int		lex_clean(t_lexer **lst); // cleans the list and the input
t_lexer	*lex_new(char *content, int token); // creates a new node
void	lex_add(t_lexer **lst, t_lexer *new); // adds a node to the list
t_lexer	*lex_last(t_lexer *lst);
void	lex_insert(t_mini *sh, t_lexer *new, t_lexer **lex, t_lexer *temp);
//int		trim_quotes(t_mini *sh, t_lexer *lex); // to trim quotes after expantion 
//char	*word_no_q(char *in, char q); // to trim quotes after expantion
/***************************************************/

/***** quotes.c - dealing with quotes *****/
int		word_in_quotes(char *in, char *q, int j);
char	*trim_quotes(char *s, char q, int len, int i);
int		len_no_q(char *s, char q, int len, int i);
int		open_q(t_exp *exp, char c, int type);
int		exp_quotes(t_mini *sh, t_lexer **head, int *flag);

/***** check_syntax.c - checks the syntax *****/
int	    check_input(char *in); // checks if there is anything in the input
int		pre_quotes(char *line);
int		check_syntax(t_mini *sh, t_lexer *current, int prev_token);
char 	int_to_char(int num);
int		ft_isspace(int c);
/***************************************************/

/***** utils.c - general utils *****/
char	*ft_substr_quotes(char *s, char q, int len, int i); //check if it trims slashes like bash
int		check_chr(char c);
char	**arr_clean(char **cmd, int flag); //frees a double array, if flag=0 - frees all the strings in it, if flag=1 only equals them to NULL (they are not allocated)
int		ft_longer(char *str, char *key); // receives 2 strings and returns the lenth of the longer one
char	*ft_smart_join(char *s1, char *s2, char *s3); // clean strjoin, that can jpoin 3 str
/***************************************************/

//###########################################################################################



#endif