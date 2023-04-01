#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"

ForwardListNode *forward_list_node_new(int value) {
    ForwardListNode *node = malloc(sizeof(ForwardListNode));
    if (node) {
        node->data = value;
        node->next = NULL;
    }
    return node;
}

void forward_list_node_delete(ForwardListNode *node) {
    free(node);
}

ForwardList *forward_list_new() {
    ForwardList *list = malloc(sizeof(ForwardList));
    if (list) list->head = NULL;
    return list;
}

void forward_list_delete(ForwardList *list) {
    if (list) {
        ForwardListNode *curr = list->head;
        while (curr) {
            ForwardListNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
        free(list);
    }
}

void forward_list_push_front(ForwardList *list, int value) {
    ForwardListNode *node = forward_list_node_new(value);
    if (node) {
        node->next = list->head;
        list->head = node;
    }
}

void forward_list_pop_front(ForwardList *list) {
    if (list->head) {
        ForwardListNode *temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
}

int *forward_list_front(ForwardList *list) {
    return list->head ? &list->head->data : NULL;
}

int forward_list_empty(ForwardList *list) {
    return list->head == NULL;
}

void forward_list_clear(ForwardList *list) {
    ForwardListNode *curr = list->head;
    while (curr) {
        ForwardListNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    list->head = NULL;
}

void forward_list_insert_after(ForwardListNode *node, int value) {
    ForwardListNode *new_node = forward_list_node_new(value);
    if (new_node) {
        new_node->next = node->next;
        node->next = new_node;
    }
}

void forward_list_erase_after(ForwardListNode *node) {
    if (node->next) {
        ForwardListNode *temp = node->next;
        node->next = node->next->next;
        free(temp);
    }
}

size_t forward_list_size(ForwardList *list) {
    size_t count = 0;
    ForwardListNode *curr = list->head;
    while (curr) {
        count++;
        curr = curr->next;
    }
    return count;
}

void forward_list_merge(ForwardList *list1, ForwardList *list2) {
    if (list1->head == NULL) list1->head = list2->head; 
    else if (list2->head != NULL) {
        ForwardListNode **pp_curr = &list1->head;
        while (*pp_curr) {
            if (list2->head->data < (*pp_curr)->data) {
                ForwardListNode *temp = list2->head;
                list2->head = list2->head->next;
                temp->next = *pp_curr;
                *pp_curr = temp;
            }
            pp_curr = &(*pp_curr)->next;
        }
        *pp_curr = list2->head;
    }
    list2->head = NULL;
}

void forward_list_remove(ForwardList *list, int value) {
    ForwardListNode **pp_curr = &list->head;
    while (*pp_curr) {
        if ((*pp_curr)->data == value) {
            ForwardListNode *temp = *pp_curr;
            *pp_curr = (*pp_curr)->next;
            free(temp);
        } else {
            pp_curr = &(*pp_curr)->next;
        }
    }
}

void forward_list_reverse(ForwardList *list) {
    ForwardListNode *prev = NULL;
    ForwardListNode *curr = list->head;
    while (curr) {
        ForwardListNode *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->head = prev;
}

