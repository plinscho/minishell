/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:51:14 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/15 19:35:02 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_envfull(char *key, char *value)
{
	char	*env_full;
	size_t	key_len;
	size_t	val_len;
	int		i;
	int		j;

	if (!key)
		return (NULL);
	if (!value)
		return (key);
	key_len = ft_strlen(key);
	val_len = ft_strlen(value);
	env_full = (char *)malloc(key_len + val_len +  2);
	if (!env_full)
		return (NULL);
	i = -1;
	while (key[++i])
		env_full[i] = key[i];
	env_full[i++] = '=';
	j = -1;
	while (value[++j])
		env_full[i + j] = value[j];
	env_full[i + j] = '\0';
	return (env_full);
}

char	**env_converter(t_env *env)
{
	t_env			*tmp;
	char			**grid;
	size_t			nodes;
	unsigned int	i;
	
	if (!env)
		return (NULL);
	nodes = env_variables(env, 2);
	grid = (char **)malloc((sizeof(char *) * (nodes + 1)));
	if (!grid)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->env_val != NULL)
		{
			grid[i] = ft_envfull(tmp->env_key, tmp->env_val);
			if (!grid[i])
				return (arr_clean(grid, 0));
			i++;
		}
		tmp = tmp->next;
	}
	if (i < nodes)
		grid[i] = NULL;
	return (grid);
}

int		env_add_last(t_mini *sh, char *name, char *value, int has_value)
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

int		add_or_update_env(t_mini *sh, char *name, char *value)
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
			if (!env->env_val)
				return (err_break(sh, "malloc", NULL, 12));
			return (0);
		}
		env = env->next;
	}
	if (env_add_last(sh, name, value, has_val))
		return (err_break(sh, "malloc", NULL, 12));
	return (0);
}

int		first_env(t_mini *sh, char **env)
{
	t_env	*sh_env;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		sh_env = malloc(sizeof(t_env));
		if (!sh_env)
			return (1);
		sh_env->env_key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		sh_env->env_val = ft_strdup(getenv(sh_env->env_key));
		sh_env->next = NULL;
		add_env_to_list(sh, sh_env);
		if (!sh_env->env_key || !sh_env->env_val)
			return (free_env_lst(sh->env_lst));
		i++;
	}
	return (0);
}
