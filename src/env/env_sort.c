/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:20:18 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/09 16:30:59 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_sort_print(t_env *env)
{
	t_env	*tmp;
	char	*tmp_name;
	char	*tmp_value;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->next != NULL)
		{
			if (ft_strcmp(tmp->env_key, tmp->next->env_key) > 0)
			{
				tmp_name = tmp->env_key;
				tmp_value = tmp->env_val;
				tmp->env_key = tmp->next->env_key;
				tmp->env_val = tmp->next->env_val;
				tmp->next->env_key = tmp_name;
				tmp->next->env_val = tmp_value;
				tmp = env;
			}
		}
		tmp = tmp->next;
	}
}

void	sort_env(t_env *head)
{
	t_env	*head_bk;

	head_bk = head;
	if (!head_bk)
		return ;
	print_sort_print(head);
	head = head_bk;
}


/*
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

t_env   *env_new_node(t_env *original)
{
	// Create a new node
	t_env *new_elem; 
	
	new_elem = (t_env *)malloc(sizeof(t_env));
	if (!new_elem)
	{
		// Handle memory allocation error if needed
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

        // Copy the contents of the original node to the new node
        new_elem->env_key = original->env_key; // Assuming you don't need a deep copy for strings
        new_elem->env_val = original->env_val; // Assuming you don't need a deep copy for strings
        new_elem->next = NULL;
	return (new_elem);
}

// returns the head of the new list
// Function to create a copy of a linked list
t_env *list_copy(t_env *og) 
{
	t_env *new_head = NULL; // Head of the new list
	t_env *new_node = NULL; // Pointer to the last node in the new list
	t_env *tmp = og;        // Temporary pointer for iterating through the original list

	// Iterate through the original list
	while (tmp) 
	{
        // Create a new node
        new_node = env_new_node(tmp);
        // Update the new list
        if (!new_head)
        {
            // If the new list is empty, set the new node as both the head and the first node
            new_head = new_node;
            new_node = new_head->next;
        }
		else
			new_node = new_node->next;

        // Move to the next node in the original list
        tmp = tmp->next;
    }
    return (new_head);
}

// Bubble sort function for sorting the linked list alphabetically
void sort_env(t_env *head) 
{
    int     swapped = 1;
    t_env   *copy;
    t_env   *ptr1;
    t_env   *lptr = NULL;

    copy = list_copy(head);
    // Check if the linked list is empty or has only one node
    if (head == NULL || head->next == NULL || !copy)
    {
        ft_putendl_fd("Error in sorting", 2);
        return ;
    }
    while (swapped) 
	{
        swapped = 0;
        ptr1 = copy;
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
	printf("\n\nTHIS IS THE COPY BEFORE FREEING\n\n");
	print_env(copy, NULL);
	free_env_lst(copy);
}
*/