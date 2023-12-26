/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:42:48 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/26 15:57:25 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>

int	arg_count(char **grid)
{
	int	i;

	i = 0;
	while (grid[i] != NULL)
		i++;
	return (i);
}

// option 1 == no numeriq req
// option 2 == too many args
int	p_exit_err(char *str_error, int option)
{
	if (option == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str_error, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else
	{
		ft_putstr_fd(str_error, 2);
		return (1);
	}
}

int	check_exit(char *str)
{
	int		i;

	i = 0;
	if ((str[i] == '-' || str[i] == '+') && str[i + 1] && ft_isdigit(str[i + 1]))
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else if (str[i] != '\0')
			return (p_exit_err(str, 1));
	}
	return (ft_atoi(str));
}

int	ft_exit(t_mini *sh)
{
	char	*input;
	int		ex;

	if (sh->input == NULL || ft_strcmp(sh->input, "exit") == 0)
	{
		sh->power_on = 0;
		return (sh->exit);
	}
	else
	{
		ex = 255;
		if (arg_count(sh->pipe_lst->cmd) > 2)
			return (p_exit_err("minishell: exit: too many arguments\n", 2));
		input = sh->pipe_lst->cmd[1];
		if (input[0] == '\0')
			p_exit_err(input, 1);
		else
			ex = check_exit(input);
	}
	if (ex != -1)
		sh->power_on = 0;
	return (ex);
}
