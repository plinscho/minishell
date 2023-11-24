/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:22:33 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/21 19:16:06 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/***** executor.c - main execution processes *****/
/*int	executor(t_mini *sh, t_pipe *p, int i, int j); // i = -1, j = -1
void	child_process(t_mini *sh, t_pipe *p); 
int	last_child(t_mini *sh, t_pipe *p);*/

/***** exec_utils.c - utils for execution processes *****/
/*int	check_builtin(char *cmd); // checks if the cmd is a builtin
int	exec_builtin(t_mini *sh); // executes the needed builtin
void	ft_open(t_mini *sh, t_pipe *p, t_fd *fd1); // opens all the file descriptors
void ft_exit_exe(t_mini *sh, char *name, char *message, int err); //- call this error function, passing it the name of a failed file
void	check_access(t_mini *sh, char **cmd, char **path);
char	*check_paths(char **paths, char *cmd, t_mini *sh);
int	ft_error_break(t_mini *sh, char *name, char *message, int err); //This one should only be used in the parent process
*/
#endif
