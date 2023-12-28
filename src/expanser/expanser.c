/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:18:38 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/27 22:23:09 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
type = 9 - no expansion
type = 6 - expansion type "" (3)
*/
char	*expand_hd(t_mini *sh, char *cont, int type)
{
	if (type == 9)
		return (cont);
	if (check_exp(cont, 3, -1) < 0)
		return (cont);
	if (exp_init(sh))
		return (ft_memdel(cont));
	cont = expand_str(sh, cont, 3, -1);
	return (cont);
}

/*
If type = 1 - It's a word (token 1)  0
if type = 3 - it's a string "" (token 3) 1
*/
char	*expand_str(t_mini *sh, char *cont, int type, int i)
{
	if (exp_start(sh, cont, type))
		return (NULL);
	while (cont[++i])
	{
		if (open_q(sh->exp, cont[i], type) || cont[i] != '$' || !cont[i + 1])
			sh->exp->new[++sh->exp->j] = cont[i];
		else
		{
			sh->exp->var = get_var(&cont[i + 1]);
			if (!sh->exp->var)
				return (NULL);
			sh->exp->val = check_value(sh, sh->exp->var);
			if (*sh->exp->var == '?' && !sh->exp->val)
				return (NULL);
			while (sh->exp->val && sh->exp->val[++sh->exp->k])
				sh->exp->new[++sh->exp->j] = sh->exp->val[sh->exp->k];
			i += ft_strlen(sh->exp->var);
			exp_nano_clean(sh->exp);
		}
	}
	sh->exp->new[++sh->exp->j] = '\0';
	if (type == 3)
		sh->exp->cont = ft_memdel(sh->exp->cont);
	return (sh->exp->new);
}

t_lexer	*read_word_exp(char *in, int *i, char q, int j)
{
	char	*cont;

	while (in[j] && in[j + 1] && check_chr(in[0]) == 2 && in[j + 1] != in[0])
		j++;
	if (in[j] && in[j + 1] && check_chr(in[0]) == 2)
		j = j + 2;
	while (in[j] && in[j + 1] && in[j + 1] != ' ' && check_chr(in[j + 1]) != 2)
		j++;
	while (in[j] && in[j + 1] && (in[j + 1] == '\'' || in[j + 1] == '\"'))
		j = word_in_quotes(in, &q, j);
	cont = ft_substr(in, 0, j + 1);
	if (cont)
		cont = trim_quotes(cont, ' ', ft_strlen(cont), -1);
	if (!cont)
		return (NULL);
	*i += j;
	return (lex_new(cont, 1));
}

int	expand_word(t_mini *sh, t_lexer **lex)
{
	char	*str;
	t_lexer	*new;
	t_lexer	*head;
	int		i;

	str = expand_str(sh, sh->lex_lst->cont, 1, -1);
	if (!str)
		return (1);
	head = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			new = read_space(&str[i], &i);
		else
			new = read_word_exp(&str[i], &i, ' ', 0);
		if (!new)
			return (1);
		lex_add(&head, new);
		if (!str[i])
			break ;
	}
	lex_insert(sh, head, lex, sh->lex_lst);
	str = ft_memdel(str);
	return (0);
}

/*
	Function designed to expand the $ into the command.
*/
int	expanser(t_mini *sh, t_lexer *head, int flag)
{
	if (exp_init(sh))
		return (1);
	while (sh->lex_lst)
	{
		if (sh->lex_lst->token == 3 && check_exp(sh->lex_lst->cont, 3, -1) >= 0)
		{
			sh->lex_lst->cont = expand_str(sh, sh->lex_lst->cont, 3, -1);
			if (!sh->lex_lst->cont)
				return (err_break(sh_re(&sh, head, NULL), "malloc", NULL, 12));
		}
		else if (!flag)
		{
			if (exp_quotes(sh, &head, &flag))
				return (err_break(sh_re(&sh, head, NULL), "malloc", NULL, 12));
		}
		if (sh->lex_lst && sh->lex_lst->token > 0
			&& sh->lex_lst->token < 4 && flag)
			flag = 0;
		if (sh->lex_lst)
			sh->lex_lst = sh->lex_lst->next;
	}
	sh_re(&sh, head, NULL);
	return (0);
}
