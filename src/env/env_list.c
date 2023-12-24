/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:24:16 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/24 18:18:05 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_getkey_node(char *new_key, t_env *list)
{
	t_env	*head;

	head = list;
	while (list->next)
	{
		if (ft_strcmp(new_key, list->env_key) == 0)
			return (list);
		list = list->next;
	}
	list = head;
	return (NULL);
}

int	env_val_update(t_env *head, char *key, char *n_value)
{
	t_env	*tmp;
	size_t	len;

	tmp = head;
	len = ft_strlen(key);
	while (tmp != NULL)
	{
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
}

int	env_add_last(t_mini *sh, char *name, char *value, int has_value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (1);
	new_env->env_key = ft_strdup(name);
	if (has_value)
		new_env->env_val = ft_strdup(value);
	new_env->next = NULL;
	if (!new_env->env_key || (has_value && !new_env->env_val))
	{
		unset_free(new_env);
		return (1);
	}
	add_env_to_list(sh, new_env);
	return (0);
}

int	add_or_update_env(t_mini *sh, char *name, char *value)
{
	t_env	*env;
	int		has_val;

	has_val = 1;
	if (value == NULL)
		has_val = 0;
	env = sh->env_lst;
	while (env != NULL)
	{
		if (ft_strncmp(env->env_key, name, ft_strlen(name)) == 0
			&& ft_strlen(env->env_key) == ft_strlen(name))
		{
			if (env->env_val)
				free(env->env_val);
			env->env_val = ft_strdup(value);
			if (!env->env_val && value)
				return (err_break(sh, "malloc", NULL, 12));
			return (0);
		}
		env = env->next;
	}
	if (env_add_last(sh, name, value, has_val))
		return (err_break(sh, "malloc", NULL, 12));
	return (0);
}
