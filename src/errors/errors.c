/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:19:22 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/26 21:07:46 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		quotes_error(t_mini *sh)
{
	ft_putstr_fd("minishell: syntax error : quotes not closed\n", 2);
	sh->exit = 127;
	return (sh->exit);
}

/*void	syntax_error(t_mini *sh, char *seq)
{
	(void)sh;
	printf("minishell: syntax error near unexpected token '%s'\n", seq);
	return ;
}*/

int	serror(char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (2);
}