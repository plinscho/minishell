/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:48:35 by plinscho          #+#    #+#             */
/*   Updated: 2023/09/08 21:22:11 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_string(t_print *tab, int control)
{
	char	*str;

	str = va_arg(tab -> arguments, char *);
	if (!str)
		str = "(null)";
	control = ft_putstr(str, tab);
	if (control == -1)
		return (-1);
	return (0);
}
