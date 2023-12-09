/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:52:26 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/09 16:40:41 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_plus_equal(t_mini *sh, char *key, char *value)
{
	t_env	*env;
	char	*old_value;
	char	*env_value;

	env_value = find_in_env_variables(sh, key);
	if (!env_value)
	{
		add_or_update_env(sh, key, value);
		return ;
	}
	else
	{
		env = sh->env_lst;
		if (!value)
			value = ft_strdup("");
		while (env != NULL)
		{
			if (ft_strncmp(env->env_key, key, ft_strlen(key)) == 0 \
				&& ft_strlen(env->env_key) == ft_strlen(key))
			{
				old_value = env->env_val;
				env->env_val = ft_strjoin(old_value, value);
				free(old_value);
				return ;
			}
			env = env->next;
		}
	}
/*
	if (sh->env)
		arr_clean(sh->env, 0);
	char	**new_env = env_converter(sh->env_lst);
	if (!new_env)
		return ;
	sh->env = new_env;
*/
}

void	error_option(char *str1, char *str2)
{
	ft_putstr_fd("Export ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd("=", 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);

}

int		handle_args(t_mini *sh, char *arg)
{
    char	**vc;
    char	*key;
    
    vc = ft_split(arg, '=');
    if (!export_option(vc[0]))
        error_option(vc[0], vc[1]);
    else
    {
        if (ft_strchr(vc[0], '+'))
        {
            key = ft_substr(vc[0], 0, ft_strchr(vc[0], '+') - vc[0]);
            if (!key)
                return (1);
            export_plus_equal(sh, key, vc[1]);
            free(key);
        }
        else
        {
            add_or_update_env(sh, vc[0], vc[1]);
        }
    }
	return (0);
}

int		ft_export(t_mini *sh)
{
	t_env	*tmp_env;
	char	**t_cmd;
	int		err;
	int		i;
	
    err = 0;
	tmp_env = sh->env_lst;
	t_cmd = sh->pipe_lst->cmd;
	i = 1;
	if (!t_cmd[1])
		return (print_export(tmp_env));
	while (t_cmd[i] != NULL)
	{
		err = handle_args(sh, t_cmd[i]);
		i++;
	}
	if (sh->env)
		sh->env = arr_clean(sh->env, 0);
	sh->env = env_converter(sh->env_lst);
	if (!sh->env)
		return (err_break(sh, "malloc", NULL, 12));
	return (err);
}
