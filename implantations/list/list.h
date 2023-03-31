#pragma once

#include <stdbool.h>

typedef unsigned long long int ulli;

/**
 * A node in a doubly linked list.
 */
struct ListNode
{
    struct ListNode *_next;     // A pointer to the next node in the list.
    struct ListNode *_previous; // A pointer to the previous node in the list.
    void *__data;               // A pointer to the data stored in the node, cast to void *.
};

/**
 * @brief A linked list data structure.
 *
 * The `List` struct consists of a `_sentinel` node that serves as the head and tail of the list, a `_visited`
 * node that is used to keep track of the last visited node, the `_size` of the list, and the `_at_visit` index
 * of the `_visited` node.
 *
 * @note
 * The `_sentinel` node is used to simplify the implementation of the list, and is not meant to contain any data.
 * The `_visited` node is used to improve the performance of repeated accesses to adjacent nodes in the list.
 * The `_at_visit` index is used to store the index of the `_visited` node, and is updated whenever the `_visited`
 * node changes.
 */
typedef struct
{
    struct ListNode *_sentinel; // The head and tail of the list.
    struct ListNode *_visited;  // The last visited node in the list.
    ulli _size;                 // The number of nodes in the list.
    ulli _at_visit;             // The index of the last visited node.
} List;

/**
 * @brief Creates a new empty linked list.
 *
 * @return A pointer to the newly created list.
 */
List *list_new();

/**
 * @brief Returns the value of the first element in the list.
 *
 * If the list is empty, the function will print an error message to `stderr`
 * and exit the program with an error code.
 *
 * @param list A pointer to the list.
 * @return The value of the first element in the list.
 */
void *list_front(List *list);

/**
 * @brief Returns the value of the last element in the list.
 *
 * If the list is empty, the function will print an error message to `stderr`
 * and exit the program with an error code.
 *
 * @param list A pointer to the list.
 * @return The value of the last element in the list.
 */
void *list_back(List *list);

/**
 * @brief Returns the number of elements in the list.
 *
 * @param list A pointer to the list.
 * @return The number of elements in the list.
 */
ulli list_size(List *list);

/**
 * @brief Returns a boolean indicating whether the list is empty or not.
 *
 * @param list A pointer to the list.
 * @return 1 if the list is empty, 0 otherwise.
 */
bool list_empty(List *list);

/**
 * @brief Adds a new element with the given value to the back of the linked list.
 *
 * @param list Pointer to the list.
 * @param value The value of the element to add to the list.
 */
void list_push_back(List *list, void *value);

/**
 * @brief Adds a new element with the given value to the front of the linked list.
 *
 * @param list Pointer to the list.
 * @param value The value of the element to add to the list.
 */
void list_push_front(List *list, void *value);

/**
 * @brief Retrieves the value of the element at the specified index in the linked list.
 *
 * @param list Pointer to the list.
 * @param index The index of the element to retrieve.
 *
 * @return The value of the element at the specified index.
 *
 * @note This function may affect the `_visited` pointer.
 */
void *list_at(List *list, ulli index);

/**
 * @brief Removes the element at the specified index from the linked list.
 *
 * @param list Pointer to the list.
 * @param index The index of the element to remove.
 * @return void* Pointer to the removed element.
 *
 * @note This function may affect the `_visited` pointer.
 */
void *list_remove(List *list, ulli index);

/**
 * @brief Removes and returns the last element of the linked list.
 *
 * @param list Pointer to the list.
 *
 * @return void* Pointer to the removed element.
 *
 * @note This function may affect the `_visited` pointer.
 */
void *list_pop_back(List *list);

/**
 * @brief Removes and returns the first element of the linked list.
 *
 * @param list Pointer to the list.
 *
 * @return void* Pointer to the removed element.
 *
 * @note This function may affect the `_visited` pointer.
 */
void *list_pop_front(List *list);

/**
 * @brief Removes all elements from the list.
 * 
 * @param list The list to clear.
 * @param deleter The function pointer to delete the data of each node in the list.
 */
void list_clear(List *list, void (*deleter)(void *));

/**
 * @brief Deletes the list itself.
 * 
 * @param list The list to delete.
 * @param deleter The function pointer to delete the data of each node in the list.
 */
void list_delete(List *list, void (*deleter)(void *));
