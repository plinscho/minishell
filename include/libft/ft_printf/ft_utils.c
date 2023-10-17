/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:23:47 by plinscho          #+#    #+#             */
/*   Updated: 2023/09/08 21:22:32 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putchar(int c, t_print *tab)
{
	int	print;

	if ((ft_isalpha(c)) && (tab -> specifier == 'X'))
		c -= 32;
	print = write(1, &c, 1);
	if (print == -1)
		return (-1);
	tab -> total_len += print;
	return (0);
}

int	ft_putstr(char *string, t_print *tab)
{
	int	i;
	int	check;

	i = 0;
	while (string[i])
	{
		check = ft_putchar(string[i], tab);
		if (check == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_count_digits(unsigned int number)
{
	int	counter;

	counter = 0;
	if (number == 0)
		return (1);
	while (number >= 1)
	{
		counter++;
		number /= 10;
	}
	return (counter);
}
