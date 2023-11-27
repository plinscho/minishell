/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:41:18 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/27 20:03:40 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/executor.h"
#include "../../include/minishell.h"

void	ft_redir(t_mini *sh, t_pipe *p, int flag)
{
//	printf("\n[REDIR] PIPE: %s, in: %i\n", p->cmd[0], p->in_fd); //erase
	if (p->in_fd >= 0)
	{
//		printf("\n[REDIR] PIPE: %s, BEFORE dup in\n", p->cmd[0]); //erase
		if (dup2(p->in_fd, STDIN_FILENO) < 0)
			err_exit(sh, "in", strerror(errno), errno);
		close(p->in_fd);
		p->in_fd = -2;
//		printf("\n[REDIR] PIPE: %s, after dup in\n", p->cmd[0]); //erase
	}
	if (p->out_fd >= 0)
	{
//		printf("\n[REDIR] PIPE: %s, BEFORE dup out\n", p->cmd[0]); //erase
		if (dup2(p->out_fd, STDOUT_FILENO) < 0)
			err_exit(sh, "out", strerror(errno), errno);
		close(p->out_fd);
		p->out_fd = -2;
//		printf("\n[REDIR] PIPE: %s, AFTER dup out\n", p->cmd[0]); //erase
	}
	else if (!flag)
	{
//		printf("\n[REDIR] PIPE: %s, if there is pipe BEFORE dup out fd: %i\n", p->cmd[0], fd[1]); //erase
		if (dup2(sh->exe->fdp[1], STDOUT_FILENO) < 0)
			err_exit(sh, "pipe", strerror(errno), errno);
		close(sh->exe->fdp[1]);
		sh->exe->fdp[1] = -2;
	}

}

void	child_process(t_mini *sh, t_pipe *p, int flag)
{
	char	*the_path;

	the_path = NULL;
//	printf("\n[CHILD] NEW PIPE: %p\n", p->cmd); //erase
	if (!flag)
	{
		close(sh->exe->fdp[0]); //check this
		sh->exe->fdp[0] = -2;
	}
//	printf("[CHILD] PIPE %p -- fd before open, in: %i, out - %i\n", p->cmd, p->out_fd, p->out_fd); //erase
	ft_open(sh, p, p->fd_lst);
//	printf("[CHILD] PIPE %p -- fd after open, in: %i, out - %i\n", p->cmd, p->in_fd, p->out_fd); //erase
	if (sh->pipe_lst->builtin)
		exit(exec_builtin(sh));
//	printf("\n[CHILD] Not command: %p\n", p->cmd); //erase
//	if (!p->cmd)
//		ft_exit_exe(sh, NULL, NULL, 0); // do not 
	check_access(sh, p->cmd, &the_path);
//	printf("\n[CHILD] after check access: %s\n", the_path); //erase
	ft_redir(sh, p, flag);
//	ft_putstr_fd("after redir -- ", 2);
//	ft_putstr_fd(p->cmd[0], 2);
//	ft_putstr_fd(" \n", 2);
	if (execve(the_path, p->cmd, sh->env) == -1)
		err_exit(sh, "execve", strerror(EXIT_FAILURE), EXIT_FAILURE);
}

int	last_child(t_mini *sh, t_pipe *p)
{
	sh->pipe_lst->builtin = check_builtin(p->cmd);
//	printf("\n[LAST CHILD] NEW PIPE: %s\n", p->cmd[0]); //erase
	if (!sh->pipes && sh->pipe_lst->builtin)
		return (exec_builtin(sh));
	sh->exe->pid = fork();
	if (sh->exe->pid < 0)
		return (3);
	else if (sh->exe->pid == 0)
		child_process(sh, p, 1);
	if (sh->pipes && p->in_fd >= 0)
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
//	int	fd[2];
	
//	printf("\n[EXEC] PIPES: %i\n", sh->pipes); //erase
	while (++i < sh->pipes)
	{
//		printf("\n[EXEC] PIPES: %i, i: %i\n", sh->pipes, i); //erase
		p->builtin = check_builtin(p->cmd);
		if (pipe(sh->exe->fdp) < 0)
			return (sh_clean(sh, errno));
//		printf("\n[EXEC] after pipe fd[0]: %i, fd[1]: %i\n", fd[0], fd[1]); //erase
		sh->exe->pid = fork();
		if (sh->exe->pid < 0)
			return (sh_clean(sh, errno));
		else if (sh->exe->pid == 0)
			child_process(sh, p, 0);
		close (sh->exe->fdp[1]);
		if (p->in_fd >= 0)
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
