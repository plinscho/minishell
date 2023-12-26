/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:01:32 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/26 15:40:37 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_builtin(char **cmd)
{
	
	if (!cmd || !(*cmd))
		return (0);
//	printf("\n[CHECK BUILT] CMD: %s\n", cmd[0]); //erase
	if (!ft_strncmp(cmd[0], "echo", ft_longer(cmd[0], "echo")))
		return (1);
	if (!ft_strncmp(cmd[0], "cd", ft_longer(cmd[0], "cd")))
		return (2);
	if (!ft_strncmp(cmd[0], "pwd", ft_longer(cmd[0], "pwd")))
		return (3);
	if (!ft_strncmp(cmd[0], "export", ft_longer(cmd[0], "export")))
		return (4);
	if (!ft_strncmp(cmd[0], "unset", ft_longer(cmd[0], "unset")))
		return (5);
	if (!ft_strncmp(cmd[0], "env", ft_longer(cmd[0], "env")))
		return (6);
	if (!ft_strncmp(cmd[0], "exit", ft_longer(cmd[0], "exit")))
		return (7);
	return (0);
}

/*
prev = -1
*/
void	ft_open(t_mini *sh, t_pipe *p, t_fd *fd1, int prev)
{
	while (fd1)
	{
	//	printf("[OPEN] PIPE %p -- filename before open: %s, fd: %i, exp flag: %i\n", p->cmd, fd1->str, fd1->fd, fd1->exp); //erase
	//	printf("[OPEN] PIPE %s -- before open: in: %i, out: %i\n", p->cmd[0], p->in_fd, p->out_fd); //erase
		ft_check_open(p, fd1, prev);
		if (fd1->exp == 1)
			err_exit(sh, fd1->str, "ambiguous redirect", 1);
		if (fd1->type == 6 || fd1->type == 9)
			p->in_fd = fd1->fd;
		else if (!fd1->str || *fd1->str == '\0')
			err_exit(sh, "", "No such file or directory", 1);
		else if (fd1->type == 4)
			p->in_fd = open(fd1->str, O_RDONLY);
		else if (fd1->type == 5)
			p->out_fd = open(fd1->str, O_TRUNC | O_CREAT | O_RDWR, 0666);
		else if (fd1->type == 7)
			p->out_fd = open(fd1->str, O_APPEND | O_CREAT | O_RDWR, 0666);
		if (p->in_fd < 0 && (fd1->type == 6 || fd1->type == 9 || fd1->type == 4))
			err_exit(sh, fd1->str, NULL, 1);
		if (p->out_fd < 0 && (fd1->type == 5 || fd1->type == 7))
			err_exit(sh, fd1->str, NULL, 1);
	//	printf("[OPEN] PIPE %s -- fd after open in: %i, out: %i\n", p->cmd[0], p->in_fd, p->out_fd); //erase
		prev = fd1->type;
		fd1 = fd1->next;
	}
}

void	ft_check_open(t_pipe *p, t_fd *cur, int prev)
{
	if (p->in_fd >= 0 && (cur->type == 6 || cur->type == 9 || cur->type == 4)\
	 && prev != 6)
	{
		close(p->in_fd);
		p->in_fd = -2;
	}
	if (p->out_fd >= 0 && (cur->type == 5 || cur->type == 7))
	{
	//	printf("[OPEN] PIPE %s -- closing out before open: %s, fd: %i\n", p->cmd[0], fd1->str, fd1->fd);
		close(p->out_fd);
		p->out_fd = -2;
	}
}

void	check_access(t_mini *sh, char **cmd, t_pipe *p)
{
	if (!cmd || !(*cmd))
		err_exit(sh, NULL, NULL, 0);
	else if (!(**cmd))
		err_exit(sh, *cmd, "command not found", 127);
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) == 0)
		{
			if (access(cmd[0], X_OK) != 0)
				err_exit(sh, cmd[0], "permission denied", 126);
			p->path = cmd[0];
		}
		else
			err_exit(sh, cmd[0], "No such file or directory", 127);
	}
	else
		check_paths(sh->paths, cmd[0], sh, p);
}

void	check_paths(char **paths, char *cmd, t_mini *sh, t_pipe *pipe)
{
	int		i;

	i = 0;
	if (!paths)
		err_exit(sh, cmd, "No such file or directory", 127);
	while (paths[i])
	{
	//	printf("\n[CHECK PATHS] i: %i, path: %s\n", i, paths[i]); //erase
		pipe->path = ft_smart_join(paths[i], "/", cmd);
	//	printf("\n[CHECK PATHS] p: %s\n", pipe->path); //erase
		if (!pipe->path)
			err_exit(sh, "malloc", NULL, 12);
		if (access(pipe->path, F_OK) == 0)
		{
			if (access(pipe->path, X_OK) != 0)
				err_exit(sh, cmd, "permission denied", 126);
			else
				return ;
		}
	//	printf("\n[CHECK PATHS] p before delete: %p, str: %s\n", pipe->path, pipe->path); //erase
		pipe->path = ft_memdel(pipe->path);
	//	printf("\n[CHECK PATHS] p after delete: %p\n", pipe->path); //erase
		i++;
	}
	err_exit(sh, cmd, "command not found", 127);
}