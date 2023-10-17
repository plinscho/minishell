/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:38:56 by plinscho          #+#    #+#             */
/*   Updated: 2023/05/16 15:27:08 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*p_dest;
	char	*p_src;
	size_t	i;

	p_dest = (char *)dest;
	p_src = (char *)src;
	if (src == (void *)0 && dest == (void *)0)
		return (NULL);
	i = 0;
	if (dest > src)
	{
		while (len-- > 0)
			p_dest[len] = p_src[len];
	}
	else
	{
		while (i < len)
		{
			p_dest[i] = p_src[i];
			i++;
		}
	}
	return (dest);
}
