/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:32:09 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/06 19:38:47 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//	Checks if there are quotes open. One of the firsts to check.
int		check_qt(char *str)
{
	unsigned int	i;
	char			open;

	i = 0;
	open = 0;
	while (str[i])
	{
		if (i > 0 && str[i - 1] == '\\')
			;
		else if (open == 0 && str[i] == '\"')
			open = 1;
		else if (open == 0 && str[i] == '\'')
			open = 2;
		else if (open == 1 && str[i] == '\"')
			open = 0;
		else if (open == 2 && str[i] == '\'')
			open = 0;
		i++;
	}
	return(open);
}

void		check_append(char *input, int *i, int *error)
{
	int	j;

	j = 2; // starting after the second '>'
	while (input[j] && input[j] == ' ')	// Iterate spaces
		j++;
	while (input[j])
	{
		if (!(check_char(input[j])))
			*error = 1;
		j++;
	}
	return (*error);
}

void	check_pipes(char *input, int *i, char *error)
{
	return ;
}		

int		check_syntax(char *input)
{
	unsigned int	i;
	int				error;

	i = 0;
	error = 0;
	while ((input[i]) && (error == 0))
	{
		if (input[i] == '>' && input[i + 1] == '>')
			check_append(&input[i], &i, &error);
		else if (input[i] == '|')
			check_pipes(&input[i], &i, &error);
	}
	if (error)
		return (1);
	return (0)
}