/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:20:05 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/06 19:05:04 by nzhuzhle         ###   ########.fr       */
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
	int		k;	//lenth of final string
} t_exp;

/**********   expanser.c -  ***********/
int	expanser(t_mini *sh, t_lexer *lex);
char	*expand_str(t_mini *sh, char *cont, int i, int j);
int	exp_start(t_mini *sh, char *cont);
//int		expand_word(t_mini *sh, t_lexer **lex, int flag); // flag=0 - expand all, flag=1 - filename, expand only ""
char	*expand_hd(t_mini *sh, char *cont, int type);

/**********   expanser_utils.c -  ******/
int	check_exp(char *cont, int type);
int	new_len(t_mini *sh, char *cont);
char *get_var(char *cont);
char	*check_value(t_mini *sh, char *var);

/**********   exp_struct.c -  ******/
int	exp_init(t_mini *sh);
void	exp_nano_clean(t_exp *exp);
void	exp_clean(t_exp **exp);

#endif