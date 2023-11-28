/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:41:20 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/28 18:43:59 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//#include <unistd.h>

/*
	This builtin needs 2 thing, the OLDPWD and the actual PWD from
	env. 
*/

// int		env_add_update(t_mini *sh, char *key, char *n_value)


int		go_to_path(int option, t_mini *sh)
{
	t_env	*env = NULL;
	int		ret;
	char	*env_path;

	env = sh->env_lst;
	if (!env)
		return (1);
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
//		update_oldpwd(env);
	}
	env = sh->env_lst;
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

int		ft_cd(t_mini *sh)
{
	char	**cmd_tmp;
	char	*pwd;
	
	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	cmd_tmp = sh->pipe_lst->cmd; // Store the command
	if (!(pwd || cmd_tmp))
		return (1);
	// cd a secas te lleva a HOME
	if (cmd_tmp[1] == NULL)
		return (go_to_path(0, sh));
	else if (ft_strcmp(cmd_tmp[1], "-") == 0)
		return (go_to_path(1, sh));
	// cd - te lleva al OLDPWD

	// si hay mas de 1 argumento:
		// bash: cd: demasiados argumentos

	pwd = ft_memdel(pwd);
	return (1);
}