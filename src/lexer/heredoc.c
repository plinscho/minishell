/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:34:20 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/27 21:20:59 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
This function checks if there is a << heredoc sign in the string,
if finds one - creates an fd node, adds it to the list, 
parses the keyword, then calls a functin that will fill the node.
*/
int	ft_heredoc(t_mini *sh, char *in, int i)
{
	t_fd	*new;

	if (!ft_strnstr(in, "<<", ft_strlen(in)))
		return (0);
	while (in[i])
	{
		i = find_hd(in, 0);
		if (i <= 0)
			return (0);
		in = in + i;
		new = malloc(sizeof(t_fd));
		if (!new)
			return (err_break(sh, "heredoc", NULL, 12));
		new->next = NULL;
		new->type = 6;
		fd_add(&(sh->hd_lst), new);
		new->str = keyword_hd(new, in, &i, ' ');
		if (!new->str)
			return (err_break(sh, "heredoc", NULL, 12));
		new->fd = save_hd(sh, new->str, NULL, new->type);
		if (new->fd < 0)
			return (err_break(sh, "heredoc", NULL, -(new->fd)));
		i = 0;
	}
	return (0);
}

/*
This function looks for the valid << sign in a string:
not <, 
not <<< or more, 
not before the | or >, 
not in the end of the string.
*/
int	find_hd(char *in, int i)
{
	while (in[i])
	{
		while (in[i] && in[i] != '<')
			i++;
		if (!in[i] || !in[i + 1] || !in[i + 2])
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

/* 
This function parses and saves the keyword of the heredoc:
all the valid characters that are not space, < OR > OR |,
trims the quotes if finds them, 
if any ' quotes are found changes the type of the node to 9 - 
for the expanser.
*/
char	*keyword_hd(t_fd *new, char *in, int *i, char q)
{
	char	*cont;
	int		j;

	j = 0;
	while (in[j] && in[j + 1] && check_chr(in[0]) != 2
		&& check_chr(in[j + 1]) != 2 && check_chr(in[j + 1]))
		j++;
	if (check_chr(in[0]) == 2)
		j = word_in_quotes(in, &q, -1);
	while (in[j] && in[j + 1] && check_chr(in[j + 1]) == 2)
		j = word_in_quotes(in, &q, j);
	cont = ft_substr(in, 0, j + 1);
	if (cont)
		cont = trim_quotes(cont, ' ', ft_strlen(cont), -1);
	if (!cont)
		return (NULL);
	if (q == '\'' || q == '\"')
		new->type = 9;
	*i += j;
	return (cont);
}

/* 
This function creates a pipe to save the heredoc content in it.
The pipe is used as a buffer with a file descriptor to read from. 
Then it opens a readline, we can fill it from standart input.
It compares each line with the key word and if it's not the keyword 
it saves the line in the buffer. 
1. return (-1) - if pipe() error occures
2. return (fd) - a file descriptor to read the content of the heredoc
*/
int	save_hd(t_mini *sh, char *key, char *str, int type)
{
	int	hd[2];

	if (pipe(hd) < -1)
		return (-1);
	while (42)
	{
		str = readline("> ");
		if (!str)
			return (hd_close(hd, 0));
		else if (!ft_strncmp(str, key, ft_longer(str, key)) && \
				(ft_strncmp(str, "\n", 1)))
			break ;
		else if (!ft_strncmp(str, "\n", 1) && (*key == '\0'))
			break ;
		str = expand_hd(sh, str, type);
		if (!str)
			return (hd_close(hd, 1));
		write(hd[1], str, ft_strlen(str));
		write(hd[1], "\n", 1);
		str = ft_memdel(str);
	}
	str = ft_memdel(str);
	close(hd[1]);
	return (hd[0]);
}

int	hd_close(int fd[], int flag)
{
	close(fd[1]);
	if (flag)
	{
		close(fd[0]);
		return (-12);
	}
	return (fd[0]);
}
