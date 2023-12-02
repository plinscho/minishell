/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:30:40 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/02 18:51:43 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_lst(t_env *head)
{
	t_env	*e_tmp = NULL;
	t_env	*prev_node = NULL;

	e_tmp = head;
	while (e_tmp)
	{
		e_tmp->env_key = ft_memdel(e_tmp->env_key);
		e_tmp->env_val = ft_memdel(e_tmp->env_val);
		prev_node = e_tmp;
		e_tmp = e_tmp->next;
		ft_memdel(prev_node);
		prev_node = NULL;
	}
}
/*
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
*/
void	free_env(t_mini *sh)
{
	printf("Cleaning env\n");
	if (sh->env)
		arr_clean(sh->env, 0);
	printf("Cleaned char **\n");
	free_env_lst(sh->env_lst);
	printf("Cleaned list\n");
}
