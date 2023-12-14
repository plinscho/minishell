/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:42:48 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/14 20:30:57 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>

// exit is also a tricky function. Can be used almost everywhere and with and saves the $? error.
// Im also saving it for the last so that can work with the rest of the code when debugged.

int		print_exit_err(char *str_error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str_error, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (-1);
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
			return (print_exit_err(str));
	}
	return (ft_atoi(str));
}

int		ft_exit(t_mini *sh)
{
	char	*input;
	int		ex;
	
	if (sh->input == NULL)
	{
		sh->power_on = 0;
		return (sh->exit);
	}
	else
	{	
		input = sh->pipe_lst->cmd[1];
		if (!input)
			return (1);
		ex = check_exit(input);
	}
	if (ex != -1)
		sh->power_on = 0;
	return (ex);
}