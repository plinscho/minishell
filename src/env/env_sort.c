/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:20:18 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/23 17:24:23 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_sort_print(t_env *env)
{
	t_env	*tmp;
	char	*tmp_name;
	char	*tmp_value;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->next != NULL)
		{
			if (ft_strcmp(tmp->env_key, tmp->next->env_key) > 0)
			{
				tmp_name = tmp->env_key;
				tmp_value = tmp->env_val;
				tmp->env_key = tmp->next->env_key;
				tmp->env_val = tmp->next->env_val;
				tmp->next->env_key = tmp_name;
				tmp->next->env_val = tmp_value;
				tmp = env;
			}
		}
		tmp = tmp->next;
	}
}

void	sort_env(t_env *head)
{
	t_env	*head_bk;

	head_bk = head;
	if (!head_bk)
		return ;
	print_sort_print(head);
	head = head_bk;
}
