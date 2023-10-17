/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:38:31 by plinscho          #+#    #+#             */
/*   Updated: 2023/09/28 17:26:10 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_words(const char *str, char c)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			count++;
		while (*str && *str != c)
			str++;
	}
	return (count);
}

static char	**free_grid(char **grid, size_t str_number)
{
	while (str_number-- > 0)
	{
		free(grid[str_number]);
	}
	free(grid);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	str_number;	
	char	*start;
	char	**str_grid;

	str_grid = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!str_grid)
		return (NULL);
	str_number = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			start = (char *)s;
			while (*s && *s != c)
				s++;
			str_grid[str_number] = ft_substr(start, 0, s - start);
			if (!str_grid[str_number])
				return (free_grid(str_grid, str_number));
			str_number++;
		}
	}
	str_grid[str_number] = NULL;
	return (str_grid);
}
