/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:41:18 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/21 19:15:11 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"
#include "../../include/minishell.h"

void	child_process(t_mini *sh, t_pipe *p)
{
	char	*the_path;

	the_path = NULL;
	close(sh->exe.fdp[0]);
	ft_open(sh, p, p->fd_lst);
	if (sh->pipe_lst->builtin)
		exit (exec_builtin(sh));
	if (dup2(p->in_fd, STDIN_FILENO) < 0)
		ft_exit_exe(sh, "dup2", strerror(errno), errno);
	close(p->in_fd);
	if (dup2(p->out_fd, STDOUT_FILENO) < 0)
		ft_exit_exe(sh, "dup2", strerror(errno), errno);
	close(p->out_fd);
	check_access(sh, p->cmd, &the_path);
	if (execve(the_path, p->cmd, sh->env) == -1)
		ft_exit_exe(sh, "execve", strerror(errno), errno);
}

int	last_child(t_mini *sh, t_pipe *p)
{
	sh->pipe_lst->builtin = check_builtin(p->cmd);
	if (!sh->pipes && sh->pipe_lst->builtin)
		return (exec_builtin(sh));
	sh->exe.pid = fork();
	if (sh->exe.pid < 0)
		return (3);
	else if (sh->exe.pid == 0)
		child_process(sh, p);
	return (0);
}

/*
This function
1. Return (0) - everything good
2. Return (1) - pipe failed
3. Return (3) - fork failed
Later we should transform it to error messages
i = -1
j = -1
*/
int	executor(t_mini *sh, t_pipe *p, int i, int j)
{
	while (++i < sh->pipes)
	{
		p->builtin = check_builtin(p->cmd);
		if (pipe(sh->exe.fdp) < 0)
			return (sh_clean(sh, errno));
		p->out_fd = sh->exe.fdp[1]; 
		sh->exe.pid = fork();
		if (sh->exe.pid < 0)
			return (sh_clean(sh, errno));
		else if (sh->exe.pid == 0)
			child_process(sh, p);
		close (sh->exe.fdp[1]);
		p = p->next;
		p->in_fd = sh->exe.fdp[0];
	}
	last_child(sh, p);
	while (++j <= sh->pipes)
	{
		if (waitpid(-1, &sh->exe.stat, 0) == sh->exe.pid)
			sh->exit = WEXITSTATUS(sh->exe.stat);
	}
	return (0);
}