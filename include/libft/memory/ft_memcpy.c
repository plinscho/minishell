/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:27:17 by plinscho          #+#    #+#             */
/*   Updated: 2023/05/16 15:21:36 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*chr_dest;
	char	*chr_src;

	chr_dest = (char *)dest;
	chr_src = (char *)src;
	if (n == 0 || (dest == 0 && src == 0))
		return (dest);
	i = 0;
	while (i < n)
	{
		chr_dest[i] = chr_src[i];
		i++;
	}
	return ((void *)chr_dest);
}
