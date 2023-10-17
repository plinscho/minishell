/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:29:51 by plinscho          #+#    #+#             */
/*   Updated: 2023/05/16 16:25:53 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;
	size_t	k;

	if (needle[0] == '\0')
		return ((char *)(haystack));
	j = 0;
	while (haystack[j] != '\0' && j < len)
	{
		k = 0;
		while (haystack[j + k] == needle[k] && haystack[j + k] != '\0')
		{
			if (needle[k + 1] == '\0' && k + j < len)
			{
				haystack += j;
				return ((char *)(haystack));
			}
			k++;
		}
		j++;
	}
	return (0);
}
