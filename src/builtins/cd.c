/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:41:20 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/25 21:33:14 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//#include <unistd.h>

/*
	This builtin needs 2 thing, the OLDPWD and the actual PWD from
	env. 
*/

void	cd_home(t_mini *sh, char **cmd)
{
	return ;
}

int		ft_cd(t_mini *sh)
{
	char	**cmd_tmp;
	char	*pwd;
	
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	cmd_tmp = sh->pipe_lst->cmd; // Store the command
	if (!(pwd || cmd_tmp))
		return (1);
	
	// cd a secas te lleva a HOME
	if (cmd_tmp[1] == NULL)
		cd_home(sh, cmd_tmp);
	// cd - te lleva al OLDPWD

	// si hay mas de 1 argumento:
		// bash: cd: demasiados argumentos

	pwd = ft_memdel(pwd);
	return (1);
}