/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:42:13 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/26 17:54:23 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_env(t_mini *sh)
{
	unsigned int	i;

	i = 0;
	if (sh && sh->env)
	{
		while (sh->env[i])
		{
			ft_putstr_fd(sh->env[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
		return (0);
	}
	else
		return (1);
}