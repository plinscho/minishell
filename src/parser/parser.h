/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:00:51 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/10/29 19:50:21 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../include/minishell.h"
# include "../lexer/lexer.h"

/* a struct with variables */
typedef struct s_var
{
	char	*str_d; // string you get in heredoc to compare it with the key word

}	t_var;

/* a list with commands for child processes */
typedef struct s_pipe
{
	char	**cmd;
	char	**paths; // where do I parse the path?
	t_fd	*fd_lst; // the list names of all the files and file descriptors
	int		in_fd; 
	int		out_fd;
//	int		hd_flag; // do I need to know if there is a heredoc?
	t_var	*vars; // a structure wih variables I'll need to use
//	struct s_pipe	*prev;
	struct s_pipe	*next;

}	t_pipe;

/***** parser_main.c - the updated main with sh struct and  *****/
int	parser(t_mini **sh, t_lexer *lex, t_fd *hd); // cleans all and returns 1 if malloc failed
t_lexer	*parse_redir(t_pipe **new, t_lexer *lex, t_fd **hd);
t_lexer	*parse_cmd(t_pipe **new, t_lexer *lex);

/***** parser_utils.c - the updated main with sh struct and  *****/
void	pipe_init(t_pipe *pip);
void	pipe_add(t_pipe **lst, t_pipe *new);

/***** initialize.c - initializing and cleaning sh!!! *****/
void	mini_init(t_mini *sh); // check with Paul
int	sh_clean(t_mini **sh, int err); // checking with Paul



#endif
