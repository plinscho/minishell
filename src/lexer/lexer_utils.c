/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:01:15 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/29 18:21:24 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
This function cleans the lex list.
*/
int	lex_clean(t_lexer **lst)
{
	t_lexer	*temp;

//	printf
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

/*int	trim_quotes(t_mini *sh, t_lexer *temp, int j)
{
	char *in;

	while (temp)
	{
		if (temp->token == 1)
		{
			in = temp->cont;
			while (in[j] && in[j + 1] && in[j + 1] != ' ' && in[j + 1] != '\'' && \
			in[j + 1] != '\"' && check_chr(in[j + 1]))
				j++;
			while (in[j] && in[j + 1] && (in[j + 1] == '\'' || in[j + 1] == '\"'))
				j += word_in_quotes(in, " ", j);
			temp->cont = ft_substr(in, 0, j + 1);
			in = ft_memdel(in);
			if (!temp->cont)
				return (sh_clean(sh, 2));
		}
		temp = temp->next;
	}
	return (0);
}*/

int	trim_quotes(t_mini *sh, t_lexer *temp)
{
	while (temp)
	{
		if (temp->token == 1)
		{
			temp->cont = word_no_q(temp->cont, '\'');
			if (!temp->cont)
				return (err_break(sh, "malloc", "Cannot allocate memory", 12));
			temp->cont = word_no_q(temp->cont, '\"');
			if (!temp->cont)
				return (err_break(sh, "malloc", "Cannot allocate memory", 12));
		}
		temp = temp->next;
	}
	return (0);
}

char	*word_no_q(char *in, char q)
{
	char	*cont;

	if (ft_strchr(in, q))
		cont = ft_substr_quotes(in, q, ft_strlen(in), -1);
	else
		return (in);
	in = ft_memdel(in);
	if (!cont)
		return (NULL);
	return (cont);
}

int	word_in_quotes(char *in, char *q, int j)
{
	*q = in[++j];
	j++;
	while (in[j] && in[j + 1] != *q)
		j++;
	while (in[j] && in[j + 1] && in[j + 1] != ' ' && in[j + 1] == '\'' && in[j + 1] == '\"')
		j++;
	return (j);
}