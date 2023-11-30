/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:18:38 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/30 20:18:51 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expanser.h"

int	new_len()

char	*expand_str(char *cont)
{
	int	len;
	int	i;
	char	*new;

	i = 0;
	while (cont[i] && cont[i + 1])
	{
		if (cont[i] == '$' && check_chr(cont[i + 1]) > 1)
			break ;
		i++;
	}
	if (!cont[i + 1])
		return (cont);
	len = new_len(); // start here next time 
	return (new);

}

/*
	Function designed to expand the $ into the command.
	
*/
int	expanser(t_mini *sh, t_lexer *head)
{
	int	flag;

	flag = 0;
	while (sh->lex_lst)
	{
		if (sh->lex_lst->token == 3 && sh->lex_lst->cont)
		{
			sh->lex_lst->cont = expand_str(sh->lex_lst->cont);
			if (!sh->lex_lst->cont)
				return (err_break(sh_restore(&sh, head, NULL), "malloc", NULL, 12));
		}
		else if (sh->lex_lst->token == 1 && !flag)
		{	
			if (!expand_word(&sh->lex_lst))
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