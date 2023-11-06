/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_qt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:32:09 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/06 16:55:10 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_qt(char *str)
{
	unsigned int	i;
	char			open;

	i = 0;
	open = 0;
	while (str[i])
	{
		if (i > 0 && str[i - 1] == '\\')
			;
		else if (open == 0 && str[i] == '\"')
			open = 1;
		else if (open == 0 && str[i] == '\'')
			open = 2;
		else if (open == 1 && str[i] == '\"')
			open = 0;
		else if (open == 2 && str[i] == '\'')
			open = 0;
		i++;
	}
	return(open);
}