/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:01:59 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/14 17:02:57 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		pre_quotes(char *line)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i])
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}