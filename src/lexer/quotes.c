/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:34:25 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/22 17:20:39 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	word_in_quotes(char *in, char *q, int j)
{
	*q = in[++j];
	j++;
	while (in[j] && in[j] != *q)
		j++;
	while (in[j] && in[j + 1] && in[j + 1] != ' ' && check_chr(in[j + 1]) != 2)
		j++;
	return (j);
}

/*
s - string you want to trim
i = -1
q = ' '
len = ft_strlen(s)
*/
char	*trim_quotes(char *s, char q, int len, int i)
{
	char	*m;
	int		flag;
	int		j;

	if (!s || !len || (!ft_strchr(s, '\'') && !ft_strchr(s, '\"')))
		return (s);
	len = len_no_q(s, q, len, -1);
	m = (char *) malloc(len + 1);
	if (m == 0)
		return (NULL);
	flag = 1;
	j = 0;
	while (++i < len && s[i + j])
	{
		while (check_chr(s[i + j]) == 2 && (flag > 0
				|| (flag < 0 && s[i + j] == q)))
		{
			flag *= -1;
			q = s[i + j++];
		}
		m[i] = s[i + j];
	}
	m[i] = '\0';
	s = ft_memdel(s);
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

int	open_q(t_exp *exp, char c, int type)
{
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

int	exp_quotes(t_mini *sh, t_lexer **head, int *flag)
{
	size_t	len;

	if (sh->lex_lst->token == 1 && check_exp(sh->lex_lst->cont, 1, -1) >= 0)
	{
		if (expand_word(sh, head))
			return (1);
	}
	else if (sh->lex_lst->token == 1 && check_exp(sh->lex_lst->cont, 1, -1) < 0)
	{
		len = ft_strlen(sh->lex_lst->cont);
		sh->lex_lst->cont = trim_quotes(sh->lex_lst->cont, ' ', len, -1);
		if (!sh->lex_lst->cont)
			return (1);
	}
	else if (sh->lex_lst->token > 3 && sh->lex_lst->token < 8)
		*flag = 1;
	return (0);
}
