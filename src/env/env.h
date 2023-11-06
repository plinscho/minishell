/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:19:33 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/06 18:26:10 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
 #define ENV_H

#include "../../include/minishell.h"

typedef struct s_envlst
{
	char				*env_full;
	char				*env_val;
	char				*env_key;
	struct s_envlst		*next;
	
} t_env;

// env.c
int		get_env(t_mini *sh, char **env);
char	*get_key(char *og_env);
char	*get_val(char *og_env);
void	print_env(t_env *head);


//	ENV_LIST
void	ft_envadd_back(t_env **lst, t_env *new);
t_env	*envnode_new(char *env);
void	env_del(t_env *head);
t_env	*ft_envlast(t_env *lst);

#endif