/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:01:59 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/27 16:06:20 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		pre_quotes(char *line)
{
	int	i;
	int	open;

	i = 0;
	open = 0;

	while (line[i])
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
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

void	print_parser(t_mini *sh)
{
	t_pipe	*tmp = NULL;
	int	i;

	tmp = sh->pipe_lst;
	i = 0;
	while (tmp)
   	{
		printf("pipe %i -- cmd: %p, fd: %p\n", i, tmp->cmd, tmp->fd_lst);
	 	i++;
       	tmp = tmp->next; 
    }
}