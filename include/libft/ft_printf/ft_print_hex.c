/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:23:40 by plinscho          #+#    #+#             */
/*   Updated: 2023/09/08 21:22:04 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_dectohex(unsigned int decimal, t_print *tab)
{
	char			hexa_digit;
	unsigned int	reminder;
	int				control;

	if (decimal == 0)
		return (0);
	if (ft_dectohex(decimal / 16, tab) == -1)
		return (-1);
	control = 0;
	reminder = decimal % 16;
	if (reminder < 10)
		hexa_digit = reminder + '0';
	else
		hexa_digit = reminder - 10 + 'a';
	control = ft_putchar(hexa_digit, tab);
	if (control == -1)
		return (-1);
	return (0);
}

int	ft_dectoptr(unsigned long int adress, t_print *tab)
{
	int					control;
	unsigned long int	reminder;
	char				digit;

	if (adress == 0)
		return (0);
	ft_dectoptr(adress / 16, tab);
	control = 0;
	reminder = adress % 16;
	if (reminder < 10)
		digit = reminder + '0';
	else
		digit = reminder - 10 + 'a';
	control = ft_putchar(digit, tab);
	if (control == -1)
		return (-1);
	return (0);
}

int	ft_print_x(t_print *tab, const char c)
{
	unsigned int	decimal;
	int				control;

	control = 0;
	tab ->specifier = c;
	decimal = va_arg(tab->arguments, unsigned int);
	if (decimal == 0)
		control = ft_putchar('0', tab);
	else
		control = ft_dectohex(decimal, tab);
	if (control == -1)
		return (-1);
	return (0);
}
