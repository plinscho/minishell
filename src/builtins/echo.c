/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:41:54 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/14 19:30:04 by plinscho         ###   ########.fr       */
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
int		parse_nl(char *s)
{
	int	i;

	i = 1;
	if (!(s[0] == '-'))
		return (0);
	while(s[i] && s[i] == 'n')
		i++;
	if (s[i] != '\0')
		return (0);
	return (1);
}

int		check_nl(char *str)
{
	if (!str)
		return (1);
	else if (str[0] == '-' && str[1] == 'n')
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
	cmd = p->cmd;
	has_n = check_nl(cmd[1]);
	output = p->out_fd;
	if (output < 0)
		output = 1;
    if (num_args(cmd) > 1)
    {
        while (cmd[i] && parse_nl(cmd[i]))
			i++;
		while (cmd[i])
        {
            ft_putendl_fd(cmd[i], output);
            if (cmd[i + 1] && cmd[i][0] != '\0')
                ft_putstr_fd(" ", output);
            i++;
        }
    }
    if (has_n)
        ft_putstr_fd("\n", output);
    return (0);
}

