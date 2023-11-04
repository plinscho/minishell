/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:03:17 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/01 23:29:38 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	env_variables(char **og_env)
{
	size_t	env_cases;
	int	*p = NULL;
	
	env_cases = 0;
	while (og_env[env_cases])
		env_cases++;
	return (env_cases);	
}


char	*get_key(char *og_env)
{
	unsigned int	i;
	char			*key = NULL;

	i = 0;
	while (og_env[i] != '=')
		i++;
	key = ft_strndup(og_env, i);
	printf("key: %s\n", key);		//Remove printf
	return (key);
}


char	*get_val(char *og_env)
{
	unsigned int	i;
	char			*val = NULL;

	i = 0;
	while (og_env[i] != '=')
		og_env++;
	og_env++;
	val = ft_strdup(og_env);
	printf("val: %s\n", val);		//remove printf
	return (val);
}

//	This function gets the original adress of the env variables
//	and makes a copy of them in the env_cpy variable, which is then
//	returned.
t_env	**env_head(char **og_env)
{
	t_env			**head = NULL;
	t_env			**tmp = NULL;
	unsigned int	i;
			
	head = (t_env **)malloc(sizeof(t_env *) * env_variables(og_env) + 1);
	if (!head)
		return (NULL);			// manage error.
	tmp = head;
	i = 0;
	
//	I might change how its done, because its not a linked list, but an
//	array of nodes. All the "next" are pointing to null.
	while (og_env[i] != NULL);
	{
		head[i] = envnode_new(og_env[i]);
		i++;
	}
	head[i] = NULL;
	head = tmp;
	return (head);
}

int main(void)
{
	printf("Compiles!\n");
	return (0);
}