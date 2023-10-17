/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:28:16 by plinscho          #+#    #+#             */
/*   Updated: 2023/05/16 15:18:20 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p_s1;
	unsigned char	*p_s2;
	size_t			i;
	size_t			j;

	p_s1 = (unsigned char *)s1;
	p_s2 = (unsigned char *)s2;
	j = 0;
	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (p_s1 && p_s2 && p_s1[j] == p_s2[j] && i < n - 1)
	{
		j++;
		i++;
	}
	return ((unsigned char)(p_s1[j]) - (unsigned char)(p_s2[j]));
}
