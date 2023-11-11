/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:30:40 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/11 19:13:38 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	free_env_lst(t_mini *sh)
{
	t_env	*tmp_node = NULL;
	t_env	*prev_node = NULL;

	tmp_node = sh->env_lst;
	while (tmp_node)
	{
		ft_memdel(tmp_node->env_key);
		ft_memdel(tmp_node->env_val);
		free(tmp_node->env_full);
		prev_node = tmp_node;
		tmp_node = tmp_node->next;
		free(prev_node);
	}
}

void	free_env_chr(t_mini *sh)
{
	char			**env_tmp = NULL;
	unsigned int	i;

	env_tmp = sh->env;
	i = 0;
	while (env_tmp[i])
	{
		free(env_tmp[i]);
		i++;
	}
	free(env_tmp);
}

void	free_env(t_mini *sh)
{
	free_env_chr(sh);
	free_env_lst(sh);
}
