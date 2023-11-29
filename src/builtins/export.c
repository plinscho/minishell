/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:42:45 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/29 22:28:09 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

// full_var	[0] full variable
// 			[1] key (before '=')
// 			[2] value (if it exists)
int		var_ripper(char **full_var, char *exp_var, int *hasval)
{
	*hasval = 0;
	full_var[0] = ft_strdup(exp_var);
	if (!full_var[0])
		return (1);
	full_var[1] = get_key(exp_var, hasval);
	if (!full_var[1])
		return (1);
	if (hasval)
	{
		full_var[2] = get_val(exp_var);
		if (!full_var[2])
			return (1);		
	}
	else 
		full_var[2] = NULL;
	return (0);
}

// list == 0 --> env_lst
// list == 1 --> s_env
int		smart_env(t_mini *sh, char *variable)
{
	int		hasval;
	char	**full_var;

	full_var = (char **)malloc(sizeof(char *)*3);
	if (!full_var)
		return (1);
	if (var_ripper(full_var, variable, &hasval))
		return (1);
	if (hasval) // if it has a value, it goes to the public env
	{
		// check if there was the same key in secret env
		if (key_exists(sh->env_lst, full_var[1]))
			return (env_val_update(sh->env_lst, full_var[1], full_var[2]));
		// Create a new node
		return (ft_envadd_back(&sh->env_lst, envnode_new(full_var[0])));
	}
	else // if it does not have a value, it goes into the secret
	{
		if (key_exists(sh->env_sec, full_var[1]))
			return (0);
		return (ft_envadd_back(&sh->env_sec, envnode_new(full_var[0])));
	}
}

int		print_export(t_env *etmp)
{
	t_env	*eprint;

	eprint = etmp;
	while (eprint)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(eprint->env_full, 1);
		ft_putstr_fd("\n", 1);
		eprint = eprint->next;
	}
	return (0);
}


// 	Not all variables are included in the env
//	but some are in the export list.
int		ft_export(t_mini *sh)
{
	t_env			*etmp;
	char			**ecmd;
	unsigned int	i;

	ecmd = sh->pipe_lst->cmd;
	etmp = sh->env_sec;
	if (sh->env_sec == NULL || ecmd == NULL)
    	return (1);
	printf("cmd: %s\n", ecmd[1]);	// ERASE !!!!!!
//	sort_env(etmp);
	i = 1;
	if (ecmd[1] == NULL)
		return (print_export(etmp));
	else
	{
		while (ecmd[i] != NULL)
		{
			if (smart_env(sh, ecmd[i])) // malloc failed
				return (1);
			i++;
		}
	}
	return (0);
}
/*

FROM THE MANUAL - man export:

 When -p is specified, export shall write to the standard output the names and values of all exported vari‐
       ables, in the following format:

           "export %s=%s\n", <name>, <value>

       if name is set, and:

           "export %s\n", <name>

       if name is unset.

       The shell shall format the output, including the proper use of quoting, so that it is suitable for reinput
       to the shell as commands that achieve the same exporting results, except:

        1. Read-only variables with values cannot be reset.

        2. Variables that were unset at the time they were output need not be reset to the unset state if a value
           is assigned to the variable between the time the state was saved and the time at which the saved  out‐
           put is reinput to the shell.

*/