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

int	no_cmd(char *seq)
{
	int	i;

	i = 0;
	while (seq[i])
	{
		if (!(ft_isspace(seq[i])))
			return (0);
		i++;
	}
	return (1);
}
/*
int	check_syntax(t_mini *sh, t_lexer *lexer)
{
	t_lexer	*node;
	int		prev_token;

	prev_token = -1;
	node = lexer;
	if (node->token == 8)
		return (err_char(node->token));
	while (node != NULL)
	{
		if (node->token != 0)
		{
			if ((node->token >= 4 && node->token <= 5) || node->token >= 7)
			{
				if (prev_token >= 4 && prev_token <= 9)
					return (err_char(node->token));
			}
			prev_token = node->token;
		}
		node = node->next;
	}
	if (prev_token >= 4 && prev_token <= 9)
		return (err_char(prev_token));
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
*/
