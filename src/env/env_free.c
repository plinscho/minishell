/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:30:40 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/28 14:42:25 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	free_env_lst(t_env *head)
{
	t_env	*e_tmp;
	t_env	*prev_node;

	e_tmp = head;
	while (e_tmp)
	{
		if (e_tmp->env_key)
			e_tmp->env_key = ft_memdel(e_tmp->env_key);
		if (e_tmp->env_val)
			e_tmp->env_val = ft_memdel(e_tmp->env_val);
		prev_node = e_tmp;
		e_tmp = e_tmp->next;
		ft_memdel(prev_node);
		prev_node = NULL;
	}
	return (1);
}

void	free_env(t_mini *sh)
{
	printf("ENTERED FREE ENV\n");
	if (sh->exe)
		free(sh->exe);
	if (sh->env != NULL)
		sh->env = arr_clean(sh->env, 0);
	free_env_lst(sh->env_lst);
	sh->env_lst = NULL;
	printf("AFTER FREE ENV: %p, %p\n", sh->env, sh->env_lst);
}
