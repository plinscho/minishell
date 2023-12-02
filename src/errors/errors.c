/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:19:22 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/02 19:30:26 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		quotes_error(t_mini *sh)
{
	ft_putstr_fd("minishell: Syntax error : Quotes not closed.\n", STDERR_FILENO);
	sh->exit = 127;
	return (sh->exit);
}

void	syntax_error(t_mini *sh, char *seq)
{
	(void)sh;
	printf("minishell: syntax error near unexpected token '%s'\n", seq);
	return ;
}

void	error_option(char *str1, char *str2)
{
	ft_putstr_fd("Export ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd("=", 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}