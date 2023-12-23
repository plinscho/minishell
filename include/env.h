/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:26:59 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/23 17:19:04 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
 # define ENV_H

#include <stddef.h>
typedef struct s_mini t_mini;
typedef struct s_pipe t_pipe;

typedef struct s_envlst
{
	char				*env_key;
	char				*env_val;
	struct s_envlst		*next;
	
} t_env;

//###########################################################################################

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
void	print_env(t_env *head, char **env);

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

#endif
