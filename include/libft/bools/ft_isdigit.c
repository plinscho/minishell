/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:04:05 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/22 18:56:13 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*
int	main(void)
{
	int c;
	c = 8;

	if (ft_isdigit(c) == 1)
		printf("Thats one digit\n\n");
	else 
		printf("Thats not a digit");

	return(0);
}*/
