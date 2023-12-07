/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:18:38 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/07 21:41:50 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expanser.h"

/*
type = 9 - no expansion
type = 6 - expansion type "" (1)
*/
char	*expand_hd(t_mini *sh, char *cont, int type)
{
	if (type == 9)
		return (cont);
	if (check_exp(cont, 1, -1) < 0)
		return (cont);
	cont = expand_str(sh, cont, -1, -1);
	return (cont);
}

/*
If type = 0 - It's a word (token 1)
if type = 1 - it's a string "" (token 3)
*/
char	*expand_str(t_mini *sh, char *cont, int type, int i)
{
//	printf("[EXP STR] entered exp str, cont-- %s\n", cont); //erase
//	printf("[EXP STR] final lenth -- %i\n", k); //erase
	if (exp_start(sh, cont, type))
		return (NULL);
	while (cont[++i])
	{
		if (cont[i] != '$' || !cont[i + 1])
			sh->exp->new[++sh->exp->j] = cont[i];
		else
		{
	//		printf("[EXP STR] entered else, str[i] -- %c\n", cont[i]); //erase
			sh->exp->var = get_var(&cont[i + 1]);
	//		printf("[EXP STR] var -- %s\n", sh->exp->var); //erase
			if (!sh->exp->var)
				return (NULL);
			sh->exp->val = check_value(sh, sh->exp->var);
			if (*sh->exp->var == '?' && !sh->exp->val)
				return (NULL);
			while (sh->exp->val && sh->exp->val[++sh->exp->k])
				sh->exp->new[++sh->exp->j] = sh->exp->val[sh->exp->k];
			i += ft_strlen(sh->exp->var);
			//		printf("[EXP STR] after get value, str[i] -- %c, str[i-1] -- %c\n", cont[i], cont[i - 1]); //erase
			exp_nano_clean(sh->exp);
		}
	}
	sh->exp->new[++sh->exp->j] = '\0';
	sh->exp->cont = ft_memdel(sh->exp->cont);
	return (sh->exp->new);
}

t_lexer *read_word_exp(char *in, int *i, char q, int j)
{
	char	*cont;

//	printf("[RW]You entered: input - %c\n", in[j]); //erase
	while (in[j] && in[j + 1] && in[j + 1] != ' ' && in[j + 1] != '\'' && \
	in[j + 1] != '\"')
		j++;
	while (in[j] && in[j + 1] && (in[j + 1] == '\'' || in[j + 1] == '\"'))
		j = word_in_quotes(in, &q, j);
//	printf("[RW] After iteration: input - %c, j - %i\n", in[j], j); //erase
//	if (q != ' ')
//		(*i)++;
	cont = ft_substr(in, 0, j + 1);
	if (!cont)
		return (NULL);
	*i += j;
//	printf("[RW] leaving: token - %s, in[i] -- %c, i -- %i\n", cont, in[j], *i); //erase
	return (lex_new(cont, 1));
}

int		expand_word(t_mini *sh, t_lexer **lex)
{
	char	*str;
	t_lexer	*new;
	t_lexer	*old;
	int		i;

	str = expand_str(sh, (*lex)->cont, 0, -1);
	if (!str)
		return (1);
	old = *lex;
	*lex = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			new = read_space(&str[i], &i);
		else
			new = read_word_exp(&str[i], &i, ' ', 0);
		if (!new)
			return (1);
		else
			lex_add(lex, new);
	}
	lex_last(*lex)->next = old->next;
	old->next = NULL;
	str = ft_memdel(str);
//	trim quotes here??? no, cause there are strings where no exp but quotes
//	trim quotes in parser? expand filename in parser??
	return (lex_clean(&old));
}

/*
	Function designed to expand the $ into the command.
*/
int	expanser(t_mini *sh, t_lexer *head)
{
	int	flag;

	flag = 0;
	if (exp_init(sh))
		return (0);
	while (sh->lex_lst)
	{
	//	printf("[EXPANSE] lex -- content: %s, type; %i\n", sh->lex_lst->cont, sh->lex_lst->token); //erase
	//	printf("[EXPANSE] check if exp: %i\n", check_exp(sh->lex_lst->cont, 1)); //erase
	//	printf("[EXPANSE] get value $0: %s\n", ft_get_value(sh, "0")); //erase
		if (sh->lex_lst->token == 3 && sh->lex_lst->cont && \
		check_exp(sh->lex_lst->cont, 1, -1) != -1)
		{
	//		printf("[EXPANSE] BEFORE EXP STRING content: %s\n", sh->lex_lst->cont); //erase
			sh->lex_lst->cont = expand_str(sh, sh->lex_lst->cont, 1, -1);
			if (!sh->lex_lst->cont)
				return (err_break(sh_restore(&sh, head, NULL), "malloc", NULL, 12));
		}
		else if (sh->lex_lst->token == 1 && check_exp(sh->lex_lst->cont, 0, -1) >= 0 && !flag)
		{	
			if (expand_word(sh, &sh->lex_lst))
				return (err_break(sh_restore(&sh, head, NULL), "malloc", NULL, 12));
		}
		else if (sh->lex_lst->token > 3 && sh->lex_lst->token < 8)
			flag = 1;
		if (sh->lex_lst->token > 0 && sh->lex_lst->token < 4 && flag)
			flag = 0;
		sh->lex_lst = sh->lex_lst->next;
	}
	sh_restore(&sh, head, NULL);
	return (0);
}