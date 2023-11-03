/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:34:20 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/01 19:34:27 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_here_doc(char *in, t_hd **hd)
{
	int		i;
	t_hd	*new;

	i = 0;
	if (!ft_strnstr(in, "<<", ft_strlen(in)))
		return (0);
	while (in[i])
	{
		i = find_hd(in, 0);
		if (i <= 0)
			return (0);
		in = in + i;
	//	printf("str after <<: %s\n", in); //erase
		new = malloc(sizeof(t_hd));
		if (!new)
			return (free_hd(hd, -2));
		new->next = NULL;
		hd_add(hd, new);
		new->str = keyword_hd(in, &i);
		if (!new->str)
			return (free_hd(hd, -2));
		new->fd = save_hd(new->str, NULL);
		if (new->fd < 0)
			return (free_hd(hd, new->fd));
	}
	return (0);
}

int	find_hd(char *in, int i)
{
	while (in[i])
	{
		while (in[i] && in[i] != '<')
			i++;
		if (!in[i] || !in[i + 1] || !in[i + 2]) // not sure about this condition. do we have \0 or \n in the end?
			return (-1);
		if (in[i + 1] != '<')
		{
			i++;
			continue ;
		}
		else if (in[i + 2] == '<')
			return (-1);
		i += 2;
		while (in[i] && in[i] == ' ')
			i++;
		if (in[i] && check_chr(in[i]))
			break ;
		else
			return (-1);
	}
	return (i);
}

char	*keyword_hd(char *in, int *i)
{
	char	*cont;
	int		j;
	char	q;

	j = 0;
	while (in[j] && in[j] != ' ' && in[j] != '\'' && in[j] != '\"' \
	&& check_chr(in[j]))
		j++;
//	printf("in keyword: stop letter: %c\n", in[j]); //erase
	if (in[j] && (in[j] == '\'' || in[j] == '\"'))
	{
		q = in[j];
		j++;
		while (in[j] && in[j] != q)
			j++;
		while (in[j] && in[j + 1] && in[j + 1] != ' ')
			j++;
		cont = ft_substr_quotes(in, q, j, -1);
	}
	else
		cont = ft_substr(in, 0, j);
	if (!cont)
		return (NULL);
	*i += j;
	return (cont);
}

int	save_hd(char *key, char *str)
{
	int	hd[2];

	if (pipe(hd) < -1)
		return (-1);
//	printf("in save hd: key -  %s\n", key); //erase
//	write(1, key, ft_strlen(key)); //erase
	while (42)
	{
		str = readline("> ");
		if (!str)
			return (-2);
		else if (!ft_strncmp(str, key, ft_longer(str, key)) && \
				(ft_strncmp(str, "\n", 1)))
		{
	//		printf("in 1st cmp: str -  %s\n", str); //erase
			break ;
		}
			
		else if (!ft_strncmp(str, "\n", 1) && (*key == '\0'))
			break ;
	//	write(1, "in heredoc: ", 12); //erase
	//	write(1, str, ft_strlen(str)); //erase
	//	write(1, "\n", 1); //erase
		write(hd[1], str, ft_strlen(str));
		free(str);
		str = NULL;
	}
	if (str)
		free(str);
	str = NULL;
	close(hd[1]);
	return (hd[0]);
}


int	free_hd(t_hd **hd, int err)
{
	t_hd	*temp;
	t_hd	*iter;

	iter = *hd;
	while (iter)
	{
		temp = iter;
		iter = iter->next;
		if (temp->str)
		{
			free(temp->str);
			temp->str = NULL;
		}
		free(temp);
		temp = NULL;
	}
	*hd = NULL;
	return (err);
}