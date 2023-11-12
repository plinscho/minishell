/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:30:40 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/12 16:16:52 by plinscho         ###   ########.fr       */
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
		ft_memdel(tmp_node->env_full);
		prev_node = tmp_node;
		tmp_node = tmp_node->next;
		ft_memdel(prev_node);
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
		ft_memdel(env_tmp[i]);
		i++;
	}
	ft_memdel(env_tmp);
}

void	free_env(t_mini *sh)
{
	printf("Cleaning env\n");
	if (sh->env)
		free_env_chr(sh);
	printf("Cleaned char **\n");
	free_env_lst(sh);
	printf("Cleaned list\n");

}
