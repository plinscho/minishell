/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:01:59 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/29 18:13:54 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		pre_quotes(char *line)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i])
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

int	check_input(char *in)
{
	while (*in && *in == ' ')
		in++;
	if (!*in)
		return (1);
	return (0);
}



/*

	FUNCTIONS ARE WAY TO COMPLICATED, using the lex list instead.

void	get_sequence(t_lexer *tmp, char *sequence)
{
	int		i;

	i = 0;
	while (tmp != NULL)
	{
		sequence[i] = int_to_char(tmp->token);
		tmp = tmp->next;
		i++;
	}
	sequence[i] = '\0';
}

char	*alloc_sequence(t_lexer *head)
{
	t_lexer	*tmp;
	char	*seq;	// stands for sequence of chars of tokens.
	int		nodes;

	tmp = head;
	nodes = 0;
	while(tmp)
	{
		nodes++;
		tmp = tmp->next;
	}
	seq = (char *)malloc(sizeof(char) * nodes + 1);
	if (!seq)
		return (NULL);
	return (seq);	
}

	This function checks for syntax errors.
	The ideal would be to use it after the lexer, I can use the tokens to create a logic.

int		w_syntax(t_mini *sh)
{
	t_lexer	*tmp;
	char 	*sequence;

	tmp = sh->lex_lst;
	sequence = NULL;
	print_lexer(sh);	// ERASE
	if (!tmp)
		return (errno); // Just for now.
	
	sequence = alloc_sequence(tmp);
	if (sequence == NULL)
		return (1);
	get_sequence(tmp, sequence);
	printf("sequence: %s\n", sequence);
	check_sequence(sh, sequence);
	free(sequence);
	return (0);
}	

*/
