/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:01:15 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/10 00:42:42 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	lex_clean(t_lexer **lst)
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

char	*ft_substr_quotes(char *s, char q, int len, int i)
{
	char	*m;
	int		new_len;
//	int		start;

	new_len = len;
//	start = 0;
	while (++i < (len - 1) && s[i + 1])
	{
		if (s[i] == q)
			new_len--;
	}
	i = 0;
	m = (char *) malloc(new_len + 1);
	if (m == 0)
		return (NULL);
	while (i < new_len && s[i])
	{
		if (s[i] == q)
			s++;
		else
		{
			m[i] = s[i];
			i++;
		}
	}
	m[i] = '\0';
	return (m);
}

int	check_chr(char c)
{
	if ((c > 32 && c < 60) || c == '=' || (c > 62 && c < 124) || \
	(c > 124 && c < 127))
		return (1);
	return (0);
}