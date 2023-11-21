/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_dina.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:01:35 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/21 18:07:11 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"
#include "../../include/minishell.h"

/* It is a first sketch. We need to change all the structure now of exiting the 
loop and cleaning the struct */
int	ft_exit_exe(t_mini *sh, char *name, char *message, int err)
{
	if (!name && message)
		printf("minishell: %s\n", message);
	if (name && message)
		printf("minishell: %s: %s\n", name, message);
	sh->exit = err;
	sh_clean(sh);
	exit(err);
}