/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:03:17 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/02 15:36:30 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		allocate_env(t_mini *sh, size_t n)
{
	char			**env_result = NULL;
	t_env			*tmp = NULL;
	unsigned int	i;
	char			err;

	if (sh->env)
		arr_clean(sh->env, 1);
	tmp = sh->env_lst;
	i = 0;
	err = 0;
	env_result = ft_calloc(n + 1, sizeof(char *));
	if (!env_result)
		return (-1);
	while (i <= n && tmp != NULL)
	{
		env_result[i] = ft_strdup(tmp->env_full);
		if (!env_result[i]) 
			err = -1;
		tmp = tmp->next;
		i++;
	}
	env_result[i] = NULL;
	sh->env = env_result;
	return (err);
}

char	*get_key(char *og_env, int *hasval)
{
	unsigned int	i;
	char			*key = NULL;
	
	i = 0;
	*hasval = 1;
	while (og_env[i] && og_env[i] != '=') 
		i++;
	if (og_env[i] == '\0')
		*hasval = 0;
	key = ft_strndup(og_env, i);
	if (!key)
		return (NULL);
	return (key);
}

char	*get_val(char *og_env)
{
	unsigned int	i;
	char			*val = NULL;

	i = 0;
	while (og_env[i] != '=')
		og_env++;
	og_env++;
	val = ft_strdup(og_env); // protect the ft_strdup
	if (!val)
		return (NULL);
	return (val);
}

int		env_converter(t_mini *sh)
{
	if (allocate_env(sh, env_variables(sh->env_lst, 2)) == -1)	// if the malloc fails
		return (-1);
	return (0);
}

int		get_env(t_mini *sh, char **env)
{
	unsigned int	i;

	sh->env_lst = NULL;
	i = 0;
	while (env[i])
	{
		if (!(ft_envadd_back(&sh->env_lst, envnode_new(env[i]))))
			return (-1);	// If malloc fails in new node it 
		i++;
	}
	return (0);
}

