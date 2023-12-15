/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:22:33 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/15 19:16:23 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

//# include "minishell.h"

typedef struct s_mini t_mini;
typedef struct s_pipe	t_pipe;
typedef struct s_fd		t_fd;
typedef struct s_exec	t_exec;

typedef struct s_exec
{
	int		fdp[2];		//array of 2 fd to use in pipe
	int		pid;		//what we receive by fork
	int		stat;		//the last process exit status
}	t_exec;


/***** executor.c - main execution processes *****/
int		executor(t_mini *sh, t_pipe *p, int i, int j); // i = -1, j = -1
void	child_process(t_mini *sh, t_pipe *p, int flag); // flag 0 if NOT last child, 1 if last one
int		last_child(t_mini *sh, t_pipe *p); 
void	ft_redir(t_mini *sh, t_pipe *p); // flag 0 if NOT last child, 1 if last one
int		exec_builtin(t_mini *sh, t_pipe *p); // executes the needed builtin
/*************************************************/

/***** exec_utils.c - utils for execution processes *****/
int		check_builtin(char **cmd); // checks if the cmd is a builtin
void	ft_open(t_mini *sh, t_pipe *p, t_fd *fd1, int prev); // opens all the file descriptors
void	ft_check_open(t_pipe *p, t_fd *cur, int prev); // check if the prev is open and closes it
void	check_access(t_mini *sh, char **cmd, t_pipe *p);
void	check_paths(char **paths, char *cmd, t_mini *sh, t_pipe *p);
/*********************************************************/


#endif
