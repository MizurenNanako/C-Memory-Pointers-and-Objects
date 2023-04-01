#pragma once
#include <stdlib.h>

typedef struct ForwardListNode ForwardListNode;
struct ForwardListNode {
    int data;
    ForwardListNode *next;
};

typedef struct {
    ForwardListNode *head;
} ForwardList;

/**
 * @brief Creates a new empty forward list.
 *
 * @return Pointer to the newly created forward list.
 */
ForwardList *forward_list_new();

/**
 * @brief Deletes a forward list and frees the memory used by its nodes.
 *
 * @param list Pointer to the forward list to be deleted.
 */
void forward_list_delete(ForwardList *list);

/**
 * @brief Adds a new element to the front of a forward list.
 *
 * @param list Pointer to the forward list to which the element will be added.
 * @param value The value of the element to be added.
 */
void forward_list_push_front(ForwardList *list, int value);

/**
 * @brief Removes the first element from a forward list.
 *
 * @param list Pointer to the forward list from which the element will be removed.
 */
void forward_list_pop_front(ForwardList *list);

/**
 * @brief Returns a pointer to the first element of a forward list.
 *
 * @param list Pointer to the forward list.
 * @return Pointer to the first element of the forward list, or NULL if the list is empty.
 */
int *forward_list_front(ForwardList *list);

/**
 * @brief Checks if a forward list is empty.
 *
 * @param list Pointer to the forward list.
 * @return 1 if the list is empty, 0 otherwise.
 */
int forward_list_empty(ForwardList *list);

/**
 * @brief Removes all elements from a forward list.
 *
 * @param list Pointer to the forward list to be cleared.
 */
void forward_list_clear(ForwardList *list);

/**
 * @brief Inserts a new element after a given node in a forward list.
 *
 * @param node Pointer to the node after which the new element will be inserted.
 * @param value The value of the new element.
 */
void forward_list_insert_after(ForwardListNode *node, int value);

/**
 * @brief Removes the element after a given node in a forward list.
 *
 * @param node Pointer to the node after which the element will be removed.
 */
void forward_list_erase_after(ForwardListNode *node);

/**
 * @brief Returns the number of elements in a forward list.
 *
 * @param list Pointer to the forward list.
 * @return The number of elements in the forward list.
 */
size_t forward_list_size(ForwardList *list);

/**
 * @brief Merges two sorted forward lists into a single sorted forward list.
 *
 * @param list1 Pointer to the first sorted forward list.
 * @param list2 Pointer to the second sorted forward list.
 */
void forward_list_merge(ForwardList *list1, ForwardList *list2);

/**
 * @brief Removes all elements with a given value from a forward list.
 *
 * @param list Pointer to the forward list.
 * @param value The value to be removed.
 */
void forward_list_remove(ForwardList *list, int value);

/**
 * @brief Reverses the order of the elements in a forward list.
 *
 * @param list Pointer to the forward list to be reversed.
 */
void forward_list_reverse(ForwardList *list);

