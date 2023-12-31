/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:01:15 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/21 19:19:21 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
This function cleans the lex list.
*/
int	lex_clean(t_lexer **lst)
{
	t_lexer	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->cont)
		{
			free((*lst)->cont);
			(*lst)->cont = NULL;
		}
		free(*lst);
		*lst = NULL;
		*lst = temp;
	}
	*lst = NULL;
	return (0);
}

/*
This function allocates a new lex node,
fills it with the given content and a type of token.
*/
t_lexer	*lex_new(char *content, int token)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (ft_memdel(content));
	new_node->cont = content;
	new_node->token = token;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

/*
This function adds a new lex node to the end of the lex list.
*/
void	lex_add(t_lexer **lst, t_lexer *new)
{
	t_lexer	*temp;

	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	new->prev = temp;
	temp->next = new;
}

t_lexer	*lex_last(t_lexer *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	lex_insert(t_mini *sh, t_lexer *new, t_lexer **lex, t_lexer *temp)
{
	if (!new)
	{
		sh->lex_lst = temp->next;
		if (temp->prev)
			temp->prev->next = temp->next;
		else
			*lex = temp->next;
		if (temp->next)
			temp->next->prev = temp->prev;
		if (temp->cont)
			temp->cont = ft_memdel(temp->cont);
		temp = ft_memdel(temp);
		return ;
	}
	new->prev = temp->prev;
	sh->lex_lst = lex_last(new);
	lex_last(new)->next = temp->next;
	if (temp->prev)
		temp->prev->next = new;
	else
		*lex = new;
	if (temp->cont)
		temp->cont = ft_memdel(temp->cont);
	temp = ft_memdel(temp);
}
