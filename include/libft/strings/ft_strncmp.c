/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:37:57 by plinscho          #+#    #+#             */
/*   Updated: 2023/05/22 14:38:34 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				j;

	j = 0;
	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (s1[j] != '\0' && s2[j] != '\0' && s1[j] == s2[j] && i < n -1)
	{
		j++;
		i++;
	}
	return ((unsigned char)(s1[j]) - (unsigned char)(s2[j]));
}
