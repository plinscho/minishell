/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:28:09 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/27 22:22:46 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exp_init(t_mini *sh)
{
	if (sh->exp)
		exp_clean(&sh->exp);
	sh->exp = malloc(sizeof(t_exp));
	if (!sh->exp)
		return (1);
	sh->exp->cont = NULL;
	sh->exp->new = NULL;
	sh->exp->var = NULL;
	sh->exp->val = NULL;
	sh->exp->alloc = 0;
	sh->exp->k = -1;
	sh->exp->j = -1;
	return (0);
}

void	exp_nano_clean(t_exp *exp)
{
	if (exp->val && exp->alloc)
		exp->val = ft_memdel(exp->val);
	if (exp->var)
		exp->var = ft_memdel(exp->var);
	exp->alloc = 0;
	exp->k = -1;
}

void	exp_clean(t_exp **exp)
{
	if (!(*exp))
		return ;
	exp_nano_clean(*exp);
	(*exp)->cont = NULL;
	(*exp)->new = NULL;
	*exp = ft_memdel(*exp);
}

/*
If type = 1 - It's a word (token 1) 0
if type = 3 - it's a string "" (token 3) 1
*/
int	exp_start(t_mini *sh, char *cont, int type)
{
	sh->exp->cont = cont;
	sh->exp->k = new_len(sh, cont, type);
	if (sh->exp->k < 0)
		return (1);
	sh->exp->new = malloc(sh->exp->k + 1);
	if (!sh->exp->new)
		return (1);
	sh->exp->alloc = 0;
	sh->exp->k = -1;
	sh->exp->j = -1;
	sh->exp->fl = 0;
	sh->exp->q = ' ';
	return (0);
}

char	*exp_file(t_mini *sh, char *cont, t_fd *new)
{
	char	*str;

	if (sh->lex_lst->token == 1 && check_exp(cont, sh->lex_lst->token, -1) < 0)
		return (trim_quotes(cont, ' ', ft_strlen(cont), -1));
	else if (new->type == 6 || check_exp(cont, sh->lex_lst->token, -1) < 0)
		return (cont);
	if (sh->exp)
		exp_clean(&sh->exp);
	if (exp_init(sh))
		return (NULL);
	str = expand_str(sh, cont, sh->lex_lst->token, -1);
	if (!str)
		return (ft_memdel(cont));
	if (check_file_exp(str))
	{
		str = ft_memdel(str);
		new->exp = 1;
		return (cont);
	}
	if (sh->lex_lst->token == 1)
		return (trim_quotes(str, ' ', ft_strlen(str), -1));
	cont = ft_memdel(cont);
	return (str);
}
