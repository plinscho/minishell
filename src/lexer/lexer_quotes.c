/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:16:59 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/02 19:36:24 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>


/*
	This function checks if the input has unclosed quotes
	Its not finished because I still need to check if a quote is
	inside other quotes, because that is allowed.
*/
int		check_quotes(char *input)
{
	unsigned int	i;
	int				dq_closed;
	int				sq_closed;

	i = -1;
	dq_closed = 1;		// 1 means closed
	sq_closed = 1;		// 0 means open
	while (input[++i] != '\0')
	{
		if (input[i] == '\"')
		{
			if (dq_closed == 1) dq_closed = 0;
			else
				dq_closed = 1;
		}
		else if (input[i] == '\'')
		{
			if (sq_closed == 1) sq_closed = 0;
			else
				sq_closed = 1;
		}
	}
	if (sq_closed && dq_closed)
		return (0);
	return (1);
}

int main(void)
{
	char *input = "Th\'is \"is a \' quote\'";
	printf("input: %s\nquotes: %d\n", input, check_quotes(input));
	return (0);
}