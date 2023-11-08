/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:24:16 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/06 18:21:40 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*envnode_new(char *env)
{
	t_env	*new_list;

	new_list = malloc(sizeof(t_env));
	if (!new_list)	// Manage errors??
		return (NULL);
	new_list->env_key = get_key(env);
	new_list->env_val = get_val(env);
	new_list->env_full = ft_strdup(env);
	new_list->next = NULL;
	return (new_list);
}

void	env_del(t_env *head)
{
	t_env	*tmp_node = NULL;
	t_env	*prev_node = NULL;

	tmp_node = head;
	while (tmp_node)
	{
		
		free(tmp_node->env_key);
		free(tmp_node->env_val);
		free(tmp_node->env_full);
		prev_node = tmp_node;
		tmp_node = tmp_node->next;
		free(prev_node);
	}
	
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp_node = NULL;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp_node = ft_envlast(*lst);
	tmp_node -> next = new;
}

t_env	*ft_envlast(t_env *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}
