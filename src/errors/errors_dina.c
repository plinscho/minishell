/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_dina.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:01:35 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/20 18:12:33 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"
#include "../../include/minishell.h"

/* It is a first sketch. We need to change all the structure now of exiting the 
loop and cleaning the struct */
int	ft_exit_exe(t_mini *sh, char *str1, char *str2, int err)
{
	printf("minishell: %s: %s\n", str1, str2);
	sh->exe.exit_stat = err;
	sh_clean(sh, err);
	return (1);
}