/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:01:59 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/22 15:50:40 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pre_quotes(char *line)
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

int	check_syntax(t_mini *sh, t_lexer *current, int prev_token)
{
	if (current->token == 8)
		return (err_char(sh, current->token));
	while (current != NULL)
	{
		if (current->token != 0)
		{
			if (current->token >= 4 && current->token <= 8)
			{
				if ((prev_token >= 4 && prev_token < 8)
					|| (prev_token == 8 && current->token == 8))
					return (err_char(sh, current->token));
			}
			prev_token = current->token;
		}
		current = current->next;
	}
	if (prev_token >= 4 && prev_token <= 9)
		return (err_char(sh, prev_token));
	return (0);
}

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

char	int_to_char(int num)
{
	return ((char)(num + '0'));
}
