/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:03:17 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/10 16:39:03 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


size_t	env_variables(char **og_env)
{
	size_t	env_cases;
	
	env_cases = 0;
	while (og_env[env_cases])
		env_cases++;
	return (env_cases);	
}


char	*get_key(char *og_env)
{
	unsigned int	i;
	char			*key = NULL;

	i = 0;
	while (og_env[i] != '=')
		i++;
	key = ft_strndup(og_env, i);
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
	val = ft_strdup(og_env);
	return (val);
}

void	print_env(t_env *head)
{
	t_env	*tmp;
	int		i;

	tmp = head;
	i = 0;
	while (tmp)
	{
		ft_printf("Node[%d]\nkey: %s\nval: %s\n\n", i, tmp->env_key, tmp->env_val);
		tmp = tmp->next;
		i++;
	}
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