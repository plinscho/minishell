/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:20:18 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/02 18:53:22 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to swap content of two nodes in the linked list
void swap(t_env *a, t_env *b) 
{
	char	*value;
	char	*key;
	
	key = a->env_key;
    value = a->env_val;
    a->env_val = b ->env_val;
	a->env_key = b->env_key;
	b->env_val = value;
	b->env_key = key;
}

// Bubble sort function for sorting the linked list alphabetically
void sort_env(t_env *head) 
{
    int swapped = 1;
    t_env *ptr1;
    t_env *lptr = NULL;

    // Check if the linked list is empty or has only one node
    if (head == NULL || head->next == NULL)
        return ;

    while (swapped) 
	{
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            // Compare two environment strings and swap if needed
            if (ft_strcmp(ptr1->env_key, ptr1->next->env_key) > 0) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
}
