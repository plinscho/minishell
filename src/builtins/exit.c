/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:42:48 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/28 17:09:01 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>

long long int	ft_atol_sh(char *str);
int				p_exit_err(char *str_error, int option);

long long int	ft_atol_sh(char *str)
{
	int			i;
	int			sign;
	long long	number;

	sign = 1;
	i = 0;
	number = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (number > INT_MAX || number < INT_MIN)
			return (p_exit_err(str, 1));
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return ((number *= sign));
}

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
	return (ft_atol_sh(s));
}

int	ft_exit(t_mini *sh)
{
	char	*input;
	int		ex;

	if (sh->input == NULL || ft_strcmp(sh->input, "exit") == 0)
	{
		sh->power_on = 0;
		printf("chao\n");
		return (sh->exit);
	}
	else
	{
		ex = 255;
		if (arg_count(sh->pipe_lst->cmd) > 2)
			return (p_exit_err("minishell: exit: too many arguments\n", 2));
		sh->power_on = 0;
		input = sh->pipe_lst->cmd[1];
		printf("chao\n");
		if (input[0] == '\0')
			p_exit_err(input, 1);
		else
			ex = check_exit(input);
	}
	return (ex);
}
