/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:40:49 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/22 18:03:02 by nzhuzhle         ###   ########.fr       */
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
	t_fd	*fd_lst;
	int		in_fd; 
	int		out_fd;
	int		builtin;
	struct s_pipe	*next;
}	t_pipe;

/* a list with all the files names with redirections */
typedef struct s_fd
{
	int		fd;
	int		type;
	int		exp;
	char	*str;
	struct s_fd	*next;
}	t_fd;

//###########################################################################################

//			--	--	PARSER	--	--

/***** parser.c - the updated main with sh struct and  *****/
int		parser(t_mini *sh, t_lexer *lex, t_fd *hd, t_pipe *new);
int		parse_redir(t_pipe *new, t_lexer *lex, t_fd *hd, t_mini *sh);
int		parse_cmd(t_pipe *new, t_lexer *lex, t_mini *sh, int j);
int		count_cmd(t_lexer *temp);
t_lexer	*next_word(t_lexer *temp);
/***************************************************/

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
