/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:50:22 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/08 14:09:19 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_parser(t_pipe *p)
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

void	print_lexer(t_mini *sh)
{
	t_lexer	*lex_list = NULL;
	int	i;

	i = 1;
	lex_list = sh->lex_lst;
	while (lex_list)
    {
		printf("node %i -- content: %s, type; %i\n", i, lex_list->cont, lex_list->token); //erase
	 	i++;
      	lex_list = lex_list->next; 
   	}
}

void	print_lex_node(t_lexer *lex_list)
{
	int	i;

	i = 1;
	while (lex_list)
    {
		printf("node %i -- content: %s, type; %i\n", i, lex_list->cont, lex_list->token); //erase
	 	i++;
      	lex_list = lex_list->next; 
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