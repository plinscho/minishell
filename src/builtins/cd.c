/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:41:20 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/28 21:10:16 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <linux/limits.h>
#include <unistd.h>
//#include <unistd.h>

/*
	This builtin needs 2 thing, the OLDPWD and the actual PWD from
	env. 
*/

// int		env_add_update(t_mini *sh, char *key, char *n_value)
void		print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

int		update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (-1);
	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
		return (-1);
	if (is_in_env(env, oldpwd) == 0)
		env_add(oldpwd, env);
	oldpwd = ft_memdel(oldpwd);
	return (0);
}

int		go_to_path(int option, t_env *head, t_mini *sh)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		//env_add_update()
		env_path = ft_get_value(sh, "HOME");
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", 2);
		if (!env_path)
			return (1);
	}
	else if (option == 1)
	{
		env_path = ft_get_value(sh, "OLDPWD");
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
		if (!env_path)
			return (1);
		update_oldpwd(head);
	}
	ret = chdir(env_path);
	env_path = ft_memdel(env_path);
	return (ret);
}

int		ft_cd(t_mini *sh)
{
	char	**args;
	t_env	*env;
	int		cd_ret;

	args = sh->pipe_lst->cmd;
	env = sh->env_lst;
	if (!args[1])
		return (go_to_path(0, env, sh));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, env, sh);
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error(args);
	}
	return (cd_ret);
}