/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:01:15 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/02 18:54:12 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_clean(t_lexer **lst)
{
	t_lexer	*temp;

	if (!lst)
		return (EXIT_FAILURE);
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

void	print_lexer(t_lexer *lex_list)
{
	int i = 0;
	while (lex_list)
    	{
			printf("node %i -- content: %s, type; %i\n", i, lex_list->cont, lex_list->token); //erase
       	 	i++;
        	lex_list = lex_list->next; 
    	}
}