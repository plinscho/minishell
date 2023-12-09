/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:40:49 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/09 16:06:30 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
 #define PARSER_H

//#include "minishell.h"
typedef struct s_envlst	t_env;
typedef struct s_lexer	t_lexer;
typedef struct s_pipe	t_pipe;
typedef struct s_fd		t_fd;
typedef struct s_exec	t_exec;
typedef struct s_exp	t_exp;

/* a list with commands for child processes */
typedef struct s_pipe
{
	char	**cmd;
	char	*path;
	t_fd	*fd_lst; // the list names of all the files and file descriptors
	int		in_fd; 
	int		out_fd;
	int		builtin;
//	struct s_pipe	*prev;
	struct s_pipe	*next;
}	t_pipe;

/* a list with all the files names with redirections */
typedef struct s_fd
{
	int		fd;		// file descriptor
	int		type;	// 4 - infile, 5 - outfile, 6 - here_doc, 7 - outfile append
	int		exp;	// flag, if there is an ambiguos redirect
	char	*str;	// keyword in heredoc, or the filename
	struct s_fd	*next;
}	t_fd;

//###########################################################################################

//			--	--	PARSER	--	--

/***** parser.c - the updated main with sh struct and  *****/
int		parser(t_mini *sh, t_lexer *lex, t_fd *hd, int check); // cleans all and returns 1 if malloc failed
int		parse_redir(t_pipe *new, t_lexer *lex, t_fd *hd, t_mini *sh); //we have 2 cases: < || > || >> and heredoc

int		parse_cmd(t_pipe *new, t_lexer *lex, t_mini *sh); //I dont clean the lex here! 
int		count_cmd(t_lexer *temp); // counts words in a command
t_lexer	*next_word(t_lexer *temp); // gets the pointer to the next word in the command

/***** parser_utils.c - the updated main with sh struct and  *****/
void	pipe_init(t_pipe *pip);
void	pipe_add(t_mini *sh, t_pipe *new);
int		pipe_clean(t_pipe **lst);

/***** printer.c - main execution processes *****/
void	print_parser(t_pipe *p);
void	print_arr(char **arr);
void	print_lexer(t_mini *sh);
void	print_lex_node(t_lexer *lex_list);
void	print_exp(t_exp *exp);

#endif
