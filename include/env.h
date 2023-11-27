/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:01:24 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/27 16:57:18 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:26:59 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/15 20:34:15 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
 # define ENV_H

//#include "minishell.h"

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

// env.c

int		get_env(t_mini *sh, char **env);
char	*get_key(char *og_env, int *hasval);
char	*get_val(char *og_env);
int		env_converter(t_mini *sh);
void	print_env(t_env *head, char **env);

//	ENV_LIST
int		allocate_env(t_mini *sh, size_t n);
int		ft_envadd_back(t_env **lst, t_env *new);
t_env	*envnode_new(char *env);
t_env	*ft_envlast(t_env *lst);

// FREE
void	free_env_lst(t_mini *sh);
void	free_env_chr(t_mini *sh);
void	free_env(t_mini *sh);

// env_utils.c 
char *ft_get_value(t_mini *sh, char *key);

#endif