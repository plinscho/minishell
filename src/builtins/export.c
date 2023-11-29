/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:42:45 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/29 19:07:03 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		export_exe(t_env *head)
{
	(void)head;
	return (1);	
}

int		smart_env(t_mini *sh, char *variable)
{
	int		err;

	err = 0;
	if (has_equalsign(variable))
	{
		
		err = ft_envadd_back(&sh->env_lst, envnode_new(variable));
	}
	else
	{
		err = ft_envadd_back(&sh->env_sec, envnode_new(variable));
		
	}
	return (err);
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
	sort_env(etmp);
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