/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:01:32 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/22 18:02:40 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	check_builtin(char **cmd)
{
	if (!cmd || !(*cmd))
		return (0);
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

int	exec_builtin(t_mini *sh)
{
/*	if (sh->pipe_lst->builtin == 1)
		return (ft_echo(sh));
	if (sh->pipe_lst->builtin == 2)
		return (ft_cd(sh));
	if (sh->pipe_lst->builtin == 3)
		return (ft_pwd(sh));
	if (sh->pipe_lst->builtin == 4)
		return (ft_export(sh));
	if (sh->pipe_lst->builtin == 5)
		return (ft_unset(sh));
	if (sh->pipe_lst->builtin == 6)
		return (ft_env(sh));
	if (sh->pipe_lst->builtin == 7)
		return (ft_exit(sh)); */
	return (sh->exit);
}

void	ft_open(t_mini *sh, t_pipe *p, t_fd *fd1)
{
	while (fd1)
	{
		printf("[OPEN] PIPE %s -- filename before open: %s, fd: %i\n", p->cmd[0], fd1->str, fd1->fd); //erase
	//	printf("[OPEN] PIPE %s -- before open: in: %i, out: %i\n", p->cmd[0], p->in_fd, p->out_fd); //erase
		if (p->in_fd >= 0 && (fd1->type == 6 || fd1->type == 9 || fd1->type == 4))
		{
			close(p->in_fd);
	//		p->in_fd = -2;
		}
		if (p->out_fd >= 0 && (fd1->type == 5 || fd1->type == 7))
		{
	//		printf("[OPEN] PIPE %s -- closing out before open: %s, fd: %i\n", p->cmd[0], fd1->str, fd1->fd);
			close(p->out_fd);
	//		p->out_fd = -2;
		}
		if (fd1->type == 6 || fd1->type == 9)
			p->in_fd = fd1->fd;
		else if (fd1->type == 4)
			p->in_fd = open(fd1->str, O_RDONLY);
		else if (fd1->type == 5)
			p->out_fd = open(fd1->str, O_TRUNC | O_CREAT | O_RDWR, 0666);
		else if (fd1->type == 7)
			p->out_fd = open(fd1->str, O_APPEND | O_CREAT | O_RDWR, 0666);
		if (p->in_fd < 0 && (fd1->type == 6 || fd1->type == 9 || fd1->type == 4))
			ft_exit_exe(sh, fd1->str, strerror(errno), 1); //to write this function
		if (p->out_fd < 0 && (fd1->type == 5 || fd1->type == 7))
			ft_exit_exe(sh, fd1->str, strerror(errno), 1); //to write this function
	//	printf("[OPEN] PIPE %s -- fd after open in: %i, out: %i\n", p->cmd[0], p->in_fd, p->out_fd); //erase
		fd1 = fd1->next;
	}
}

void	check_access(t_mini *sh, char **cmd, char **path)
{
	if (!cmd)
		return ;
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) == 0)
		{
			if (access(cmd[0], X_OK) != 0)
				ft_exit_exe(sh, cmd[0], "permission denied", 126); // here should be return
			*path = cmd[0];
		}
		else
			ft_exit_exe(sh, cmd[0], "command not found", 127);
	}
	else
		*path = check_paths(sh->paths, cmd[0], sh);
}

char	*check_paths(char **paths, char *cmd, t_mini *sh)
{
	char	*p;
	int		i;

	i = -1;
//	print_arr(sh->paths);
	while (paths[++i])
	{
		p = ft_smart_join(paths[i], "/", cmd);
//		printf("\n[CHECK PATHS] p: %s\n", p); //erase
		if (!p)
			ft_exit_exe(sh, "malloc", "allocation failed", errno);
		if (access(p, F_OK) == 0)
		{
			if (access(p, X_OK) != 0)
				ft_exit_exe(sh, cmd, "permission denied", 126);
			else
				return (p);
		}
		p = ft_memdel(p);
	}
	ft_exit_exe(sh, cmd, "command not found", 127);
	return (NULL);
}