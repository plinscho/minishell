/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:29:44 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/23 17:22:39 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_value(t_mini *sh, char *key)
{
	t_env	*tmp;

	if (!sh || !key)
		return (NULL);
	tmp = sh->env_lst;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->env_key, ft_longer(key, tmp->env_key)) == 0)
			return (tmp->env_val);
		else
			tmp = tmp->next;
	}
	return (NULL);
}
