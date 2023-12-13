/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:34:25 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/13 17:43:53 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	word_in_quotes(char *in, char *q, int j)
{
	*q = in[++j];
	j++;
	while (in[j] && in[j] != *q)
		j++;
//	if (in[j])
//		j++;
//	printf("[IN QUOTES] IN quotes: input - %s, j -- %i\n", in + j, j); //erase
	while (in[j] && in[j + 1] && in[j + 1] != ' ' && in[j + 1] != '\'' && in[j + 1] != '\"')
		j++;
//	printf("[AFTER QUOTES] IN quotes: input - %s, j -- %i\n", in + j, j); //erase
	return (j);
}


/*
s - string you want to trim
i = -1
q = ' '
len = ft_strlen(s)
*/

char		*trim_quotes(char *s, char q, int len, int i)
{
	char	*m;
	int		flag;
	int		j;

	if (!s || !len)
		return (s);
	len = len_no_q(s, q, len, -1);
	m = (char *) malloc(len + 1);
	if (m == 0)
		return (NULL);
	flag = 1;
	j = 0;
	while (++i < len && s[i + j])
	{
		if (check_chr(s[i + j]) == 2 && (flag > 0 || (flag < 0 && s[i + j] == q)))
		{
			q = s[i + j];
			flag *= -1;
			j++;
		}
		m[i] = s[i + j];
	}
	m[i] = '\0';
//	s = ft_memdel(s);
	return (m);
}

int	len_no_q(char *s, char q, int len, int i)
{
	int	flag;
	
	flag = 1;
	while (s[++i])
	{
		if (check_chr(s[i]) == 2 && flag > 0)
		{
			q = s[i];
			flag *= -1;
			len--;
		}
		else if (check_chr(s[i]) == 2 && flag < 0 && s[i] == q)
		{
			flag *= -1;
			len--;
		}
	}
	return (len);
}

int		open_q(t_exp *exp, char c, int type)
{
//	printf("[OPEN Q] c -- %c, type -- %i, q -- %c, flag -- %i\n", c, type, exp->q, exp->fl); //erase
	if (type == 3)
		return (0);
	if (c == '$' && exp->fl && exp->q == '\'')
		return (1);
	if (!exp->fl && check_chr(c) == 2)
	{
		exp->fl = 1;
		exp->q = c;
	}
	else if (exp->fl && c == exp->q)
		exp->fl = 0;
	return (0);
}