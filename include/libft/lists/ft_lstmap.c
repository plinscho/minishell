/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:31:24 by plinscho          #+#    #+#             */
/*   Updated: 2023/05/22 16:59:09 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*content;
	t_list	*head;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		content = f(lst -> content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			ft_lstclear(&head, del);
			free(content);
			return (NULL);
		}
		ft_lstadd_back(&head, new_node);
		lst = lst -> next;
	}
	return (head);
}
