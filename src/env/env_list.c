/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:24:16 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/02 19:25:49 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*last_env(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	add_env_to_list(t_env **env, t_env *new_env)
{
	if (new_env == NULL)
		return ;
	if (*env == NULL)
	{
		*env = new_env;
		return ;
	}
	last_env(*env)->next = new_env;
}

size_t	env_variables(t_env *head, int option)
{
	t_env	*tmp = NULL;
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
		while (tmp)
		{
			if (head->env_val)
				env_cases++;
			tmp = tmp->next;
		}
		return (env_cases);	
	}
	else
		return (0);
}
