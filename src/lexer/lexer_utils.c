/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:01:15 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/09 19:21:15 by nzhuzhle         ###   ########.fr       */
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
	return (0);
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


/*int	trim_quotes(t_mini *sh, t_lexer *temp)
{
	while (temp)
	{
		if (temp->token == 1)
		{
			temp->cont = word_no_q(temp->cont, '\'');
			if (!temp->cont)
				return (err_break(sh, "malloc", NULL, 12));
			temp->cont = word_no_q(temp->cont, '\"');
			if (!temp->cont)
				return (err_break(sh, "malloc", NULL, 12));
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
}*/

int	word_in_quotes(char *in, char *q, int j)
{
	*q = in[++j];
	j++;
	while (in[j] && in[j] != *q)
		j++;
//	if (in[j])
//		j++;
//	printf("[IN QUOTES] IN quotes: input - %s, j -- %i\n", in + j, j); //erase
	while (in[j] && in[j + 1] && in[j + 1] != ' ' && in[j + 1] != '\'' && in[j + 1] != '\"')
		j++;
//	printf("[AFTER QUOTES] IN quotes: input - %s, j -- %i\n", in + j, j); //erase
	return (j);
}

t_lexer	*lex_last(t_lexer *lst)
{
	if (lst)
	{
		while (lst -> next)
			lst = lst -> next;
	}
	return (lst);
}

void	lex_insert(t_mini *sh, t_lexer *new, t_lexer **lex)
{
	t_lexer	*temp;

	temp = sh->lex_lst;
//	printf("[LEX INSERT] BEFORE temp ptr: %p, lst->cont: %s, sh-lst: %p, new: %p\n", temp, temp->cont, sh->lex_lst, new);
	if (!new)
	{
		sh->lex_lst = temp->next;
		if (temp->prev)
			temp->prev->next = temp->next;
		else
			*lex = temp->next;
		if (temp->next)
			temp->next->prev = temp->prev;
	//	printf("[LEX INSERT] BEFORE *lst ptr: %p, sh-lst: %p, new: %p\n", *lst, sh->lex_lst, new);	
	//	sh->lex_lst = temp->next;
	//	printf("[LEX INSERT] BEFORE temp ptr: %p, lst->cont: %s, sh-lst: %p, new: %p\n", temp, temp->cont, sh->lex_lst, new);
		if (temp->cont)
			temp -> cont = ft_memdel(temp -> cont);
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
	if (temp -> cont)
		temp -> cont = ft_memdel(temp -> cont);
	temp = ft_memdel(temp);
//	sh->lex_lst = new;
//	printf("[LEX INSERT] *lst ptr: %p, sh-lst: %p\n", *lst, sh->lex_lst);
//	if (temp -> cont)
//		temp -> cont = ft_memdel(temp -> cont);
//	temp = ft_memdel(temp);
}
/*
i = -1
q = ' '
*/
char		*trim_quotes(char *s, char q, int len, int i)
{
	char	*m;
	int		flag;
	int		j;

	if (!s || !len)
		return (s);
	len = len_no_q(s, q, len, -1);
	m = (char *) malloc(len + 1);
	if (m == 0)
		return (NULL);
	flag = 1;
	j = 0;
	while (++i < len && s[i + j])
	{
		if (check_chr(s[i + j]) == 2 && (flag > 0 || (flag < 0 && s[i + j] == q)))
		{
			q = s[i + j];
			flag *= -1;
			j++;
		}
		m[i] = s[i + j];
	}
	m[i] = '\0';
//	s = ft_memdel(s);
	return (m);
}

int	len_no_q(char *s, char q, int len, int i)
{
	int	flag;
	
	flag = 1;
	while (s[++i])
	{
		if (check_chr(s[i]) == 2 && flag > 0)
		{
			q = s[i];
			flag *= -1;
			len--;
		}
		else if (check_chr(s[i]) == 2 && flag < 0 && s[i] == q)
		{
			flag *= -1;
			len--;
		}
	}
	return (len);
}