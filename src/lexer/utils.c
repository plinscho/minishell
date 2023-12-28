/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:49:55 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/24 19:43:12 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
This function is a substring that trims quotes 
(returns the string without quotes) 
*/
char	*ft_substr_quotes(char *s, char q, int len, int i)
{
	char	*m;
	int		new_len;

	new_len = len;
	while (++i < (len - 1) && s[i + 1])
	{
		if (s[i] == q)
			new_len--;
	}
	i = 0;
	m = (char *) malloc(new_len + 1);
	if (m == 0)
		return (NULL);
	while (i < new_len && s[i])
	{
		if (s[i] == q)
			s++;
		else
		{
			m[i] = s[i];
			i++;
		}
	}
	m[i] = '\0';
	return (m);
}

/* 
This function checks if a char is a redirection (< OR > OR |) or not:
1. return (1) - the char is NOT a redirection, it's a simple char
2. return (0) - the char is a redirection or space
3. return (2) - the char is a quote (for expansion)
4. return (3) - the char is a number (for expansion)
4. return (4) - the char is a character (for expansion)
*/
int	check_chr(char c)
{
	if (c == 34 || c == 39)
		return (2);
	if ((c > 47 && c < 58) || c == 63)
		return (3);
	else if ((c > 64 && c < 91) || (c > 96 && c < 123) || c == 95)
		return (4);
	else if ((c > 32 && c < 60) || c == '=' || (c > 62 && c < 124) || \
	(c > 124 && c < 127))
		return (1);
	return (0);
}

/* 
This function receives an double array and a flag that means:
1. flag=0 - all the strings in the array are allocated, so it frees them
2. flag=1 - the strings in the array are NOT allocated, 
			it only iquals them to null
*/
char	**arr_clean(char **cmd, int flag)
{
	int		i;

	i = 0;
	while (cmd && *cmd && cmd[i])
	{
		if (!flag)
			cmd[i] = ft_memdel(cmd[i]);
		else
			cmd[i] = NULL;
		i++;
	}
	if (cmd)
		free(cmd);
	return (NULL);
}

/* 
This function receives 2 strings and returns the lenth of the longer one 
*/
int	ft_longer(char *str, char *key)
{
	int	len;

	if (ft_strlen(str) > ft_strlen(key))
		len = ft_strlen(str);
	else
	{
		len = ft_strlen(key);
	}
	return (len);
}

char	*ft_smart_join(char *s1, char *s2, char *s3)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!(s1 && s2 && s3))
		return (0);
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!new)
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	while (s2[j])
		new[i++] = s2[j++];
	j = 0;
	while (s3[j])
		new[i++] = s3[j++];
	new[i] = '\0';
	return (new);
}
