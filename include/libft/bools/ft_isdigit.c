/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:04:05 by plinscho          #+#    #+#             */
/*   Updated: 2023/05/16 15:04:22 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
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
