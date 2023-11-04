/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_qt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:32:09 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/03 21:05:48 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	check_qt(char *str)
{
	unsigned int	i;
	unsigned int	limit;
	char			open;

	i = 0;
	open = 0;
	limit = 1000;
	while (str[i] && i < 1000)
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