/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:41:18 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/23 17:18:49 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"
#include "../../include/minishell.h"

void	ft_redir(t_mini *sh, t_pipe *p, int flag)
{
//	printf("\n[REDIR] PIPE: %s\n", p->cmd[0]); //erase
	if (p->in_fd >= 0)
	{
		printf("\n[REDIR] PIPE: %s, BEFORE dup in\n", p->cmd[0]); //erase
		if (dup2(p->in_fd, STDIN_FILENO) < 0)
			ft_exit_exe(sh, "IN", strerror(errno), errno);
//		close(p->in_fd);
//		p->in_fd = -2;
//		printf("\n[REDIR] PIPE: %s, after dup in\n", p->cmd[0]); //erase
	}
	if (p->out_fd >= 0)
	{
		printf("\n[REDIR] PIPE: %s, BEFORE dup out\n", p->cmd[0]); //erase
		if (dup2(p->out_fd, STDOUT_FILENO) < 0)
			ft_exit_exe(sh, p->cmd[0], strerror(errno), errno);
//		close(p->out_fd);
//		p->out_fd = -2;
//		printf("\n[REDIR] PIPE: %s, AFTER dup out\n", p->cmd[0]); //erase
	}
	else if (!flag)
	{
		printf("\n[REDIR] PIPE: %s, if there is pipe BEFORE dup out fd: %i\n", p->cmd[0], sh->exe->fdp[1]); //erase
		if (dup2(sh->exe->fdp[1], STDOUT_FILENO) < 0)
			ft_exit_exe(sh, p->cmd[0], strerror(errno), errno);
//		close(sh->exe.fdp[1]);
	}

}

void	child_process(t_mini *sh, t_pipe *p, int flag, int pip)
{
	char	*the_path;

	the_path = NULL;
//	printf("\n[CHILD] NEW PIPE: %s\n", p->cmd[0]); //erase
	if (!flag)
		close(sh->exe->fdp[0]); //check this
//	printf("[CHILD] PIPE %s -- fd before open: %i\n", p->out_fd); //erase
	ft_open(sh, p, p->fd_lst);
	printf("[CHILD] PIPE %s -- fd after open, in: %i, out - %i\n", p->cmd[0], p->in_fd, p->out_fd); //erase
	if (sh->pipe_lst->builtin)
		exit (exec_builtin(sh));
	check_access(sh, p->cmd, &the_path);
	printf("\n[CHILD] after check access: %s\n", the_path); //erase
	ft_redir(sh, sh->pipe_lst, flag);
	ft_putstr_fd("after redir -- \n", 2);
	if (execve(the_path, p->cmd, sh->envp) == -1)
		ft_exit_exe(sh, "execve", strerror(errno), errno);
}

int	last_child(t_mini *sh, t_pipe *p)
{
	sh->pipe_lst->builtin = check_builtin(p->cmd);
	printf("\n[LAST CHILD] NEW PIPE: %s\n", p->cmd[0]); //erase
	if (!sh->pipes && sh->pipe_lst->builtin)
		return (exec_builtin(sh));
	sh->exe->pid = fork();
	if (sh->exe->pid < 0)
		return (3);
	else if (sh->exe->pid == 0)
		child_process(sh, p, 1, -1);
	if (sh->pipes)
		close(p->in_fd);
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
	printf("\n[EXEC] PIPES: %i\n", sh->pipes); //erase
	while (++i < sh->pipes)
	{
		p->builtin = check_builtin(p->cmd);
		if (pipe(sh->exe->fdp) < 0)
			return (sh_clean(sh, errno));
		sh->exe->pid = fork();
		if (sh->exe->pid < 0)
			return (sh_clean(sh, errno));
		else if (sh->exe->pid == 0)
			child_process(sh, p, 0, sh->exe->fdp);
		close (sh->exe->fdp[1]);
		close (p->in_fd);
		p = p->next;
		p->in_fd = sh->exe->fdp[0];
	}
	last_child(sh, p);
	while (++j <= sh->pipes)
	{
		if (waitpid(-1, &sh->exe->stat, 0) == sh->exe->pid)
			sh->exit = WEXITSTATUS(sh->exe->stat);
	}
	return (0);
}