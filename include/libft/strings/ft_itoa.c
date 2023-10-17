/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:39:33 by plinscho          #+#    #+#             */
/*   Updated: 2023/05/18 18:07:02 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	n_elements(int n)
{
	size_t	elements;

	elements = 0;
	if (n == 0)
		elements = 1;
	while (n != 0)
	{
		n = n / 10;
		elements++;
	}
	return (elements);
}

static void	ft_populate(char *str, long int nbr, size_t len)
{
	while (len != 0)
	{
		str[len - 1] = nbr % 10 + '0';
		nbr = nbr / 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char		*new_string;
	size_t		len;
	int			is_negative;
	long int	nbr;

	nbr = n;
	is_negative = 0;
	if (nbr < 0)
	{
		is_negative = 1;
		nbr *= (-1);
	}
	len = n_elements(n) + is_negative;
	new_string = (char *)ft_calloc(len + 1, sizeof(char));
	if (!new_string)
		return (NULL);
	ft_populate(new_string, nbr, len);
	if (is_negative == 1)
		new_string[0] = '-';
	return (new_string);
}
