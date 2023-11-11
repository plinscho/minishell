/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:24:16 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/11 19:07:52 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int		allocate_env(t_mini *sh, size_t n)
{
	char			**env_result = NULL;
	t_env			*tmp = NULL;
	unsigned int	i;
	char			err;

	tmp = sh->env_lst;
	i = 0;
	err = 0;
	env_result = ft_calloc(n + 1, sizeof(char *));
	if (!env_result)
		return (-1);
	sh->env = env_result;
	ft_printf("[allocate_env]\n");
	while (i <= n && tmp != NULL)
	{
		env_result[i] = ft_strdup(tmp->env_full);
//		printf("env[%d]: %s\n", i, env_result[i]);
		if (!env_result[i])
			err = -1;
		tmp = tmp->next;
		i++;
	}
	env_result[i] = NULL;
	return (err);

//	Create a function that frees the char **env
	i = 0;
	while (env_result[i])
		free(env_result[i++]);
	free(env_result[i]);
}

t_env	*envnode_new(char *env)
{
	t_env	*new_list;

	new_list = malloc(sizeof(t_env));
	if (!new_list)
		return (NULL);
	new_list->env_key = get_key(env);
	new_list->env_val = get_val(env);
	new_list->env_full = ft_strdup(env);
	new_list->next = NULL;
	return (new_list);
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