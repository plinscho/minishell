/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:15:43 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/02 22:15:46 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	hd_add(t_hd **lst, t_hd *new)
{
	t_hd	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp -> next)
		temp = temp -> next;
	temp -> next = new;
}

int	ft_longer(char *str, char *key)
{
	int	len;

//	printf("in ft_longer: str - %zu, key - %zu\n", ft_strlen(str), ft_strlen(key)); //erase
	if (ft_strlen(str) > ft_strlen(key))
		len = ft_strlen(str);
	else
	{
		len = ft_strlen(key);
	}
//	printf("in ft_longer: len -  %i\n", len); //erase
	return (len);
}