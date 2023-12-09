/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:43:15 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/09 16:06:48 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset_free(t_env *env)
{
	env->env_key = ft_memdel(env->env_key);
	env->env_val = ft_memdel(env->env_val);
	env = ft_memdel(env);
}

void	unset_var(t_mini *sh, char *var)
{
	t_env	*node;
	t_env	*tmp;

	node = sh->env_lst;
	tmp = NULL;
	if (ft_strcmp(node->env_key, var) == 0)
	{
		sh->env_lst = sh->env_lst->next;
		unset_free(node);
		return ;
	}
	while (node != NULL && ft_strcmp(node->env_key, var) != 0)
	{
		tmp = node;
		node = node->next;
	}
	if (node == NULL)
		return ;
	tmp->next = node->next;
	unset_free(node);
}

int		ft_unset(t_mini *sh)
{
	char	**args;
//	char	**new_env;
	int		i;

	args = sh->pipe_lst->cmd;
	i = 1;
	while (args[i])
	{
		unset_var(sh, args[i]);
		i++;
	}
	if (sh->env)
		sh->env = arr_clean(sh->env, 0);
	sh->env = env_converter(sh->env_lst);
	if (!sh->env)
		return (err_break(sh, "malloc", NULL, 12));
	return (0);
}