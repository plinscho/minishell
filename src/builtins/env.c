/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:42:13 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/19 19:57:21 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_env(t_mini *sh, t_pipe *p)
{
	t_env	*tmp;
	int output;
	
	output = p->out_fd;
	if (output < 0 )
		output = 1;
	if (sh && sh->env_lst)
	{
		tmp = sh->env_lst;
		while (tmp)
		{
			if (tmp->env_val != NULL)
			{
				ft_putstr_fd(tmp->env_key, output);
				ft_putstr_fd("=", output);
				ft_putendl_fd(tmp->env_val, output);
				ft_putstr_fd("\n", output);
			}
			tmp = tmp->next;
		}
		return (0);
	}
	else
		return (1);
}