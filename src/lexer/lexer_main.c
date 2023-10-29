/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:33:36 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/10/29 17:41:44 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer *read_redirection(char *in, int *i)
{
    int j;

    j = 0;
    if (in[j] == '<' && in[j + 1] != '<') // the case of < input file
        return (lex_new(NULL, 4));
    else if (in[j] == '>' && in[j + 1] != '>') // the case of > output file
        return (lex_new(NULL, 5));
    else if (in[j] == '<' && in[j + 1] == '<') // the case of << heredoc
    {
        *i++;
        return (lex_new(NULL, 6));
    }
    else if (in[j] == '<' && in[j + 1] == '<') // the case of >> append
    {    
        *i++;
        return (lex_new(NULL, 7));
    }
    else if (in[j] == '|')
        return (lex_new(NULL, 8));
    return (NULL);
}


/*	P: what happens with the "" and ''? There is no case where the program saves the
	token into the list. Or if the input has '\' we have to ingnore the next character.
	We need to consider these cases before tokenizing.
*/
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
            while (input[i + 1] && input[i + 1] == ' ')
                i++;
            new = lex_new(NULL, 0);
        }
        else if (input[i] == '<' || input[i] == '>' || input[i] == '|')
            new = read_redirection(&input[i], &i);
        
    }
}
/*
int main(int argc, char **argv)
{
    t_lexer *list;
    int i;

    i == 1;
    list = lexer(argv[1]);
    while (list)
    {
        printf("node 1 -- content: %s, type; %i\n", list->cont, list->token); //erase
        i++;
        list == list->next; 
    }

}
*/