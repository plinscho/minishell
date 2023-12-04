/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:29:44 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/04 16:23:21 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*


int		env_add(char *var, t_env *head)
{
	t_env	*tmp;
	t_env	*new;

	tmp = head;
	new = envnode_new(var);
	if (!new)
		return (1);
	tmp = ft_envlast(tmp);
	tmp->next = new;
	return (0);
}

*/

int		env_val_update(t_env *head, char *key, char *n_value)
{
	t_env	*tmp;
	size_t	len;
	
	tmp = head;
	len = ft_strlen(key);
	while (tmp != NULL)
	{
		// Found an old env key
		if (ft_strncmp(tmp->env_key, key, len) == 0 \
			&& len == ft_strlen(tmp->env_key))
		{
			tmp->env_val = ft_strdup(n_value);
			if (!tmp->env_val)
				return (1);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	print_env(t_env *head, char **env)
{
	t_env	*tmp;
	int		i;

	tmp = head;
	i = 0;
	if (tmp)
	{
		while (tmp)
		{
			printf("Node[%d]\nkey: %s\nVal: %s\n\n", i, tmp->env_key, tmp->env_val);
			tmp = tmp->next;
			i++;
		}
	}
	if (env)
	{
		i = 0;
		while(env[i])
		{
			ft_printf("char_env[%d]: %s\n", i, env[i]);
			i++;
		}
	}
	ft_printf("\n");
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