/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:40:49 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/24 21:13:03 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
 #define PARSER_H

#include "minishell.h"

/* a list with commands for child processes */
typedef struct s_pipe
{
	char	**cmd;
//	char	**paths; // where do I parse the path?
	t_fd	*fd_lst; // the list names of all the files and file descriptors
	int		in_fd; 
	int		out_fd;
//	int		hd_flag; // do I need to know if there is a heredoc?
//	t_var	*vars; // a structure wih variables I'll need to use
//	struct s_pipe	*prev;
	struct s_pipe	*next;

}	t_pipe;

/* a list with all the files names with redirections */
typedef struct s_fd
{
	int		fd; // file descriptor
	int		type; // 4 - infile, 5 - outfile, 6 - here_doc, 7 - outfile append
	char	*str; // keyword in heredoc, or the filename
	struct s_fd	*next;
}	t_fd;

//###########################################################################################

//			--	--	PARSER	--	--

/***** parser.c - the updated main with sh struct and  *****/
int		parser(t_mini *sh, t_lexer *lex, t_fd *hd, int check); // cleans all and returns 1 if malloc failed
int		parse_redir(t_pipe *new, t_lexer *lex, t_fd *hd, t_mini *sh); //we have 3 cases:
	//1. its one of the < > >>
	//2. its a heredoc
	//3. its a word so we treat it as a <
int		parse_cmd(t_pipe *new, t_lexer *lex, t_mini *sh); //I dont clean the lex here! 
int		count_cmd(t_lexer *temp); // counts words in a command
t_lexer	*next_word(t_lexer *temp); // gets the pointer to the next word in the command

/***** parser_utils.c - the updated main with sh struct and  *****/
void	pipe_init(t_pipe *pip);
void	pipe_add(t_mini *sh, t_pipe *new);
int		pipe_clean(t_pipe **lst);

/***** executor.c - main execution processes *****/
int		executor(t_mini *sh, t_pipe *p, int i, int j); // i = -1, j = -1
void	child_process(t_mini *sh, t_pipe *p, int flag, int *fd); // flag 0 if NOT last child, 1 if last one
int		last_child(t_mini *sh, t_pipe *p, int *fd); 
void	ft_redir(t_mini *sh, t_pipe *p, int *fd, int flag); // flag 0 if NOT last child, 1 if last one

/***** exec_utils.c - utils for execution processes *****/
int		check_builtin(char **cmd); // checks if the cmd is a builtin
int		exec_builtin(t_mini *sh); // executes the needed builtin
void	ft_open(t_mini *sh, t_pipe *p, t_fd *fd1); // opens all the file descriptors
int 	ft_exit_exe(t_mini *sh, char *name, char *message, int err); //- call this error function, passing it the name of a failed file
void	check_access(t_mini *sh, char **cmd, char **path);
char	*check_paths(char **paths, char *cmd, t_mini *sh);
int		ft_error_break(t_mini *sh, char *name, char *message, int err); //This one should only be used in the parent process

/***** printer.c - main execution processes *****/
void	print_parser_dina(t_pipe *p);
void	print_arr(char **arr);


#endif