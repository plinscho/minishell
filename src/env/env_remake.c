/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:26:16 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/28 22:26:13 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

//int		bubble_env(t_env *head)


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
				return (-1);	// If malloc fails in new node it 
		e_tmp = e_tmp->next;
	}
	e_tmp = sh->env_sec;
	sort_env(sh->env_sec);
	return (0);
}

int		rebase_env(t_env *env_new, char* env_key, char *env_val)
{
	env_new->env_key = ft_strdup(env_key);
	env_new->env_val = ft_strdup(env_val);
	free(env_new->env_full);
	env_new->env_full = ft_smart_join(env_key, "=", env_val);
	if (env_new->env_full == NULL)
		return (1);
	return (0);
}
int		env_add_update(t_mini *sh, char *key, char *n_value)
{
	t_env	*tmp;
//	t_env	*env_new;
	size_t	len;
	
//	env_new = NULL;
	tmp = sh->env_lst;
	len = ft_strlen(key);
	while (tmp != NULL)
	{
		// Found an old env key
		if (ft_strncmp(tmp->env_key, key, len) == 0 \
			&& len == ft_strlen(tmp->env_key))
		{
			tmp->env_val = ft_strdup(n_value);
			if (!tmp->env_val)
				return (1);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
	/*
	env_new = malloc(sizeof(t_env));
	if (!env_new)
		return (errno);
	if (rebase_env(env_new, env_new->env_key, env_new->env_val))
		return (1);
	return (0);
	*/
}