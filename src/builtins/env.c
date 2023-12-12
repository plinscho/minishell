/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:42:13 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/12 17:27:00 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_env(t_mini *sh, t_pipe *p)
{
	t_env	*tmp;

	(void)p;
	if (sh && sh->env_lst)
	{
		tmp = sh->env_lst;
		while (tmp)
		{
			if (tmp->env_val != NULL)
			{
				ft_putstr_fd(tmp->env_key, 1);
				ft_putstr_fd("=", 1);
				ft_putendl_fd(tmp->env_val, 1);
			}
			tmp = tmp->next;
		}
		return (0);
	}
	else
		return (1);
}