/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:47:18 by plinscho          #+#    #+#             */
/*   Updated: 2023/09/08 21:22:06 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_int(t_print *tab, int control)
{
	int		num;
	char	*nbr;

	num = va_arg(tab -> arguments, int);
	nbr = ft_itoa(num);
	if (nbr == NULL)
		return (-1);
	control = ft_putstr(nbr, tab);
	free(nbr);
	if (control == -1)
		return (-1);
	return (0);
}
