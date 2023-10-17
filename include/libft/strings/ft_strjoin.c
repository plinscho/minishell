/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:11:17 by plinscho          #+#    #+#             */
/*   Updated: 2023/05/16 18:11:14 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
/*Parámetros 
s1: La primera string.
s2: La string a añadir a ’s1’.
Reserva (con malloc(3)) y devuelve una nueva string, 
formada por la concatenación de ’s1’ y ’s2’.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	s1_lenght;
	size_t	s2_lenght;

	if (!(s1 && s2))
		return (0);
	s1_lenght = ft_strlen(s1);
	s2_lenght = ft_strlen(s2);
	new_string = malloc(s1_lenght + s2_lenght + 1);
	if (!new_string)
		return (NULL);
	ft_strlcpy(new_string, s1, s1_lenght + 1);
	ft_strlcpy(new_string + s1_lenght, s2, s1_lenght + s2_lenght + 1);
	return (new_string);
}
