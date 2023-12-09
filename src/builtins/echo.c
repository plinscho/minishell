/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:41:54 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/09 21:29:53 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// ECho is a tricky function. Can be used almost everywhere and with -n extension.
// Im saving it for the last so that can work with the rest of the code when debugged.

/*
	CASES:

	bash-3.2$ echo -n howdy
	howdybash-3.2$

	bash-3.2$ echo -nnnnnnnnnn howdy -n
	howdy -nbash-3.2$

	bash-3.2$ echo -n -n -n -n howdy -n -nnnnnnnnn
	howdy -n -nnnnnnnnnbash-3.2$
*/

int		ft_echo(t_mini *sh)
{
	char	**cmd;
	int		i;
	
	i = 1;
	cmd = sh->pipe_lst->cmd;
	if (!cmd)
		return (1);
	

	
	return (0);
}