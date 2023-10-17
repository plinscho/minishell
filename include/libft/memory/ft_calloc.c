/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:57:58 by plinscho          #+#    #+#             */
/*   Updated: 2023/05/16 17:57:16 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t members, size_t size)
{
	void	*ptr;

	ptr = malloc(members * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, members * size);
	return (ptr);
}
