/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:20:05 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/08 21:56:39 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSER_H
# define EXPANSER_H

# include "minishell.h"

typedef struct s_exp
{
	char	*cont;	//the initial content
	char	*new;	//the final expanded string
	char	*var;	//variable name
	char	*val;	//the value of the variable
	int		alloc;	//flag, if 0 - val is not allocated, 1 - vaal is allocated
	int		k;		//lenth of final string
	int		j;		//counter variable
} t_exp;

/**********   expanser.c -  ***********/
int	expanser(t_mini *sh, t_lexer *lex);
char	*expand_str(t_mini *sh, char *cont, int type, int i);
int		expand_word(t_mini *sh, t_lexer **lex);
t_lexer *read_word_exp(char *in, int *i, char q, int j); 
char	*expand_hd(t_mini *sh, char *cont, int type);
/***************************************************/

/**********   expanser_utils.c -  ******/
int	check_exp(char *cont, int type, int q); // q is a flag used inside to count " quotes
int	new_len(t_mini *sh, char *cont, int type);
char *get_var(char *cont);
char	*check_value(t_mini *sh, char *var);
int	exp_start(t_mini *sh, char *cont, int type);
/***************************************************/


/**********   exp_struct.c -  ******/
int	exp_init(t_mini *sh);
void	exp_nano_clean(t_exp *exp);
void	exp_clean(t_exp **exp);

#endif