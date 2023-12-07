/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:28:09 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/07 17:35:20 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expanser.h"

int	exp_init(t_mini *sh)
{
	sh->exp = malloc(sizeof(t_exp));
	if (!sh->exp)
		return (1);
	sh->exp->cont = NULL; //??
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
	if ((*exp)->cont)
		(*exp)->cont = ft_memdel((*exp)->cont);
	if ((*exp)->new)
		(*exp)->new = ft_memdel((*exp)->new);
	*exp = ft_memdel(*exp);
}