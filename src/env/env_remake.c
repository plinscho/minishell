/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:26:16 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/26 17:41:33 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>


void	rebase_env(t_env *env_new, char* env_key, char *env_val)
{
	env_new->env_key = ft_strdup(env_key);
	env_new->env_val = ft_strdup(env_val);
	free(env_new->env_full);
	env_new->env_full = ft_smart_join(env_key, "=", env_val);
}
int		env_add_update(t_mini *sh, char *key, char *n_value)
{
	t_env	*tmp;
	t_env	*env_new;
	size_t	len;
	
	env_new = NULL;
	tmp = sh->env_lst;
	len = ft_strlen(key);
	while (tmp != NULL)
	{
		// Found an old env key
		if (ft_strncmp(tmp->env_key, key, len) == 0 \
			&& len == ft_strlen(tmp->env_key))
		{
			free(tmp->env_val);
			tmp->env_val = ft_strdup(n_value);
			if (!tmp->env_val)
				return (1);
			return (0);
		}
		tmp = tmp->next;
	}
	env_new = malloc(sizeof(t_env));
	if (!env_new)
		return (errno);
	rebase_env(env_new, env_new->env_key, env_new->env_val);
	return (0);
}