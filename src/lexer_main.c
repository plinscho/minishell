/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:33:36 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/10/25 18:33:52 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer *lexer(char *input)
{
    t_lexer *list;
    t_lexer *new;
    int i;

    i = -1;
    list = NULL;
    new = NULL;
    while (input[++i])
    {
        if (input[i] == ' ')
        {
            new = lex_new(NULL, 0);
            while (input[i] == ' ')
                i++;
        }
    }
}

/*int main(int argc, char **argv)
{
    t_lexer *list;
    int i;

    i == 1;
    list = lexer(argc, argv);
    while (list)
    {
        printf("node 1 -- content: %s, type; %i\n", list->cont, list->token); //erase
        i++;
        list == list->next; 
    }

}*/
