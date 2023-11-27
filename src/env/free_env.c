/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:30:40 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/27 19:47:00 by plinscho         ###   ########.fr       */
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

void	free_env_lst(t_mini *sh)
{
	t_env	*s_tmp = NULL;
	t_env	*e_tmp = NULL;
	t_env	*prev_node = NULL;

	e_tmp = sh->env_lst;
	s_tmp = sh->env_sec;
	while (e_tmp)
	{
		ft_memdel(e_tmp->env_key);
		ft_memdel(e_tmp->env_val);
		ft_memdel(e_tmp->env_full);
		prev_node = e_tmp;
		e_tmp = e_tmp->next;
		ft_memdel(prev_node);
	}
	while (s_tmp)
	{
		s_tmp->env_key = ft_memdel(s_tmp->env_key);
		s_tmp->env_full = ft_memdel(s_tmp->env_full);
		if (s_tmp->env_val)
			s_tmp->env_val = ft_memdel(s_tmp->env_val);
		prev_node = e_tmp;
		s_tmp = s_tmp->next;
		prev_node = ft_memdel(prev_node);
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
