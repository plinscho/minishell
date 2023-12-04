/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:16:12 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/04 20:24:01 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expanser.h"

/*
If type = 0 - It's a word (token 1)
if type = 1 - it's a string "" (token 3)
*/
int	check_exp(char *cont, int type)
{
	int	i;

	i = 0;
	while (cont[i] && cont[i + 1])
	{
		if (!type && cont[i] == '\'')
		{
			i++;
			while (cont[i] && cont[i] != '\'')
				i++;
			if (!cont[i])
				break ;
		}
		else if (cont[i] == '$' && check_chr(cont[i + 1]) > 2)
				break ;
		i++;
	}
	if (!cont[i] || !cont[i + 1])
		return (0);
	return (i);
}


int	new_len(t_mini *sh, char *cont)
{
	int	len;
	int	i;
	char	*new;
	
	len = ft_strlen(cont);
	while (*cont)
	{
		i = check_exp(cont, 1);
		if (!i)
			break ;
		new = get_var(&cont[i + 1]);
		if (!new)
			return (-1);
		len = len - ft_strlen(new) - 1 + ft_strlen(ft_get_value(sh, new));
		cont = cont + i + 1;
		new = ft_memdel(new);
	}
	return (len);
}

char *get_var(char *cont)
{
	int	len;
	char	*new;

	len = 0;
	if (!cont)
		return (NULL);
	if (check_chr(cont[len]) == 3)
	{
		new = malloc(2);
		new[0] = cont[0];
		new[1] = '\0';
		return (new);
	}
	while (cont[len] && check_chr(cont[len]) > 2)
		len++;
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	len = -1;
	while (cont[++len] && check_chr(cont[len]) > 2)
		new[len] = cont[len];
	new[len] = '\0';
	return (new);
}