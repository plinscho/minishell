/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:18:38 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/06 19:11:48 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expanser.h"

char	*expand_hd(t_mini *sh, char *cont, int type)
{
	if (type == 9)
		return (cont);
	if (check_exp < 0)
		return (cont);
	cont = expand_str(sh, cont, -1, -1);
	return (cont);
}

//char	*add_var(t_mini *sh, char *cont, int j)

int	exp_start(t_mini *sh, char *cont)
{
	sh->exp->cont = cont;
	sh->exp->k = new_len(sh, cont);
	if (sh->exp->k < 0)
		return (1);
	sh->exp->new = malloc(sh->exp->k + 1);
	if (!sh->exp->new)
		return (1);
	sh->exp->k = -1;
	return (0);
}

char	*expand_str(t_mini *sh, char *cont, int i, int j)
{
//	printf("[EXP STR] entered exp str, cont-- %s\n", cont); //erase
//	printf("[EXP STR] final lenth -- %i\n", k); //erase
	if (exp_start(sh, cont))
		return (NULL);
	while (cont[++i])
	{
		if (cont[i] != '$' || !cont[i + 1])
			sh->exp->new[++j] = cont[i];
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
				sh->exp->new[++j] = sh->exp->val[sh->exp->k];
			i += ft_strlen(sh->exp->var);
			//		printf("[EXP STR] after get value, str[i] -- %c, str[i-1] -- %c\n", cont[i], cont[i - 1]); //erase
			exp_nano_clean(sh->exp);
		}
	}
	sh->exp->new[++j] = '\0';
	sh->exp->cont = ft_memdel(sh->exp->cont);
	return (sh->exp->new);
}

/*int		expand_word(t_lexer **lex, int flag)
{
	(void *)lex;
	return (flag);
}*/

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
		check_exp(sh->lex_lst->cont, 1) != -1)
		{
	//		printf("[EXPANSE] BEFORE EXP STRING content: %s\n", sh->lex_lst->cont); //erase
			sh->lex_lst->cont = expand_str(sh, sh->lex_lst->cont, -1, -1);
			if (!sh->lex_lst->cont)
				return (err_break(sh_restore(&sh, head, NULL), "malloc", NULL, 12));
		}
		/*else if (sh->lex_lst->token == 1 && check_exp(sh->lex_lst->cont, 0) != -1)
		{	
			if (!expand_word(sh, &sh->lex_lst, flag))
				return (err_break(sh_restore(&sh, head, NULL), "malloc", NULL, 12));
		}*/
		else if (sh->lex_lst->token > 3 && sh->lex_lst->token < 8)
			flag = 1;
		if (sh->lex_lst->token > 0 && sh->lex_lst->token < 4 && flag)
			flag = 0;
		sh->lex_lst = sh->lex_lst->next;
	}
	sh_restore(&sh, head, NULL);
	return (0);
}