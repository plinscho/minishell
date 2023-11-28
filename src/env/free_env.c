/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:30:40 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/28 19:44:33 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_nodel(t_env *head, char *key)
{
	t_env 	*etmp;
	size_t	len;

	etmp = head;
	len = ft_strlen(key);
	while (head->next != NULL)
	{
		if (ft_strncmp(head->env_key, key, len) == 0)
		{
			etmp->env_key = ft_memdel(etmp->env_key);
			etmp->env_full = ft_memdel(etmp->env_full);
			if (etmp->env_val)
				etmp->env_val = ft_memdel(etmp->env_val);
		}
		etmp = etmp->next;
	}
}

void	free_env_lst(t_env *head)
{
	t_env	*e_tmp = NULL;
	t_env	*prev_node = NULL;

	e_tmp = head;
	while (e_tmp)
	{
		e_tmp->env_key = ft_memdel(e_tmp->env_key);
		if (e_tmp->env_val)
			e_tmp->env_val = ft_memdel(e_tmp->env_val);
		e_tmp->env_full = ft_memdel(e_tmp->env_full);
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
	free_env_lst(sh->env_sec);
	printf("Cleaned list\n");
}
