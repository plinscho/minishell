/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:18:50 by plinscho          #+#    #+#             */
/*   Updated: 2023/09/08 20:47:41 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
//	#include <stdio.h>
/*
int main()
{
	int		fd, fd2, fd3;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	fd2 = open("test_2.txt", O_RDONLY);
	fd3 = open("test_3.txt", O_RDONLY);

	printf("opening file...\n");
	while ((line = get_next_line(fd)))
		printf("%s", line);

	while ((line = get_next_line(fd2)))
			printf("%s", line);

	while ((line = get_next_line(fd3)))
		printf("%s", line);

	close(fd);
	close(fd2);
	close(fd3);
	return (0);
}
*/
void	polish_list(t_line **list)
{
	t_line	*last_node;
	t_line	*clean_node;
	int		i;
	int		k;
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_line));
	if (!buff || !clean_node)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buff[i] != '\0' && last_node->str_buff[i] != '\n')
		i++;
	while (last_node->str_buff[i] && last_node->str_buff[++i] != '\0')
		buff[k++] = last_node->str_buff[i];
	buff[k] = '\0';
	clean_node->str_buff = buff;
	clean_node->next = NULL;
	dealloc(list, clean_node, buff);
}

char	*get_line(t_line *list)
{
	int		str_len;
	char	*next_str;

	if (!list)
		return (NULL);
	str_len = len_to_new_line(list);
	next_str = malloc(str_len + 1);
	if (!next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void	append(t_line **list, char *buffer)
{
	t_line	*new_node;
	t_line	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_line));
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buff = buffer;
	new_node->next = NULL;
}

void	create_list(t_line **list, int fd)
{
	int		bytes_read;
	char	*buffer;

	while (!found_new_line(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		append(list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_line	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_line(list);
	polish_list(&list);
	return (next_line);
}
