/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:39:34 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/26 19:41:00 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_mini *sh, t_pipe *p)
{
	char	*pwd;
	int		output;

	output = p->out_fd;
	if (output < 0)
		output = 1;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		ft_putstr_fd(ft_get_value(sh, "PWD"), output);
	}
	ft_putstr_fd(pwd, output);
	ft_putstr_fd("\n", output);
	free(pwd);
	return (0);
}
