/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:03:17 by plinscho          #+#    #+#             */
/*   Updated: 2023/10/27 21:01:20 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	env_variables(char **og_env)
{
	size_t	env_cases;
	
	env_cases = 0;
	while (og_env[env_cases])
		env_cases++;
	return (env_cases);	
}


void	populate_env(char **env_cpy, char **og_env)
{
	unsigned int	i;

	i = 0;
	while (og_env[i])
	{
		env_cpy[i] = ft_strdup(og_env[i]);
//		ft_printf("og: %s\ncp: %s\n\n", og_env[i], env_cpy[i]);
		i++;
	}
	env_cpy[i] = NULL;
}

//	This function gets the original adress of the env variables
//	and makes a copy of them in the env_cpy variable, which is then
//	returned.
char	**cpy_env(char **og_env)
{
	char **env_cpy = NULL;
	
	env_cpy = (char **)malloc(sizeof(char *) * env_variables(og_env) + 1);
	populate_env(env_cpy, og_env);
	return (env_cpy);
}

//	This function emulates the behaviour of getenv(), however
//	we need the path to all our env variables.
//	1. The function takes the lenght of the variable name 
//	2. Iteration untill we find the match between the var_name in the grid
//	3. First condition (== '=') is to skip the firsts matches and find only 
//		the desired word. It will take the first match and there are 
//		names that are the same, taking the first match.
char	*ft_getenv(char *var, char **env)
{
	unsigned int	i;
	size_t			len;
	char			*env_name = NULL;

	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if ((env[i][len] == '=') && (ft_strncmp(var, env[i], len) == 0))
		{
			env_name = env[i] + len + 1;
			return (env_name);
		}
		i++;
	}
	return (NULL);
}