/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:50:22 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/21 20:52:49 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_parser_dina(t_pipe *p)
{
	t_fd *f;
	int	i;
	int j = 0;

	while (p)
   	{
		printf("PIPE %i:\n", j);
		f = p->fd_lst;
		i = 0;
		while (p->cmd && p->cmd[i])
		{
			printf("cmd[%i]: %s\n", i, p->cmd[i]);
			i++;
		}
		i = 0;
		while (f)
		{
			printf("fd %i: %i, type %i, file - %s\n", i, f->fd, f->type, f->str);
			i++;
			f = f->next;
		}
		j++;
       	p = p->next; 
    }
}

void	print_arr(char **arr)
{
	int	i = -1;

	if (!arr || !*arr)
		printf("no array: %p\n", arr);
	while (arr[++i])
		printf("array %i: %s\n", i, arr[i]);
}