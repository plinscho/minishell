/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:48:37 by plinscho          #+#    #+#             */
/*   Updated: 2023/05/16 16:16:04 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_d;
	size_t	len_s;
	size_t	i;

	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	if (dstsize == 0)
		return (len_s);
	i = 0;
	while (src[i] && len_d + i < dstsize - 1)
	{
		dst[len_d + i] = ((char *)src)[i];
		i++;
	}
	dst[len_d + i] = '\0';
	if (dstsize <= len_d)
		return (len_s + dstsize);
	return (len_d + len_s);
}
