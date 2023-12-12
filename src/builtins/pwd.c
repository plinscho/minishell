/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:39:34 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/12 18:05:03 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_pwd(t_mini *sh, t_pipe *p)
{
	char	*pwd;
	int 	output;
	
	output = p->out_fd;
	if (output < 0 )
		output = 1;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (err_break(sh, "pwd", "PWD not found", 42 ));
	ft_putstr_fd(pwd, output);
	ft_putstr_fd("\n", output);
	free(pwd);
	return (0);
}