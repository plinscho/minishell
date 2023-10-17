/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:04:38 by plinscho          #+#    #+#             */
/*   Updated: 2023/05/16 15:35:25 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	a;

	a = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		((char *)b)[i] = a;
		i++;
	}
	return (b);
}
/*
int main(void)
{
	char str[20] = "Hello, world";
	printf("original: %s\n", str);
	ft_memset(str, 'a', 4);
	printf("modified: %s\n", str);

	return (0);
}*/
