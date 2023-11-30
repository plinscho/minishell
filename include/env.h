/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:26:59 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/30 22:57:02 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
 # define ENV_H

//#include "minishell.h"

#include <stddef.h>
typedef struct s_mini t_mini;

typedef struct s_envlst
{
	char				*env_full;
	char				*env_val;
	char				*env_key;
	struct s_envlst		*next;
	
} t_env;

//###########################################################################################

//			--	--	ENV	--	--


/*
	EXPORT_UTILS_C
*/
t_env	*ft_getkey_node(char *key, t_env *list);
int		has_equal_sign(char *str);

// env.c

int		get_env(t_mini *sh, char **env);
char	*get_key(char *og_env, int *hasval);
char	*get_val(char *og_env);
int		env_converter(t_mini *sh);
size_t	env_variables(t_env *head, int option);
void	print_env(t_env *head, char **env);

//	ENV_LIST
int		allocate_env(t_mini *sh, size_t n);
int		ft_envadd_back(t_env **lst, t_env *new);
t_env	*envnode_new(char *env);
t_env	*ft_envlast(t_env *lst);

// FREE
void	free_env_lst(t_env *head);
void	free_env_chr(t_mini *sh);
void	free_env(t_mini *sh);
void	env_nodel(t_env *head, char *key);

//	env_remake.c
int		env_val_update(t_env *head, char *key, char *n_value);
int		get_sec_env(t_mini *sh);
int		bubble_env(t_env *head);

// env_utils.c 
char	*ft_get_value(t_mini *sh, char *key);
int		key_exists(t_env *head, char *key);
//env_sort.c
void sort_env(t_env *head);

#endif