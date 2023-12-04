/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:51:14 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/04 16:30:17 by plinscho         ###   ########.fr       */
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
	grid = (char **)malloc(sizeof(char *) * nodes + 1);
	tmp = env;
	i = 0;
	while (tmp->next)
	{
		if (tmp->env_val != NULL)
		{
			grid[i] = ft_envfull(tmp->env_key, tmp->env_val);
			if (!grid[i])
				return (NULL);
			i++;
		}
		tmp = tmp->next;
	}
	grid[i] = NULL;
	return (grid);
}

void	add_or_update_env(t_mini *sh, char *name, char *value)
{
	t_env	*env;
	t_env	*new_env;

	env = sh->env_lst;
	while (env != NULL)
	{
		if (ft_strncmp(env->env_key, name, ft_strlen(name)) == 0
			&& ft_strlen(env->env_key) == ft_strlen(name))
		{
			free(env->env_val);
			env->env_val = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	new_env = malloc(sizeof(t_env));
	new_env->env_key = ft_strdup(name);
	new_env->env_val = ft_strdup(value);
	new_env->next = NULL;
	add_env_to_list(&sh->env_lst, new_env);
}

int		first_env(t_mini *sh, char **env)
{
	t_env	*sh_env;
	int		i;

	i = ~0;
	while (env[++i] != NULL)
	{
		sh_env = malloc(sizeof(t_env));
		if (!sh_env)
			return (1);
		sh_env->env_key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		sh_env->env_val = ft_strdup(getenv(sh_env->env_key));
		sh_env->next = NULL;
		if (!sh_env->env_key || !sh_env->env_val)
			return (1);
		add_env_to_list(&sh->env_lst, sh_env);
	}
	return (0);
}
