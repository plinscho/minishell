/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:29:44 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/28 20:58:16 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

# define BUFF_SIZE 1024

char		*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int			is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->env_val);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->env_val);
			env->env_val = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int			env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->env_val == NULL)
	{
		env->env_full = ft_strdup(value);
		return (0);
	}
	if (!(new = malloc(sizeof(t_env))))
		return (-1);
	new->env_full = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (0);
}

char *ft_get_value(t_mini *sh, char *key)
{
	t_env	*tmp = NULL;
	
	if (!sh || !key)
		return (NULL);

	tmp = sh->env_lst;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->env_key, ft_strlen(key)) == 0)
			return (tmp->env_val);
		else
			tmp = tmp->next;
	}
	ft_putstr_fd("Error: Key not found.\n", 2);
	return (NULL);
}