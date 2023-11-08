/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:41:40 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/07 17:41:43 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	pipe_init(t_pipe *pip)
{
	pip->cmd = NULL;
	pip->paths = NULL;
	pip->fd_lst = NULL;
	pip->in_fd = -2;
	pip->out_fd = -2;
	pip->vars = NULL;
}

void	pipe_add(t_pipe **lst, t_pipe *new)
{
	t_pipe	*temp;

	if (!*lst)
		*lst = new;
	temp = *lst;
	while (temp -> next)
		temp = temp -> next;
	temp -> next = new;
}