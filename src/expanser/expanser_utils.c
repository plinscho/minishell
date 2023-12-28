/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:16:12 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/27 22:22:59 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
If type = 1 - It's a word (token 1) 0
if type = 3 - it's a string "" (token 3) 1
if type = 2 - it's a string '' (token 3) - no expansion
Q is always starting -1 - its a flag to check if we are in the double quotes. 
q < 0 - no open quotes
q > 1 - you are inside open quotes
*/
int	check_exp(char *cont, int type, int q)
{
	int	i;

	i = 0;
	if (!cont || (type != 1 && type != 3))
		return (-1);
	while (cont[i] && cont[i + 1])
	{
		if (type == 1 && cont[i] == '\"')
			q *= -1;
		if (type == 1 && q < 0 && cont[i] == '\'')
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
		return (-1);
	return (i);
}

/*
If type = 1 - It's a word (token 1) 0
if type = 3 - it's a string "" (token 3) 1
*/
int	new_len(t_mini *sh, char *cont, int type)
{
	int		len;
	int		i;
	char	*new;
	char	*val;

	len = ft_strlen(cont);
	while (*cont)
	{
		i = check_exp(cont, type, -1);
		if (i < 0)
			break ;
		new = get_var(&cont[i + 1]);
		if (!new)
			return (-1);
		val = check_value(sh, new);
		len = len - ft_strlen(new) - 1 + ft_strlen(val);
		if (*new == '?')
			val = ft_memdel(val);
		cont = cont + i + 1;
		new = ft_memdel(new);
	}
	return (len);
}

char	*get_var(char *cont)
{
	int		len;
	char	*new;

	len = 0;
	if (!cont)
		return (NULL);
	if (check_chr(cont[len]) == 3)
	{
		new = malloc(2);
		if (!new)
			return (NULL);
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

char	*check_value(t_mini *sh, char *var)
{
	if (!var)
		return (NULL);
	if (*var == '?')
	{
		sh->exp->alloc = 1;
		return (ft_itoa(sh->exit));
	}
	else if (*var == '0')
		return ("kebab\0");
	else
		return (ft_get_value(sh, var));
}

/*
flag = 0 - there is no open quotes
fflag = 1 - there is an open quote
*/
int	check_file_exp(char *str)
{
	int		i;
	int		flag;
	char	q;

	i = -1;
	flag = 0;
	q = ' ';
	while (str[++i])
	{
		if (str[i] == ' ' && !flag)
			return (1);
		if (check_chr(str[i]) == 2 && !flag)
		{
			flag++;
			q = str[i];
		}
		else if (flag && str[i] == q)
			flag = 0;
	}
	return (0);
}
