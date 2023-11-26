/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:58:38 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/25 13:28:18 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
 #define LEXER_H

//#include "minishell.h"

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

/***** lexer_utils.c - dealing with lexer lists *****/
int		lex_clean(t_lexer **lst); // cleans the list and the input
t_lexer	*lex_new(char *content, int token); // creates a new node
void	lex_add(t_lexer **lst, t_lexer *new); // adds a node to the list
int		trim_quotes(t_mini *sh, t_lexer *lex); // to trim quotes after expantion 
char	*word_no_q(t_lexer *lex, int j); // to trim quotes after expantion
char 	int_to_char(int num); //converts int into char
int		ft_isspace(int c); // Detects if "c" is a space char.

/***** check_syntax.c - *****/
int		pre_quotes(char *line);
void	print_lexer(t_mini *sh);
void	print_parser(t_mini *sh);

/***** utils.c - general utils *****/
char	*ft_substr_quotes(char *s, char q, int len, int i); //check if it trims slashes like bash
int		check_chr(char c);
char	**arr_clean(char **cmd, int flag); //frees a double array, if flag=0 - frees all the strings in it, if flag=1 only equals them to NULL (they are not allocated)
int		ft_longer(char *str, char *key); // receives 2 strings and returns the lenth of the longer one
char	*ft_smart_join(char *s1, char *s2, char *s3); // clean strjoin, that can jpoin 3 str

//	Check_sequence.c - Checks the syntax sequence based on the tokens
int		w_syntax(t_mini *sh);
//	void	check_sequence(t_mini *sh, char *seq);
int		check_syntax(t_lexer *head);

//###########################################################################################



#endif