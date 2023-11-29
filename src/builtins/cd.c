/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:41:20 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/29 19:20:28 by plinscho         ###   ########.fr       */
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
	ft_putstr_fd("minishell: cd: ", 2);
	if (args[2])
		ft_putstr_fd("too many arguments\n", 2);
	else
	{
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	
	}
}

int		update_oldpwd(t_mini *sh)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (-1);
	if (env_add_update(sh, "OLDPWD", cwd))
		return (1);
	return (0);
}

int		go_to_path(int option, t_mini *sh)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(sh);
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
		update_oldpwd(sh);
	}
	ret = chdir(env_path);
	env_path = ft_memdel(env_path);
	return (ret);
}

int		ft_cd(t_mini *sh)
{
	char	**args;
	int		cd_ret;

	args = sh->pipe_lst->cmd;
	if (!args[1])
		return (go_to_path(0, sh));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, sh);
	else
	{
		update_oldpwd(sh);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error(args);
	}
	return (cd_ret);
}