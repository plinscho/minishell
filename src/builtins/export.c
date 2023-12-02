/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:52:26 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/02 15:27:30 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#define ERR_MLC	-2
#define ERR_KEY	-1
#define	NOTHING	0
#define UPDATE	1
#define ADD		2

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

	tmp = head;
	new = envnode_new(var);
	if (!new)
		return (1);
	tmp = ft_envlast(tmp);
	tmp->next = new;
	printf("Last node: %s\n", tmp->env_key);
//	print_export(head);
	return (0);
}

// This var has value and its in env
int		env_update(t_mini *sh, char *var, t_env *head)
{
	t_env	*tmp;
	char	*new_val;
	char	*new_key;

	new_key = get_key(var, NULL);
	if (!new_key)
		return (ERR_KEY);
	tmp = ft_getkey_node(new_key, head);
	if (!tmp)
		return (ERR_MLC);
	new_val = ft_get_value(sh, new_key);
	if (!new_val)
		return (ERR_MLC);
	make_env_full(tmp, new_key, new_val, var);
	return (0);
}

int		split_var(char *export, t_env *head)
{
	int		in_env;
	int		hasval;
	char	*new_key;

	hasval = 0;
	new_key = get_key(export, &hasval);
	if (!new_key)
		return (ERR_KEY);
	in_env = key_in_env(new_key, head);
	// If it exists and has value. Will be shown in char **env
	if (hasval && in_env)
		return (UPDATE);
	else if (!in_env)
		return (ADD);
	else
		return (NOTHING);
}

int		ft_export(t_mini *sh)
{
	t_env	*tmp_env;
	char	**t_cmd;
	int		option;
	int		err;
	int		i;
	
	tmp_env = sh->env_lst;
	t_cmd = sh->pipe_lst->cmd;
	if (!t_cmd || !tmp_env)
		return (1);
	err = 0;
	i = 0;
	if (!t_cmd[1])
		return (print_export(tmp_env));
	while (t_cmd[++i] != NULL)
	{
		option = split_var(t_cmd[i], tmp_env);
		if (option == ERR_KEY)
			return (ERR_KEY);
		else if (option == UPDATE)
			err = env_update(sh, t_cmd[i], tmp_env);
		else if (option == ADD)
			err = env_add(t_cmd[i], tmp_env);
		if (err)
			return (err);
	}
	return (env_converter(sh));
}