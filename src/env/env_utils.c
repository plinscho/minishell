/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:29:44 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/02 11:57:53 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// option 1 == All variables
// option 2 == Only variables with value ('=')
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
		while (tmp)
		{
			if (has_equal_sign(tmp->env_full))
				env_cases++;
			tmp = tmp->next;
		}
		return (env_cases);	
	}
	else
		return (0);
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
			printf("Node[%d] | %s\n", i, tmp->env_full);
			printf("key: %s\nVal: %s\n\n", tmp->env_key, tmp->env_val);
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