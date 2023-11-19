/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:01:15 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/19 16:31:16 by nzhuzhle         ###   ########.fr       */
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
		temp = (*lst) -> next;
		if ((*lst) -> cont)
		{
			free((*lst) -> cont);
			(*lst) -> cont = NULL;
		}
		free(*lst);
		*lst = NULL;
		*lst = temp;
	}
	*lst = NULL;
	return (1);
}

/*
This function allocates a new lex node, fills it with the given content and a type of token.
*/
t_lexer	*lex_new(char *content, int token)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node -> cont = content;
	new_node -> token = token;
	new_node -> prev = NULL;
	new_node -> next = NULL;
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
		new -> prev = NULL;
		return ;
	}
	temp = *lst;
	while (temp -> next)
		temp = temp -> next;
	new -> prev = temp;
	temp -> next = new;
}

int	trim_quotes(t_mini *sh, t_lexer *temp)
{
	while (temp)
	{
		if (temp->token == 1)
		{
			temp->cont = word_no_q(temp, 0);
			if (!temp->cont)
				return (sh_clean(sh, 2));
		}
		temp = temp->next;
	}
	return (0);
}

char	*word_no_q(t_lexer *lex, int j)
{
	char	*cont;
	char	q;

	while (lex->cont[j] && lex->cont[j] != '\'' && lex->cont[j] != '\"')
		j++;
	if (lex->cont[j] && (lex->cont[j] == '\'' || lex->cont[j] == '\"'))
	{
		q = lex->cont[j];
		j++;
		while (lex->cont[j] && lex->cont[j] != q)
			j++;
		while (lex->cont[j])
			j++;
		cont = ft_substr_quotes(lex->cont, q, j, -1);
	}
	else
		return (lex->cont);
	if (!cont)
		return (NULL);
	free(lex->cont);
	lex->cont = NULL;
	return (cont);
}