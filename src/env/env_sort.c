/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:20:18 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/28 19:32:56 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to swap two nodes in the linked list
void swap(t_env *a, t_env *b) 
{
    char *temp = a->env_full;
    a->env_full = b->env_full;
    b->env_full = temp;
}

// Bubble sort function for sorting the linked list alphabetically
void sort_env(t_env *head) 
{
    int swapped = 1;
    t_env *ptr1;
    t_env *lptr = NULL;

    // Check if the linked list is empty or has only one node
    if (head == NULL || head->next == NULL)
        return;

    while (swapped) 
	{
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            // Compare two environment strings and swap if needed
            if (ft_strcmp(ptr1->env_full, ptr1->next->env_full) > 0) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
}


// Function to print the sorted linked list
void print_sorted_env(t_env *head)
{
    t_env *current = head;

    // Iterate through the linked list and print each environment variable
    while (current != NULL) 
	{
        printf("%s\n", current->env_full);
        current = current->next;
    }
}
