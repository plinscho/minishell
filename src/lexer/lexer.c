/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:25:46 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/21 20:43:43 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
This function trims all the sequential spaces and saves token 0 in the node.
*/
t_lexer *read_space(char *in, int *i)
{
	int	j;

	j = 0;
	while (in[j + 1] && in[j + 1] == ' ')
        j++;
	*i += j;
    return(lex_new(NULL, 0));
}

/*
This function parses words (see the list in README).
If it finds quotes inside of a word, it jons to the word everything that 
is inside of the quotes, doesn't trim any quotes.
Then it saves it to the node.
*/
t_lexer *read_word(char *in, int *i, char q, int j)
{
	char	*cont;

//	printf("[RW]You entered: input - %c\n", in[j]); //erase
	while (in[j] && in[j + 1] && in[j + 1] != ' ' && in[j + 1] != '\'' && \
	in[j + 1] != '\"' && check_chr(in[j + 1]))
		j++;
	if (in[j] && in[j + 1] && (in[j + 1] == '\'' || in[j + 1] == '\"'))
	{
		q = in[++j];
		j++;
		while (in[j] && in[j] != q)
			j++;
		while (in[j] && in[j + 1] && in[j + 1] != ' ')
			j++;
//		if (q == '\"')
//			cont = ft_substr_quotes(in, q, j, -1);
		(*i)++;
	}
//	if (q == ' ' || q == '\'')
//		cont = ft_substr(in, 0, j + 1);
	cont = ft_substr(in, 0, j + 1);
	if (!cont)
		return (NULL);
	*i += j;
//	printf("[RW] leaving: input - %c\n", in[j]); //erase
	return (lex_new(cont, 1));
}

/*
This function parses strings in single/double quotes (see the list in README)
and updates the position in the string to the pointer to the last quote.
*/
t_lexer *read_in_quotes(char *in, int *i)
{
	char	*cont;
	int		j;

	j = 0;
//	printf("entered read quotes: i == %i\n", *i);
	while (in[j] && in[j + 1] != in[0])
		j++;
	cont = ft_substr(in, 1, j);
	if (!cont)
		return (NULL);
	*i += j + 1;
//	printf("in read quotes: i == %i\n", *i);
	if (in[0] == '\'')
		return (lex_new(cont, 2));
	else
		return (lex_new(cont, 3));
	
}

/*
This function parses all the types of redirections (see the list in README).
*/
t_lexer *read_redirection(char *in, t_mini *sh, int *i)
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
    else if (in[j] == '>' && in[j + 1] == '>') // the case of >> append
    {    
        (*i)++;
        return (lex_new(NULL, 7));
    }
    else if (in[j] == '|')
	{
		sh->pipes++;
		return (lex_new(NULL, 8));
	}
	return (NULL);
}

/*
This function splits the string into tokens (see the list in README). 
It creates a node for each token and adds it to the lexer list.
1. return (0) - everything went well
2. return (1) - some malloc failed, the struct is freed.
*/
int lexer(t_mini *sh, char *input)
{
    t_lexer *new;
    int i;

    i = -1;
    new = NULL;
    while (input[++i])
    {
 //       printf("[LEX]You entered: input - %c\n", input[i]); //erase
		if (input[i] == ' ')
            new = read_space(&input[i], &i);
        else if (input[i] == '<' || input[i] == '>' || input[i] == '|')
            new = read_redirection(&input[i], sh, &i);
        else if (input[i] == '\'' || input[i] == '\"')
			new = read_in_quotes(&input[i], &i);
		else
			new = read_word(&input[i], &i, ' ', 0);
		if (!new)
			return (sh_clean(sh, 2));
		else
			lex_add(&(sh->lex_lst), new);
    }
	return (0);
}