/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:09:40 by plinscho          #+#    #+#             */
/*   Updated: 2023/05/16 16:11:06 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	int		j;
	char	*str;

	i = ft_strlen(s) + 1;
	str = ft_calloc(i, sizeof(char));
	if (str == NULL)
		return (NULL);
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
