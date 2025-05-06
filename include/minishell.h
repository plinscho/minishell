/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 22:10:06 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/28 17:00:46 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include <stddef.h>
# include <stdio.h>
# include <limits.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <string.h>

# define NORM		1
# define N_INTERACT	3

// global variable
extern int	g_sig_rec;
/*
typedef struct s_envlst	t_env;
typedef struct s_lexer	t_lexer;
typedef struct s_pipe	t_pipe;
typedef struct s_fd		t_fd;
typedef struct s_exec	t_exec;
typedef struct s_exp	t_exp;
typedef struct s_mini	t_mini;
*/

typedef struct s_envlst
{
	char				*env_key;
	char				*env_val;
	struct s_envlst		*next;
}	t_env;

typedef struct s_lexer
{
	char			*cont;
	int				token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_exp
{
	char	*cont;
	char	*new;
	char	*var;
	char	*val;
	int		alloc;
	int		k;
	int		j;
	int		fl;
	char	q;
}	t_exp;

/* a list with commands for child processes */

/* a list with all the files names with redirections */
typedef struct s_fd
{
	int			fd;
	int			type;
	int			exp;
	char		*str;
	struct s_fd	*next;
}	t_fd;

typedef struct s_pipe
{
	char			**cmd;
	char			*path;
	t_fd			*fd_lst;
	int				in_fd;
	int				out_fd;
	int				builtin;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_exec
{
	int		fdp[2];
	int		pid;
	int		stat;
}	t_exec;

typedef struct s_mini
{
	t_env	*env_lst;
	t_lexer	*lex_lst;
	t_pipe	*pipe_lst;
	t_fd	*hd_lst;
	t_exp	*exp;
	char	*input;
	char	**paths;
	int		exit;
	int		pipes;
	int		check;
	t_exec	*exe;
	char	**env;
	int		power_on;
}	t_mini;

//	BUILTINS

int		ft_env(t_mini *sh, t_pipe *p);
int		ft_export(t_mini *sh, t_pipe *p);
int		ft_pwd(t_mini *sh, t_pipe *p);
int		ft_exit(t_mini *sh);
int		ft_cd(t_mini *sh, t_pipe *p);
int		ft_unset(t_mini *sh, t_pipe *p);
int		ft_echo(t_mini *sh, t_pipe *p);

//			--	--	MAIN	--	--
int		minishell(t_mini *sh);

/***** initialize.c - initializing and cleaning sh!!! *****/
int		sh_init(t_mini *sh, char **env);
void	sh_clean(t_mini *sh);
t_mini	*sh_re(t_mini **sh, t_lexer *lex, t_fd *hd);
int		sh_loop_init(t_mini *sh);
int		allocate_exe(t_mini *sh);

//			--	--	LEXER	--	--

/***** lexer.c - Main and the main lexer cases *****/
int		lexer(t_mini *sh, char *input);
t_lexer	*read_redirection(char *in, t_mini *sh, int *i);
t_lexer	*read_in_quotes(char *in, int *i);
t_lexer	*read_word(char *in, int *i, char q, int j);
t_lexer	*read_space(char *in, int *i);
/***************************************************/

/***** lexer_utils.c - dealing with lexer lists *****/
int		lex_clean(t_lexer **lst);
t_lexer	*lex_new(char *content, int token);
void	lex_add(t_lexer **lst, t_lexer *new);
t_lexer	*lex_last(t_lexer *lst);
void	lex_insert(t_mini *sh, t_lexer *new, t_lexer **lex, t_lexer *temp);
/***************************************************/

/***** quotes.c - dealing with quotes *****/
int		word_in_quotes(char *in, char *q, int j);
char	*trim_quotes(char *s, char q, int len, int i);
int		len_no_q(char *s, char q, int len, int i);
int		open_q(t_exp *exp, char c, int type);
int		exp_quotes(t_mini *sh, t_lexer **head, int *flag);

/***** check_syntax.c - checks the syntax *****/
int		check_input(char *in); // checks if there is anything in the input
int		pre_quotes(char *line);
int		check_syntax(t_mini *sh, t_lexer *current, int prev_token);
char	int_to_char(int num);
int		ft_isspace(int c);
/***************************************************/

/***** utils.c - general utils *****/
char	*ft_substr_quotes(char *s, char q, int len, int i);
int		check_chr(char c);
char	**arr_clean(char **cmd, int flag);
int		ft_longer(char *str, char *key);
char	*ft_smart_join(char *s1, char *s2, char *s3);
/***************************************************/

//			--	--	HERE_DOC	--	--

/***** heredoc.c - after checking unclosed quotes *****/
int		ft_heredoc(t_mini *sh, char *in, int i);
int		find_hd(char *in, int i);
char	*keyword_hd(t_fd *new, char *in, int *i, char q);
int		save_hd(t_mini *sh, char *key, char *str, int type);
int		hd_close(int fd[], int flag);
/*************************************************/

/***** fd_utils.c - dealing with fd lists *****/
void	fd_add(t_fd **lst, t_fd *new);
void	fd_clean(t_fd **hd, int flag);
int		fd_init(t_fd *new, t_mini *sh, int fd);
int		ft_open_built(t_mini *sh, t_pipe *p, t_fd *fd1, int prev);
/*************************************************/

//			--	--	SIGNALS	--	--

void	norm_handler(int sig, siginfo_t *data, void *non_used_data);
void	do_sigign(int signum);
int		init_signals(int mode);
void	exit_status(t_mini	*sh, int j);
/*************************************************/

//			--	--	ERRORS	--	--

int		quotes_error(t_mini *sh);
int		err_char(t_mini *sh, int token);
int		error_option(char *str1, char *str2, char **vc);
int		err_break(t_mini *sh, char *name, char *message, int err);
int		err_exit(t_mini *sh, char *name, char *message, int err);

//			--	--	ENV	--	--

int		first_env(t_mini *sh, char **env);
void	add_env_to_list(t_mini *sh, t_env *new_env);
char	**env_converter(t_env *env);
size_t	env_var(t_env *head, int option);
char	*ft_envfull(char *key, char *value);

//			--	--	ENV_LIST	--	--

t_env	*ft_getkey_node(char *new_key, t_env *list);
int		add_or_update_env(t_mini *sh, char *name, char *value);
int		env_add_last(t_mini *sh, char *name, char *value, int has_value);
int		env_val_update(t_env *head, char *key, char *n_value);

//			--	--	ENV_UTILS	--	--

char	*ft_get_value(t_mini *sh, char *key);

//			--	--	ENV_SORT	--	--

void	sort_env(t_env *head);
void	print_sort_print(t_env *env);

//			--	--	ENV_FREE	--	--

int		free_env_lst(t_env *head);
void	free_env(t_mini *sh);

//			--	--	EXPORT_UTILS	--	--
int		export_option(const char *name);
char	*find_in_env_variables(t_mini *sh, char *variable_name);
int		print_export(t_env *eprint, t_pipe *p);

//			--	--	UNSET	--	--
void	unset_var(t_mini *sh, char *var);
void	unset_free(t_env *env);

//			--	--	EXPANSER	--	--

/**********   expanser.c -  ***********/
int		expanser(t_mini *sh, t_lexer *lex, int flag);
char	*expand_str(t_mini *sh, char *cont, int type, int i);
int		expand_word(t_mini *sh, t_lexer **lex);
t_lexer	*read_word_exp(char *in, int *i, char q, int j);
char	*expand_hd(t_mini *sh, char *cont, int type);
/***************************************************/

/**********   expanser_utils.c -  ******/
int		check_exp(char *cont, int type, int q);
int		new_len(t_mini *sh, char *cont, int type);
char	*get_var(char *cont);
char	*check_value(t_mini *sh, char *var);
int		check_file_exp(char *str);
/***************************************************/

/**********   exp_struct.c -  ******/
int		exp_init(t_mini *sh);
void	exp_nano_clean(t_exp *exp);
void	exp_clean(t_exp **exp);
int		exp_start(t_mini *sh, char *cont, int type);
char	*exp_file(t_mini *sh, char *cont, t_fd *new);
/***************************************************/

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
/***************************************************/

//			--	--	EXECUTOR	--	--

/***** executor.c - main execution processes *****/
int		executor(t_mini *sh, t_pipe *p, int i, int j);
void	child_process(t_mini *sh, t_pipe *p, int flag);
int		last_child(t_mini *sh, t_pipe *p);
void	ft_redir(t_mini *sh, t_pipe *p);
int		exec_builtin(t_mini *sh, t_pipe *p);
/*************************************************/

/***** exec_utils.c - utils for execution processes *****/
int		check_builtin(char **cmd);
void	ft_open(t_mini *sh, t_pipe *p, t_fd *fd1, int prev);
void	ft_check_open(t_pipe *p, t_fd *cur, int prev);
void	check_access(t_mini *sh, char **cmd, t_pipe *p);
void	check_paths(char **paths, char *cmd, t_mini *sh, t_pipe *p);
/*********************************************************/

#endif
