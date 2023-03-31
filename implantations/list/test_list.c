#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Define a custom deleter function for the list_delete() function
void custom_deleter(void *data)
{
    printf("Deleting data: %d\n", *(int *)data);
}

int main()
{
    List *list = list_new();
    int data[] = {1, 1, 4, 5, 1, 4};

    // Add elements to the list
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i)
    {
        list_push_back(list, &data[i]);
    }

    // Print the list
    printf("List elements: ");
    for (int i = 0; i < list_size(list); ++i)
    {
        printf("%d ", *(int *)list_at(list, i));
    }
    printf("\n");

    // Remove an element from the list
    printf("Removed 2nd element.\n");
    list_remove(list, 2);

    // Print the updated list
    printf("Updated list elements: ");
    for (int i = 0; i < list_size(list); ++i)
    {
        printf("%d ", *(int *)list_at(list, i));
    }
    printf("\n");

    // Delete the first and last elements from the list
    int *first = (int *)list_pop_front(list);
    int *last = (int *)list_pop_back(list);
    printf("Deleted first element: %d\n", *first);
    printf("Deleted last element: %d\n", *last);

    // Print the updated list
    printf("Updated list elements: ");
    for (int i = 0; i < list_size(list); ++i)
    {
        printf("%d ", *(int *)list_at(list, i));
    }
    printf("\n");

    // Clear the list
    list_clear(list, custom_deleter);

    // Print the updated list size
    printf("List size: %llu\n", list_size(list));

    // Add elements to the list
    for (int i = 1; i < sizeof(data) / sizeof(data[0]); ++i)
    {
        list_push_back(list, &data[i - 1]);
        list_push_back(list, &data[i]);
    }

    // Print the updated list size
    printf("List size: %llu\n", list_size(list));

    printf("List elements: ");
    for (int i = 0; i < list_size(list); ++i)
    {
        printf("%d ", *(int *)list_at(list, i));
    }
    printf("\n");

    // Delete the list
    list_delete(list, custom_deleter);

    return 0;
}
