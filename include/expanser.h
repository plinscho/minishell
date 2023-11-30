/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:20:05 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/30 19:03:32 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSER_H
# define EXPANSER_H

# include "minishell.h"
    
int	expanser(t_mini *sh, t_lexer *lex);
char	*expand_str(char *cont);



#endif