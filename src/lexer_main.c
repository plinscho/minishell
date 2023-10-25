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

#include "../include/lexer.h"

t_lexer *lexer(int argc, char **argv)
{
    t_lexer *list;
    int i;

    i = -1;
    list = NULL;
    while (++i < argc)
    {
        
    }
}

int main(int argc, char **argv)
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

}
