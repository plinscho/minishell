/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:17:19 by plinscho          #+#    #+#             */
/*   Updated: 2023/09/08 21:22:25 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_print	*ft_initialize_tab(t_print *tab)
{
	tab -> specifier = '0';
	tab -> total_len = 0;
	return (tab);
}

int	ft_iterate_format(const char *fmt, int print_len, int control, t_print *tab)
{
	int		i;

	i = 0;
	while (fmt[i] && control != -1)
	{
		tab = ft_initialize_tab(tab);
		control = 0;
		if (fmt[i] == '%')
			control = ft_check_specifier(fmt, tab, ++i);
		else
			control = ft_putchar(fmt[i], tab);
		i++;
		if (control == -1)
			return (-1);
		print_len += tab -> total_len;
	}
	return (print_len);
}

int	ft_check_specifier(const char *fmt, t_print *tab, int position)
{
	int		check;

	check = 0;
	if (fmt[position] == 'c')
		check = ft_print_char(tab, check);
	else if (fmt[position] == 's')
		check = ft_print_string(tab, check);
	else if (fmt[position] == 'i' || fmt[position] == 'd')
		check = ft_print_int(tab, check);
	else if (fmt[position] == '%')
		check = ft_putchar('%', tab);
	else if (fmt[position] == 'u')
		check = ft_print_unsigned(tab, check);
	else if (fmt[position] == 'x' || fmt[position] == 'X')
		check = ft_print_x(tab, fmt[position]);
	else if (fmt[position] == 'p')
		check = ft_get_ptr(tab);
	return (check);
}

int	ft_printf(const char *fmt, ...)
{
	t_print	*tab;
	int		print_len;
	int		control;

	tab = (t_print *)malloc(sizeof(t_print));
	if (!tab)
		return (-1);
	va_start(tab -> arguments, fmt);
	control = 0;
	print_len = 0;
	print_len = ft_iterate_format(fmt, print_len, control, tab);
	va_end(tab -> arguments);
	free(tab);
	if (control == -1)
		return (-1);
	return (print_len);
}
