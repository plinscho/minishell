/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:41:54 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/14 17:43:19 by plinscho         ###   ########.fr       */
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

int		check_flag(char *str)
{
	if (ft_strcmp(str, "-n") == 0)
		return (0);
	return (1);
}


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
	int		output;
	(void)sh;
	
	i = 1;
	has_n = 0;
	cmd = p->cmd;
	output = p->out_fd;
	if (output < 0)
		output = 1;
    if (num_args(cmd) > 1)
    {
        while (cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
        {
            has_n = 1;
            i++;
        }
		while (cmd[i])
        {
            ft_putendl_fd(cmd[i], output);
            if (cmd[i + 1] && cmd[i][0] != '\0')
                write(1, " ", output);
            i++;
        }
    }
    if (!has_n && output == 1)
        write(1, "\n", output);
    return (0);
}

