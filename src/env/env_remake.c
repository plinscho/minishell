/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:26:16 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/02 12:07:14 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int		get_sec_env(t_mini *sh)
{
	t_env	*e_tmp;
	char	*full_var;

	full_var = NULL;
	e_tmp = sh->env_lst;
	while (e_tmp != NULL)
	{
		full_var = e_tmp->env_full;
		if (!(ft_envadd_back(&sh->env_sec, envnode_new(full_var))))
				return (1);	// If malloc fails in new node it 
		e_tmp = e_tmp->next;
	}
	e_tmp = sh->env_sec;
//	sort_env(sh->env_sec);
	return (0);
}

