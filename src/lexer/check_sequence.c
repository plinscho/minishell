/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:22:21 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/27 22:32:15 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		no_cmd(char *seq)
{
	int	i;

	i = 0;
	while(seq[i])
	{
		if (!(ft_isspace(seq[i])))
			return (0);
		i++;
	}
	return (1);
}

int check_syntax(t_mini *sh, t_lexer *lexer)
{
    t_lexer *current = lexer;
    int prev_token = -1;

	if (current->token == 8)
	{
		sh->exit = 258;
		return (err_char(current->token));
	}
    while (current != NULL)
    {
        if (current->token != 0) // Ignore space tokens
        {
            if ((current->token >= 4 && current->token <= 5) || current->token >= 7)// If the token is a pipe or redirection operator
            {
                if (prev_token >= 4 && prev_token <= 9) // If the previous token was also a pipe or redirection operator
                {
                    sh->exit = 258;
                    return (err_char(current->token)); // Return an error
                }
            }
            prev_token = current->token;
        }
        current = current->next;
    }
    if (prev_token >= 4 && prev_token <= 9) // If the last token was a pipe or redirection operator
    {
        sh->exit = 258;
        return (err_char(prev_token)); // Return an error
    }
    return (0); // No syntax errors found
}

int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}
