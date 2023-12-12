/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:41:54 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/12 17:26:54 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	CASES:

	bash-3.2$ echo -n howdy
	howdybash-3.2$

	bash-3.2$ echo -nnnnnnnnnn howdy -n
	howdy -nbash-3.2$

	bash-3.2$ echo -n -n -n -n howdy -n -nnnnnnnnn
	howdy -n -nnnnnnnnnbash-3.2$
*/

int		num_args(char **args)
{
	int	i;
	
	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

int		ft_echo(t_mini *sh, t_pipe *p)
{
	char	**cmd;
	int		i;
	int		has_n;
	
	(void)p;
	i = 1;
	has_n = 0;
	cmd = sh->pipe_lst->cmd;
	if (num_args(cmd) > 1)
	{
		while (cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
		{
			has_n = 1;
			i++;
		}
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1] && cmd[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (has_n == 0)
		write(1, "\n", 1);
	return (0);
}