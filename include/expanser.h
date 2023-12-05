/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:20:05 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/05 17:35:07 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSER_H
# define EXPANSER_H

# include "minishell.h"

/**********   expanser.c -  ***********/
int	expanser(t_mini *sh, t_lexer *lex);
char	*expand_str(t_mini *sh, char *cont, int i);
//int		expand_word(t_mini *sh, t_lexer **lex, int flag); // flag=0 - expand all, flag=1 - filename, expand only ""
char	*expand_hd(t_mini *sh, char *cont, int type);

/**********   expanser_utils.c -  ******/
int	check_exp(char *cont, int type);
int	new_len(t_mini *sh, char *cont);
char *get_var(char *cont);


#endif