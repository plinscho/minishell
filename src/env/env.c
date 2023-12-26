/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:51:14 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/26 16:06:21 by nzhuzhle         ###   ########.fr       */
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
		return (ft_strdup(key));
	key_len = ft_strlen(key);
	val_len = ft_strlen(value);
	env_full = (char *)malloc(key_len + val_len + 2);
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

// option 1 is for complete variables (with value)
size_t	env_var(t_env *head, int option)
{
	t_env	*tmp;
	size_t	env_cases;

	tmp = head;
	env_cases = 0;
	if (option == 1)
	{
		while (tmp)
		{
			env_cases++;
			tmp = tmp->next;
		}
		return (env_cases);
	}
	else if (option == 2)
	{
		while (tmp->next)
		{
			if (tmp->env_val)
				env_cases++;
			tmp = tmp->next;
		}
		return (env_cases);
	}
	return (0);
}

// Old function below, but shouldn't be used anymore
char	**env_converter(t_env *env)
{
	t_env			*tmp;
	char			**grid;
	unsigned int	i;

	if (!env)
		return (NULL);
	grid = (char **)malloc(sizeof(char *) * (env_var(env, 1) + 1)); // check all this
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
	grid[i] = NULL;
	return (grid);
}

void	add_env_to_list(t_mini *sh, t_env *new_env)
{
	t_env	*head;
	t_env	*tmp;

	head = sh->env_lst;
	tmp = sh->env_lst;
	if (new_env == NULL)
		return ;
	if (head == NULL)
	{
		sh->env_lst = new_env;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_env;
}

int	first_env(t_mini *sh, char **env)
{
	t_env	*s_env;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		s_env = malloc(sizeof(t_env));
		if (!s_env)
			return (1);
		s_env->env_key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		s_env->env_val = ft_strdup(getenv(s_env->env_key));
		s_env->next = NULL;
		add_env_to_list(sh, s_env);
		if (!s_env->env_key || !s_env->env_val)
			return (free_env_lst(sh->env_lst));
		i++;
	}
	return (0);
}

/*
char	**env_converter(t_env *env)
{
	t_env			*tmp;
	char			**grid;
	size_t			nodes;
	unsigned int	i;
	
	if (!env)
		return (NULL);
	nodes = env_var(env, 2);
	grid = (char **)malloc((sizeof(char *) * (nodes + 1) + 1));
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
*/
