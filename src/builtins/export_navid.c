/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_navid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:26:16 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/02 17:07:16 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*

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

int		env_add(char *var, t_env *head)
{
	t_env	*tmp;
	t_env	*new;

	if (!var)
		return (1);
	tmp = head;
	new = envnode_new(var);
	if (!new)
		return (1);
	tmp = ft_envlast(tmp);
	tmp->next = new;
	return (0);
}

void	add_or_update_env(t_mini *sh, char *name, char *value)
{
	t_env	*env;
	t_env	*new_env;

	env = sh->env_lst;
	while (env != NULL)
	{
		if (ft_strncmp(env->env_key, name, ft_strlen(name)) == 0
			&& ft_strlen(env->env_key) == ft_strlen(name))
		{
			free(env->env_val);
			env->env_val = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	new_env = malloc(sizeof(t_env));
	new_env->env_key = ft_strdup(name);
	new_env->env_val = ft_strdup(value);
	new_env->next = NULL;
	ft_envadd_back(&sh->env_lst, new_env);
}

int		is_valid_identifier(const char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			if ((name[i] == '+' || name[i] == '=') && name[i + 1] != '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

void	export_plus_equal(t_mini *sh, char *name, char *value)
{
	t_env	*env;
	char	*old_value;
	char	*env_value;

	env_value = ft_get_value(sh, name);
	if (!env_value)
	{
		add_or_update_env(sh, name, value);
		return ;
	}
	env = sh->env_lst;
	if (!value)
		value = ft_strdup("");
	while (env != NULL)
	{
		if (ft_strncmp(env->env_key, name, ft_strlen(name)) == 0 \
			&& ft_strlen(env->env_key) == ft_strlen(name))
		{
			old_value = env->env_val;
			env->env_val = ft_strjoin(old_value, value);
			free(old_value);
			return ;
		}
		env = env->next;
	}
}

void	handle_arg(t_mini *sh, char *arg)
{
	char	**v;
	char	*name;

	v = ft_split(arg, '=');
	if (!is_valid_identifier(v[0]))
		print_export_err(v[0], v[1]);
	else
	{
		if (ft_strchr(v[0], '+'))
		{
			name = ft_substr(v[0], 0, ft_strchr(v[0], '+') - v[0]);
			export_plus_equal(sh, name, v[1]);
			free(name);
		}
		else
			add_or_update_env(sh, v[0], v[1]);
	}
	arr_clean(v, 0);
}

int		ft_export(t_mini *sh)
{
	t_env	*tmp;
	char	**args;
	int		i;

	tmp = sh->env_lst;
	args = sh->pipe_lst->cmd;
	i = 1;
	if (args[i] == NULL)
		print_export(tmp);
	else
	{
		while (args[i] != NULL)
		{
			handle_arg(sh, args[i]);
			i++;
		}
	}
	return (0);
}


*/
