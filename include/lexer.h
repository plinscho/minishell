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

t_lexer *lexer(int argc, char **argv); //creates the lexer list with tokens



#endif
