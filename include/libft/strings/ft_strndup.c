/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:30:53 by plinscho          #+#    #+#             */
/*   Updated: 2023/10/17 22:55:59 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	unsigned int	i;
	char			*str;

	str = ft_calloc(n + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int main(void)
{   
    const char *s = "Hello, world!\n";
    char *new_s;

    new_s = ft_strndup(s, 3);
    printf("s: %s\nnew_s: %s\n", s, new_s);

    return (0);
}*/