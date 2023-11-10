/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:24:16 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/10 17:55:33 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int		allocate_env(t_mini *sh, size_t n)
{
	t_env			*tmp = NULL;
	unsigned int	i;
	char			err;
	char			**env_result;

	tmp = sh->env_lst;
	i = 0;
	err = 0;
	env_result = ft_calloc(n + 1, sizeof(char *));
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
	i = 0;
	while (env_result[i])
		free(env_result[i++]);
	free(env_result[i]);
	return (err);
}

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

void	env_del(t_mini *sh)
{
	t_env	*tmp_node = NULL;
	t_env	*prev_node = NULL;
	char	**env_del = NULL;
	int 	i;

	i = 0;
	env_del = sh->env;
	tmp_node = sh->env_lst;
	while (tmp_node)
	{
		free(tmp_node->env_key);
		free(tmp_node->env_val);
		free(tmp_node->env_full);
		prev_node = tmp_node;
		tmp_node = tmp_node->next;
		free(prev_node);
	}
	while (env_del[i] != NULL)
	{
		free(env_del[i]);
		i++;
	}
	free(sh->env);
}

int		ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp_node = NULL;

	if (!new)
		return (0);	
	if (!*lst)
	{
		*lst = new;
		return (1);
	}
	tmp_node = ft_envlast(*lst);
	tmp_node -> next = new;
	return (1);
}

t_env	*ft_envlast(t_env *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}