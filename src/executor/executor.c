/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:41:18 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/27 20:47:27 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/executor.h"
#include "../../include/minishell.h"

void	ft_redir(t_mini *sh, t_pipe *p)
{
//	printf("\n[REDIR] PIPE: %s, in: %i\n", p->cmd[0], p->in_fd); //erase
	if (p->in_fd >= 0)
	{
//		printf("\n[REDIR] PIPE: %s, BEFORE dup in\n", p->cmd[0]); //erase
		if (dup2(p->in_fd, STDIN_FILENO) < 0)
			err_exit(sh, "dup2", NULL, 1);
		close(p->in_fd);
		p->in_fd = -2;
//		printf("\n[REDIR] PIPE: %s, after dup in\n", p->cmd[0]); //erase
	}
	if (p->out_fd >= 0)
	{
//		printf("\n[REDIR] PIPE: %s, BEFORE dup out\n", p->cmd[0]); //erase
		if (dup2(p->out_fd, STDOUT_FILENO) < 0)
			err_exit(sh, "dup2", NULL, 1);
		close(p->out_fd);
		p->out_fd = -2;
//		printf("\n[REDIR] PIPE: %s, AFTER dup out\n", p->cmd[0]); //erase
	}
}

void	child_process(t_mini *sh, t_pipe *p, int flag)
{
//	printf("\n[CHILD] NEW PIPE: %p\n", p->cmd); //erase
	init_signals(N_INTERACT);
	if (!flag)
	{
//		printf("\n[CHILD] closing fd[0]: %i\n", sh->exe->fdp[0]); //erase
		close(sh->exe->fdp[0]); //check this
		sh->exe->fdp[0] = -2;
	}
//	printf("[CHILD] PIPE %p -- fd before open, in: %i, out - %i\n", p->cmd, p->out_fd, p->out_fd); //erase
	ft_open(sh, p, p->fd_lst, -1);
//	printf("[CHILD] PIPE %s -- fd after open, in: %i, out: %i, flag built: %i\n", p->cmd[0], p->in_fd, p->out_fd, p->builtin); //erase
//	if (sh->pipe_lst->builtin)
//		exit(exec_builtin(sh, p));
//	printf("\n[CHILD] Not command: %p\n", p->cmd); //erase
//	if (!p->cmd)
//		ft_exit_exe(sh, NULL, NULL, 0); // do not 
	if (p->builtin)
		exit(exec_builtin(sh, p));
	check_access(sh, p->cmd, p);
//	printf("\n[CHILD]after check access: %s\n", p->path); //erase
	ft_redir(sh, p);
//	ft_putstr_fd("after redir -- ", 2);
//	ft_putstr_fd(p->cmd[0], 2);
//	ft_putstr_fd(" \n", 2);
	if (execve(p->path, p->cmd, sh->env) == -1)
		err_exit(sh, "execve", NULL, 14);
}

int	last_child(t_mini *sh, t_pipe *p)
{
	p->builtin = check_builtin(p->cmd);
//	printf("\n[LAST CHILD] NEW PIPE: %s\n", p->cmd[0]); //erase
	if (!sh->pipes && sh->pipe_lst->builtin)
	{
		sh->exit = exec_builtin(sh, p);
		return (0);
	}
	sh->exe->pid = fork();
	if (sh->exe->pid < 0)
		return (err_break(sh, "fork", NULL, 12));
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
//	printf("\n[EXEC] PIPES: %i\n", sh->pipes); //erase
	while (++i < sh->pipes)
	{
//		printf("\n[EXEC] PIPES: %i, i: %i\n", sh->pipes, i); //erase
		p->builtin = check_builtin(p->cmd);
//		printf("\n[EXEC] FLAG BUILT: %i\n", p->builtin); //erase
		if (pipe(sh->exe->fdp) < 0)
			return (err_break(sh, "pipe", "Broken pipe", 32));
//		printf("\n[EXEC] after pipe fd[0]: %i, fd[1]: %i\n", fd[0], fd[1]); //erase
		p->out_fd = sh->exe->fdp[1];
		sh->exe->pid = fork();
		if (sh->exe->pid < 0)
			return (err_break(sh, "fork", NULL, 12));
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
		if (sh->exe->pid == wait(&sh->exe->stat))
		{
			if (WIFEXITED(sh->exe->stat))
				sh->exit = WEXITSTATUS(sh->exe->stat);
			else if (WIFSIGNALED(sh->exe->stat))
			{
				if (WTERMSIG(sh->exe->stat) == SIGINT)
				{
					printf("\n");
					sh->exit = 130;
				}
				else if (WTERMSIG(sh->exe->stat) == SIGQUIT)
					(1 && (sh->exit = 131) && (printf("Quit: 3\n")));
			}
		}
	}
	return (0);
}

int	exec_builtin(t_mini *sh, t_pipe *p)
{	
	if (!sh->pipes && ft_open_built(sh, p, p->fd_lst, -1))
		return (sh->exit);
	if (p->builtin == 1)
		return (ft_echo(sh, p));
	if (p->builtin == 2)
		return (ft_cd(sh, p));
	if (p->builtin == 3)
		return (ft_pwd(sh, p));
	if (p->builtin == 4)
		return (ft_export(sh, p));
	if (p->builtin == 5)
		return (ft_unset(sh, p));
	if (p->builtin == 6 && sh->paths)
		return (ft_env(sh, p));
	else if (p->builtin == 6 && !sh->paths)
		err_break(sh, p->cmd[0], "No such file or directory", 127);
	if (p->builtin == 7)
		return (ft_exit(sh)); 
	return (sh->exit);
}