/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:23:56 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/01 23:29:24 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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


void	env_del(t_env **head)
{
	t_env	*tmp_node = NULL;
	t_env	*node = NULL;

	tmp_node = *head; 
	while (tmp_node)
	{
		
		free(tmp_node->env_key);
		free(tmp_node->env_val);
		free(tmp_node->env_full);
		node = tmp_node;
		tmp_node = tmp_node->next;
		free(node);
	}
}

/*
t_env	*ft_lstlast(t_env *lst)
{
	if (lst)
		while (lst -> next)
			lst = lst -> next;
	return (lst);
}

void	ft_lstadd_front(t_env **lst, t_env *new)
{
	new -> next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp_node;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp_node = ft_lstlast(*lst);
	tmp_node -> next = new;
}
*/