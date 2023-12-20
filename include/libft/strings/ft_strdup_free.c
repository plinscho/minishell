/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:42:45 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/20 14:43:14 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup_free(char *s)
{
	size_t	i;
	int		j;
	char	*str;

	if (!s)
		return (NULL);
	i = ft_strlen(s) + 1;
	str = ft_calloc(i, sizeof(char));
	if (str == NULL)
		return (ft_memdel(s));
	j = 0;
	while (s[j])
	{
		str[j] = ((char *)s)[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}
/*
int main(void)
{   
    const char *s = "Hello, world!\n";
    char *new_s;

    new_s = ft_strdup(s);
    printf("s: %s\nnew_s: %s\n", s, new_s);

    return (0);
}*/
