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

#include "lexer.h"

t_lexer *read_word(char *in, int *i)
{
	char	*cont;
	int		j;

	j = 0;
	while (in[j] && in[j + 1] != ' ')
		j++;
	cont = ft_substr_slash(in, 0, j, -1);
	if (!cont)
		return (NULL);
	*i += j;
	return (lex_new(cont, 1));
}

t_lexer *read_in_quotes(char *in, int *i)
{
	char	*cont;
	int		j;

	j = 0;
	while (in[j] && in[j + 1] != in[0])
		j++;
	cont = ft_substr_slash(in, 0, j, -1);
	if (!cont)
		return (NULL);
	*i += j;
	if (in[0] == '\'')
		return (lex_new(cont, 2));
	else
		return (lex_new(cont, 2));
	
}

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
        (*i)++;
        return (lex_new(NULL, 6));
    }
    else if (in[j] == '<' && in[j + 1] == '<') // the case of >> append
    {    
        (*i)++;
        return (lex_new(NULL, 7));
    }
    else if (in[j] == '|')
        return (lex_new(NULL, 8));
    return (NULL);
}

int lexer(char *input, t_lexer **head)
{
    t_lexer *new;
    int i;

    i = -1;
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
        else if (input[i] == '\'' || input[i] == '\"')
			new = read_in_quotes(&input[i], &i);
		else
			new = read_word(&input[i], &i);
		if (!new)
			return (lex_clean(head, &input));
		else
			lex_add(head, new);
    }
	return (0);
}

int main(void)
{
    char    *input = NULL;
	t_lexer *lex_list = NULL;
    int i;

	while (42)
	{
		input = readline("minishell> ");
        if (!input) // in case we recieved an empty line
            break;
		printf("[MAIN]You entered: %s\n\n", input);
		if (lexer(input, &lex_list)) // it means that a malloc failed, my lex_clean cleaned input and list
			return (1);
		i = 1;
    	while (lex_list)
    	{
			printf("node %i -- content: %s, type; %i\n", i, lex_list->cont, lex_list->token); //erase
       	 	i++;
        	lex_list = lex_list->next; 
    	}
	}
	lex_clean(&lex_list, &input);
	return (0);
}
