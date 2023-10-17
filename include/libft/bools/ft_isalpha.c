/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:11:35 by plinscho          #+#    #+#             */
/*   Updated: 2023/09/08 20:33:20 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	
	char a;

	a = 'a';
	if (ft_isalpha(a) == 0)
		printf("its a character!\n\n");
	else
		printf("Thats not a char!\n\n");

	return(0);
}*/
