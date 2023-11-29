/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:34:20 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/29 17:19:57 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
This function checks if there is a << heredoc sign in the string,
if finds one - creates an fd node, adds it to the list, 
parses the keyword, then calls a functin that will fill the node.
*/
int	ft_heredoc(t_mini *sh, char *in)
{
	int		i;
	t_fd	*new;

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
		new = malloc(sizeof(t_fd));
		if (!new)
			return (err_break(sh, "heredoc", "Memory allocation failed", EXIT_FAILURE));
		new->next = NULL;
		new->type = 6;
		fd_add(&(sh->hd_lst), new);
		new->str = keyword_hd(new, in, &i);
		if (!new->str)
			return (sh_clean(sh, 2));
		new->fd = save_hd(new->str, NULL);
		if (new->fd < 0)
			return (sh_clean(sh, -(new->fd)));
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

/* 
This function parses and saves the keyword of the heredoc:
all the valid characters that are not space, < OR > OR |,
trims the quotes if finds them, 
if any ' quotes are found changes the type of the node to 9 - for the expanser.
*/
char	*keyword_hd(t_fd *new, char *in, int *i)
{
	char	*cont;
	int		j;
	char	q;

	j = 0;
	while (in[j] && in[j] != ' ' && in[j] != '\'' && in[j] != '\"' \
	&& check_chr(in[j]))
		j++;
	printf("[HEREDOC] in keyword: stop letter: %c\n", in[j]); //erase
	if (in[j] && (in[j] == '\'' || in[j] == '\"'))
	{
		q = in[j];
		j++;
		while (in[j] && in[j] != q)
			j++;
		while (in[j] && in[j + 1] && in[j + 1] != ' ')
			j++;
		printf("[HEREDOC] before substr: %s$\n", in + j); //erase
		cont = ft_substr_quotes(in, q, j, -1);
	}
	else
		cont = ft_substr(in, 0, j);
	printf("[HEREDOC] final keyword: %s$\n", cont); //erase
	if (!cont)
		return (NULL);
	if (q == '\'' || q =='\"')
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
		write(hd[1], "\n", 1);
		free(str);
		str = NULL;
	}
	if (str)
		free(str);
	str = NULL;
	close(hd[1]);
	return (hd[0]);
}