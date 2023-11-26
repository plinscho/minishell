/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:03:17 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/26 20:16:08 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>


size_t	env_variables(t_env *head)
{
	t_env	*tmp = NULL;
	size_t	env_cases;
	
	tmp = head;
	env_cases = 0;
	while (tmp)
	{
		env_cases++;
		tmp = tmp->next;
	}
	return (env_cases);	
}


char	*get_key(char *og_env, int *hasval)
{
	unsigned int	i;
	char			*key = NULL;
	
	i = 0;
	if (!og_env)
		return (NULL);
	printf("og: %s\n", og_env);
	while (og_env[i] != '\0' || og_env[i] != '=')
		i++;
	if (og_env[i] == '\0')
	{
		*hasval = 0;
		return (NULL);
	}
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
	val = ft_strdup(og_env);
	if (!val)
		return (NULL);
	return (val);
}

int		env_converter(t_mini *sh)
{
	if (allocate_env(sh, env_variables(sh->env_lst)) == -1)	// if the malloc fails
	{
		printf("Error in converting env to char **\n");
		return (-1);
	}
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

void	print_env(t_env *head, char **env)
{
	t_env	*tmp;
	int		i;

	tmp = head;
	i = 0;
	if (tmp)
	{
		while (tmp)
		{
			ft_printf("Node[%d] | %s\n", i, tmp->env_full);
			tmp = tmp->next;
			i++;
		}
	}
	if (*env)
	{
		i = 0;
		while(env[i])
		{
			ft_printf("char_env[%d]: %s\n", i, env[i]);
			i++;
		}
	}
	ft_printf("\n");
}