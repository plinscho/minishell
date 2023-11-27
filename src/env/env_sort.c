/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:20:18 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/27 20:20:35 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to swap two nodes in the linked list
void swap(t_env *a, t_env *b) {
    char *temp = a->env_full;
    a->env_full = b->env_full;
    b->env_full = temp;
}

// Bubble sort function for sorting the linked list alphabetically
void sort_env(t_env *head) {
    int swapped;
    t_env *ptr1;
    t_env *lptr = NULL;

    // Check if the linked list is empty or has only one node
    if (head == NULL || head->next == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            // Compare two environment strings and swap if needed
            if (strcmp(ptr1->env_full, ptr1->next->env_full) > 0) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Function to print the sorted linked list
void print_sorted_env(t_env *head) {
    t_env *current = head;

    // Iterate through the linked list and print each environment variable
    while (current != NULL) {
        printf("%s\n", current->env_full);
        current = current->next;
    }
}

// Function to add a new node to the linked list
t_env *add_node(t_env *head, char *env_full) {
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    if (new_node == NULL) {
        // Handle memory allocation error
        exit(EXIT_FAILURE);
    }

    new_node->env_full = strdup(env_full); // Duplicate the string
    new_node->next = head;

    return new_node;
}