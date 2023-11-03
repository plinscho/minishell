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

//# include "../../include/minishell.h"
# include "../lexer/lexer.h"

/* a list with all the files names with redirections */
typedef struct s_fd
{
	char		*file; // name of the file
	int			hd; // fd where heredoc is stored, -2 if no heredoc. The heredoc will be stored in another list
	int			type; // 4 - infile, 5 - outfile, 6 - here_doc, 7 - outfile append
	struct s_fd	*next;
}	t_fd;

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
	t_fd	*fd_lst; // the list names of all the files
	int		in_fd; 
	int		out_fd;
	int		hd_flag; // do I need to know if there is a heredoc?
	t_var	vars; // a structure wih variables I'll need to use
	struct s_pipe	*prev;
	struct s_pipe	*next;

}	t_pipe;

#endif
