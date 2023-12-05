/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:18:38 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/05 16:56:45 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expanser.h"


char	*expand_str(t_mini *sh, char *cont, int i)
{
	int	k;
	int	j;
	char	*var;
	char	*new;

	j = -1;
//	printf("[EXP STR] entered exp str, cont-- %s\n", cont); //erase
	k = new_len(sh, cont);
//	printf("[EXP STR] final lenth -- %i\n", k); //erase
	if (k < 0)
		return (NULL);
	new = malloc(k + 1);
	while (cont[++i])
	{
		if (cont[i] != '$' || !cont[i + 1])
			new[++j] = cont[i];
		else
		{
			k = -1;
	//		printf("[EXP STR] entered else, str[i] -- %c\n", cont[i]); //erase
			var = get_var(&cont[i + 1]);
	//		printf("[EXP STR] var -- %s\n", var); //erase
			if (!var)
				return (NULL);
			while (ft_get_value(sh, var) && ft_get_value(sh, var)[++k])
				new[++j] = ft_get_value(sh, var)[k];
			i += ft_strlen(var);
	//		printf("[EXP STR] after get value, str[i] -- %c, str[i-1] -- %c\n", cont[i], cont[i - 1]); //erase
			var = ft_memdel(var);
		}
	}
	new[++j] = '\0';
	return (new);
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
	while (sh->lex_lst)
	{
	//	printf("[EXPANSE] lex -- content: %s, type; %i\n", sh->lex_lst->cont, sh->lex_lst->token); //erase
	//	printf("[EXPANSE] check if exp: %i\n", check_exp(sh->lex_lst->cont, 1)); //erase
	//	printf("[EXPANSE] get value $0: %s\n", ft_get_value(sh, "0")); //erase
		if (sh->lex_lst->token == 3 && sh->lex_lst->cont && \
		check_exp(sh->lex_lst->cont, 1) != -1)
		{
	//		printf("[EXPANSE] BEFORE EXP STRING content: %s\n", sh->lex_lst->cont); //erase
			sh->lex_lst->cont = expand_str(sh, sh->lex_lst->cont, -1);
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