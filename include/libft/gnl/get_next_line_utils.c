/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:24:37 by plinscho          #+#    #+#             */
/*   Updated: 2023/09/08 20:47:07 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	dealloc(t_line **list, t_line *clean_node, char *buff)
{
	t_line	*tmp;

	if ((*list) == NULL)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str_buff);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node->str_buff[0])
		*list = clean_node;
	else
	{
		free(buff);
		free(clean_node);
	}
}

int	found_new_line(t_line *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buff[i] && i < BUFFER_SIZE)
		{
			if (list->str_buff[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

t_line	*find_last_node(t_line *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	len_to_new_line(t_line *list)
{
	int	i;
	int	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buff[i])
		{
			if (list->str_buff[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

void	copy_str(t_line *list, char *str)
{
	int	i;
	int	k;

	if (!list)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->str_buff[i])
		{
			if (list->str_buff[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->str_buff[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}
