/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:25:46 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/19 17:33:35 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
This function trims all the sequential spaces and saves token 0 in the node.
*/
t_lexer	*read_space(char *in, int *i)
{
	int		j;
	char	*cont;

	j = 0;
	while (in[j + 1] && in[j + 1] == ' ')
		j++;
	cont = malloc(2);
	if (!cont)
		return (NULL);
	cont[0] = ' ';
	cont[1] = '\0';
	*i += j;
	return (lex_new(cont, 0));
}

/*
This function parses words (see the list in README).
If it finds quotes inside of a word, it jons to the word everything that 
is inside of the quotes, doesn't trim any quotes.
Then it saves it to the node.
*/
t_lexer	*read_word(char *in, int *i, char q, int j)
{
	char	*cont;

	while (in[j] && in[j + 1] && check_chr(in[0]) != 2
		&& check_chr(in[j + 1]) != 2 && check_chr(in[j + 1]))
		j++;
	if (check_chr(in[0]) == 2)
		j = word_in_quotes(in, &q, -1);
	while (in[j] && in[j + 1] && check_chr(in[j + 1]) == 2)
		j = word_in_quotes(in, &q, j);
	cont = ft_substr(in, 0, j + 1);
	if (!cont)
		return (NULL);
	*i += j;
	return (lex_new(cont, 1));
}

/*
This function parses strings in single/double quotes (see the list in README)
and updates the position in the string to the pointer to the last quote.
*/
t_lexer	*read_in_quotes(char *in, int *i)
{
	char	*cont;
	int		j;

	j = 0;
	while (in[j] && in[j + 1] && in[j + 1] != in[0])
		j++;
	if (in[j + 2] && check_chr(in[j + 2]))
		return (read_word(in, i, ' ', 0));
	cont = ft_substr(in, 1, j);
	if (!cont)
		return (NULL);
	*i += j + 1;
	if (in[0] == '\'')
		return (lex_new(cont, 2));
	else
		return (lex_new(cont, 3));
}

/*
This function parses all the types of redirections
(see the list in README).
*/
t_lexer	*read_redirection(char *in, t_mini *sh, int *i)
{
	int	j;

	j = 0;
	if (in[j] == '<' && in[j + 1] != '<')
		return (lex_new(NULL, 4));
	else if (in[j] == '>' && in[j + 1] != '>')
		return (lex_new(NULL, 5));
	else if (in[j] == '<' && in[j + 1] == '<')
	{
		(*i)++;
		return (lex_new(NULL, 6));
	}
	else if (in[j] == '>' && in[j + 1] == '>')
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
int	lexer(t_mini *sh, char *input)
{
	t_lexer	*new;
	int		i;

	i = -1;
	new = NULL;
	while (input[++i])
	{
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
	}
	return (0);
}
