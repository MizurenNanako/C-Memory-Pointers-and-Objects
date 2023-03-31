#include <stdio.h>
#include "forward_list.h"

int cmp(int a, int b) {
    return a < b;
}

int main() {
    ForwardList *list = forward_list_new();

    printf("Adding 3 elements to the front of the list...\n");
    forward_list_push_front(list, 1);
    forward_list_push_front(list, 2);
    forward_list_push_front(list, 3);

    printf("The size of the list is now %lu\n", forward_list_size(list));

    printf("The first element of the list is %d\n", *forward_list_front(list));

    printf("Removing the first element from the list...\n");
    forward_list_pop_front(list);

    printf("The size of the list is now %lu\n", forward_list_size(list));

    printf("Clearing the list...\n");
    forward_list_clear(list);

    printf("The size of the list is now %lu\n", forward_list_size(list));
    printf("The list is%s empty.\n", forward_list_empty(list) ? "" : " not");

    printf("Adding 3 elements to the list...\n");
    forward_list_push_front(list, 3);
    forward_list_push_front(list, 1);
    forward_list_push_front(list, 514);
    forward_list_push_front(list, 2);
    forward_list_push_front(list, 114);

    printf("The current list is: ");
    ForwardListNode *curr = list->head;
    while (curr) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");

    printf("Reversing the list...\n");
    forward_list_reverse(list);

    printf("The reversed list is: ");
    curr = list->head;
    while (curr) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");

    printf("Deleting the list...\n");
    forward_list_delete(list);

    return 0;
}
