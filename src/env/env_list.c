/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:24:16 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/09 19:47:14 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
static t_env	*last_env(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}
*/


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
//	sh->env_lst = head;
}

// option 1 is for complete variables (with value)
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
		while (tmp->next)
		{
			if (tmp->env_val)
				env_cases++;
			tmp = tmp->next;
		}
		return (env_cases);	
	}
	else
		return (0);
}
