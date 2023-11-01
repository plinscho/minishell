/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:01:15 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/10/25 19:01:37 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lex_clean(t_lexer **lst, char **in)
{
	t_lexer	*temp;

	while (*lst)
	{
		temp = (*lst) -> next;
		if ((*lst) -> cont)
			free((*lst) -> cont);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	if (*in)
		free(*in);
	*in = NULL;
	return (1);
}

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

char	*ft_substr_quotes(char *s, int start, int len, int i)
{
	char	*m;
	int		new_len;

	new_len = len;
	while (++i < (len - 1) && s[i + start + 1])
	{
		if (s[i + start] == '\'' || s[i + start] == '\"')
			new_len--;
	}
	i = 0;
	m = (char *) malloc(new_len + 1);
	if (m == 0)
		return (NULL);
	while (i < new_len && s[i + start])
	{
		if (s[i + start] == '\'' || s[i + start] == '\"')
			start++;
		else
		{
			m[i] = s[start + i];
			i++;
		}
	}
	m[i] = '\0';
	return (m);
}