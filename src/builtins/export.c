/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:42:45 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/27 17:17:30 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		bubble_env(t_env *head)
{
	t_env 	*lptr = NULL;
	t_env	*ptr1 = head;
	int		swapped;
	
	if (head == NULL)
        return (1);

    swapped = 1; // Set to 1 initially to enter the loop
    while (swapped) {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            // Compare two environment keys and swap if needed
            if (strcmp(ptr1->env_key, ptr1->next->env_key) > 0) {
                // Swap the nodes
                t_env *temp = ptr1;
                ptr1 = ptr1->next;
                temp->next = ptr1->next;
                ptr1->next = temp;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
	return (0);
}

int		export_exe(t_env *head)
{
	(void)head;
	return (1);	
}

int		input_check(t_env *etmp, char **cmd_grd)
{
//	char *cmd_str;

	// if no arguments, return 1 and just print.
	if (cmd_grd[1] == NULL)
		return (1);
	// if 
	else
	{
		(void)etmp;
		return (0);
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

// Not all variables are included in the env, but some are in the export list.
int		ft_export(t_mini *sh)
{
	t_env	*etmp;
	char	**ecmd;

	ecmd = sh->pipe_lst->cmd;
	etmp = sh->env_lst;
	if (sh->env_lst == NULL)
    	return (1);

//	Bubble sorting the list, is needed for all cases.
	bubble_env(etmp);

//	Check if only printing or actually exporting | 1 == P , 2 == E
	if (input_check(etmp, ecmd) == 1)
		return (print_export(etmp));
	if(export_exe(etmp))
		return (1);

	return (1);
}