/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:29:44 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/29 21:45:18 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		key_exists(t_env *head, char *key)
{
	t_env	*etpm;

	etpm = head;
	while (head->next)
	{
		if (ft_strcmp(key, etpm->env_key))
			return (1);
		etpm = etpm->next;
	}
	return (0);
}

char	*ft_get_value(t_mini *sh, char *key)
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