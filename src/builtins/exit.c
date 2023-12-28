/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:42:48 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/27 21:56:52 by nzhuzhle         ###   ########.fr       */
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

int	check_exit(char *s)
{
	int		i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (!s[i])
		return (p_exit_err(s, 1));
	if ((s[i] == '-' || s[i] == '+') && s[i + 1] && ft_isdigit(s[i + 1]))
		i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i])
		return (p_exit_err(s, 1));
	return (ft_atoi(s));
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
	return (ex);
}
