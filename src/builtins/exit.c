/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:42:48 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/19 18:59:25 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>

// exit is also a tricky function. Can be used almost everywhere and with and saves the $? error.
// Im also saving it for the last so that can work with the rest of the code when debugged.

int		arg_count(char ** grid)
{
	int	i;

	i = 0;
	while (grid[i] != NULL)
		i++;
	return (i);
}

// option 1 == no numeriq req
// option 2 == too many args
int		p_exit_err(char *str_error, int option)
{
	if (option == 1)
	{
		ft_putstr_fd("minishell: ", 2);
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

int		check_exit(char *str)
{
	int		i;

	i = 0;
	while (str[i])	
	{
		if (ft_isdigit(str[i]))
			i++;
		else if (str[i] != '\0')
			return (p_exit_err(str, 1));
	}
	return (ft_atoi(str));
}

int		ft_exit(t_mini *sh)
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