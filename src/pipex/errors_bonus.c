/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:37:01 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/27 16:28:43 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_error(char *message, int flag, t_pipe *info)
{
	if (info)
		clean_up(info);
	write(2, "pipex: ", 7);
	if (flag == 0)
		perror(message);
	else
	{
		write(2, message, ft_strlen(message));
		exit(flag);
	}
	if (errno == 13)
		exit (1);
	exit (errno);
}

void	clean_up(t_pipe *info)
{
	if (info && info -> paths)
		ft_free(info -> paths, -1);
	if (info && info -> str_doc)
		free(info -> str_doc);
	free(info);
	info = NULL;
}

void	ft_free(char **arr, int n)
{
	while (n > 0)
		free(arr[n--]);
	if (n == 0)
		free(arr[n]);
	if (n < 0)
	{
		while (arr[++n])
			free(arr[n]);
	}
	free(arr);
	arr = NULL;
}

void	check_access(t_pipe *info, char **cmd, char **path)
{
	ft_putstr_fd("entered check access: ", 2); //erase
	ft_putstr_fd(cmd[0], 2); //erase
	ft_putstr_fd("\n", 2); //erase
	if (ft_strchr(cmd[0], '/'))
	{
		ft_putstr_fd("found / \n", 2); //erase
		if (access(cmd[0], F_OK) == 0)
		{
			if (access(cmd[0], X_OK) != 0)
				print_error(ft_strjoin(cmd[0], ": Permission denied"), \
						126, info);
			*path = ft_strdup(cmd[0]);
		}
		else
			print_error(ft_strjoin(cmd[0], ": command not found\n"), 127, info);
	}
	else
	{
		ft_putstr_fd("entered else\n", 2); //erase
		*path = ft_strdup(check_paths(info->paths, cmd[0], info));
	}
	ft_putstr_fd("check access, path: ", 2); //erase
	ft_putstr_fd(*path, 2); //erase
	ft_putstr_fd("\n", 2); //erase
}

char	*check_paths(char **paths, char *cmd, t_pipe *info)
{
	char	*p;
	int		i;

	i = -1;
	ft_putstr_fd("entered check paths: ", 2); //erase
	ft_putstr_fd(cmd, 2); //erase
	ft_putstr_fd("\n", 2); //erase
	while (paths[++i])
	{
		p = ft_strjoin(paths[i], cmd);
		if (!p)
		{
			ft_free(paths, -1);
			print_error("malloc", 0, info);
		}
		if (access(p, F_OK) == 0)
		{
			if (access(p, X_OK) != 0)
				print_error(ft_strjoin(cmd, ": Permission denied"), 126, info);
			else
				return (p);
		}
	}
	print_error(ft_strjoin(cmd, ": command not found\n"), 127, info);
	return (NULL);
}
