/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:42:13 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/07 16:43:41 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_env(t_mini *sh)
{
	t_env	*tmp;

	if (sh && sh->env_lst)
	{
		tmp = sh->env_lst;
		while (tmp->next)
		{
			if (*tmp->env_val != '\0')
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