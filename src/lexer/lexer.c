/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:25:46 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/15 19:37:45 by plinscho         ###   ########.fr       */
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

//	printf("[RW]You entered: input - %s\n", in + j); //erase
/*	while (in[j] && in[j + 1] && check_chr(in[0]) == 2 && in[j + 1] != in[0])
		j++;
	printf("[RW] After first while: input - %s\n", in + j); //erase
	if (in[j] && in[j + 1] && check_chr(in[0]) == 2)
		j = j + 2;
	printf("[RW] After if: input - %s\n", in + j); //erase*/
	while (in[j] && in[j + 1] && check_chr(in[0]) != 2 && check_chr(in[j + 1]) != 2 && check_chr(in[j + 1]))
		j++;
//	printf("[RW] After 2d while: input - %s\n", in + j); //erase
	if (check_chr(in[0]) == 2)
		j = word_in_quotes(in, &q, -1);
	while (in[j] && in[j + 1] && check_chr(in[j + 1]) == 2)
		j = word_in_quotes(in, &q, j);
//	printf("[RW] After iteration: input - %c, j - %i\n", in[j], j); //erase
//	if (q != ' ')
//		(*i)++;
	cont = ft_substr(in, 0, j + 1);
//	printf("creando cont!!!!!: %s\n", cont);
	if (!cont)
		return (NULL);
	*i += j;
//	printf("[RW] leaving: token - %s, in[i] -- %c, i -- %i\n", cont, in[j], *i); //erase
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
//	printf("[LEX READ IN QUOTES]entered read quotes: in == %s\n", in + j);
	while (in[j] && in[j + 1] && in[j + 1] != in[0])
		j++;
//	printf("[LEX READ IN QUOTES] after while: in == %s\n", in + j);
//	if (j == 0 && in[j + 1] && in[j + 1] == in[0] && !in[j + 2])
//		j++;
	if (in[j + 2] && check_chr(in[j + 2]))
		return (read_word(in, i, ' ', 0));
///	printf("[LEX READ IN QUOTES] after all: j == %i\n", j);
	cont = ft_substr(in, 1, j);
	if (!cont)
		return (NULL);
	*i += j + 1;
//	printf("[LEX READ IN QUOTES]: i == %i\n", *i);
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
//		printf("[LEXER] found a pipe: pipes == %i\n", sh->pipes);
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

    i = 0;
    new = NULL;
//	printf("[LEX] input: %s\n", input);
    while (input[i])
    {
//      printf("[LEX]You entered: input - %c\n", input[0]); //erase
		if (input[i + 1] && check_chr(input[i]) == 2 && input[i + 1] == input[i] && input[i + 2])
		{
			i++;
			continue ;
		}
		if (input[i] == ' ')
            new = read_space(&input[i], &i);
        else if (input[i] == '<' || input[i] == '>' || input[i] == '|')
            new = read_redirection(&input[i], sh, &i);
        else if (input[i] == '\'' || input[i] == '\"')
			new = read_in_quotes(&input[i], &i);
		else
			new = read_word(&input[i], &i, ' ', 0);
		if (!new)
			return (err_break(sh, "malloc", NULL, 12));
		else
			lex_add(&(sh->lex_lst), new);
		i++;
	//	printf("[LEX] After loop: input - %c\n", input[i]);
    }
	return (0);
}