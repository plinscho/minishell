/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:26:59 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/07 15:45:38 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
 # define ENV_H

//#include "minishell.h"

#include <stddef.h>
typedef struct s_mini t_mini;

typedef struct s_envlst
{
	char				*env_key;
	char				*env_val;
	struct s_envlst		*next;
	
} t_env;

//###########################################################################################

//			--	--	ENV	--	--

//unset.c
void	unset_var(t_mini *sh, char *var);
void	unset_free(t_env *env);

//export.c


/*
// OLD

int		first_env(t_mini *sh, char **env);
char	*get_key(char *og_env, int *hasval);
char	*get_val(char *og_env);
int		env_converter(t_mini *sh);
int		allocate_env(t_mini *sh, size_t n);

// export_utils.c
int		key_in_env(char *new_key, t_env *env);
void	make_env_full(t_env *node, char *key, char *val, char *full);
t_env	*ft_getkey_node(char *key, t_env *list);
int		print_export(t_env *etmp);
int		has_equal_sign(char *str);

//	ENV_LIST
char	*ft_envfull(char *key, char *value);
int		ft_envadd_back(t_env **lst, t_env *new);
t_env	*envnode_new(char *env);
t_env	*ft_envlast(t_env *lst);

//	env_remake.c
int		get_sec_env(t_mini *sh);

// env_utils.c
size_t	env_variables(t_env *head, int option);
int		key_exists(t_env *head, char *key);

*/
// FREE
void	free_env_lst(t_env *head);
void	free_env_chr(t_mini *sh);
void	free_env(t_mini *sh);

//env_utils.c
void	print_env(t_env *head, char **env);
int		env_val_update(t_env *head, char *key, char *n_value);
size_t	env_variables(t_env *head, int option);
char	*ft_get_value(t_mini *sh, char *key);
char	*ft_envfull(char *key, char *value);

// env_sort.c
void	sort_env(t_env *head);
t_env	*list_copy(t_env *og);
t_env	*env_new_node(t_env *original);

// export.c


// export_utils.c
int		export_option(const char *name);
char	*find_in_env_variables(t_mini *sh, char *variable_name);
int		print_export(t_env *eprint);

//	env2.c
int		first_env(t_mini *sh, char **env);
void	add_or_update_env(t_mini *sh, char *name, char *value);
char	**env_converter(t_env *env);
void	add_or_update_env(t_mini *sh, char *name, char *value);
//static t_env	*last_env(t_env *env);

// env_list.c
size_t	env_variables(t_env *head, int option);
void	add_env_to_list(t_env **env, t_env *new_env);
//static t_env	*last_env(t_env *env);


#endif