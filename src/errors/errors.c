/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:19:22 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/15 16:53:32 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	synt_error(t_mini *sh)
{
	ft_putstr_fd("minishell: Syntax error : Quotes not closed.\n", STDERR_FILENO);
	sh->exit = 127;
	return ;
}