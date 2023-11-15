/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:40:49 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/15 20:57:25 by plinscho         ###   ########.fr       */
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

/*
//			--	--	PARSER	--	--


// parser_main.c - the updated main with sh struct and  
int	parser(t_mini **sh, t_lexer *lex, t_fd *hd, int check);  cleans all and returns 1 if malloc failed
int	parse_redir(t_pipe *new, t_lexer *lex, t_fd *hd, t_mini *sh); 
//we have 3 cases:
	//1. its one of the < > >>
	//2. its a heredoc
	//3. its a word so we treat it as a <

int	parse_cmd(t_pipe *new, t_lexer *lex, t_mini *sh); //I dont clean the lex here! 
void	print_parser(t_mini *sh);

*/

// parser_utils.c - the updated main with sh struct and  //
void	pipe_init(t_pipe *pip);
void	pipe_add(t_pipe **lst, t_pipe *new);
void	fd_init(t_fd *new, t_lexer *lex, int fd, int type);

// initialize.c - initializing and cleaning sh!!! //
int		sh_init(t_mini *sh, char **env); // check with Paul
int		sh_clean(t_mini *sh, int err);
int		minishell(t_mini *sh);

//###########################################################################################


#endif