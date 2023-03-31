#pragma once
#include <stdlib.h>

typedef struct
{
    int *data;
    size_t size;
    size_t capacity;
} Vector;
/**
 * @brief Allocate memory for a new Vector and initialize its fields.
 *
 * @return A pointer to the new Vector, or NULL if allocation fails.
 */
Vector *vector_new();

/**
 * @brief Deallocate the memory used by a Vector.
 *
 * @param v A pointer to the Vector to be deleted.
 */
void vector_delete(Vector *v);

/**
 * @brief Add an element to the end of a Vector.
 *
 * If the Vector is at capacity, its size is doubled before the new element is added.
 *
 * @param v A pointer to the Vector.
 * @param value The value of the element to be added.
 */
void vector_push_back(Vector *v, int value);

/**
 * @brief Remove the last element from a Vector.
 *
 * If the Vector is empty, this function does nothing.
 *
 * @param v A pointer to the Vector.
 */
void vector_pop_back(Vector *v);

/**
 * @brief Get the number of elements in a Vector.
 *
 * @param v A pointer to the Vector.
 * @return The number of elements in the Vector.
 */
size_t vector_size(Vector *v);

/**
 * @brief Check whether a Vector is empty.
 *
 * @param v A pointer to the Vector.
 * @return 1 if the Vector is empty, 0 otherwise.
 */
int vector_empty(Vector *v);

/**
 * @brief Remove all elements from a Vector.
 *
 * This function does not deallocate any memory used by the Vector.
 *
 * @param v A pointer to the Vector.
 */
void vector_clear(Vector *v);

/**
 * @brief Get the value of an element in a Vector by index.
 *
 * @param v A pointer to the Vector.
 * @param index The index of the element to retrieve.
 * @return The value of the element at the specified index, or -1 if the index is out of bounds.
 */
int vector_at(Vector *v, size_t index);

/**
 * @brief Get a pointer to the first element in a Vector.
 *
 * @param v A pointer to the Vector.
 * @return A pointer to the first element in the Vector, or NULL if the Vector is empty.
 */
int *vector_front(Vector *v);

/**
 * @brief Get a pointer to the last element in a Vector.
 *
 * @param v A pointer to the Vector.
 * @return A pointer to the last element in the Vector, or NULL if the Vector is empty.
 */
int *vector_back(Vector *v);

/**
 * @brief Allocate memory for a Vector with a specified capacity.
 *
 * If the new capacity is less than the current size of the Vector, the size is not changed.
 *
 * @param v A pointer to the Vector.
 * @param new_capacity The desired capacity for the Vector.
 */
void vector_reserve(Vector *v, size_t new_capacity);

/**
 * @brief Change the size of a Vector.
 *
 * If the new size is greater than the current size, new elements are added with the specified default value.
 * If the new size is less than the current size, elements are removed from the end of the Vector.
 * If the new size is equal to the current size, this function does nothing.
 *
 * @param v A pointer to the Vector.
 * @param new_size The desired size for the Vector.
 * @param default_value The default value to use for new elements added to the Vector.
 */
void vector_resize(Vector *v, size_t new_size, int default_value);

/**
 * @brief Remove an element from a Vector by index.
 *
 * If the index is out of bounds, this function does nothing.
 *
 * @param v A pointer to the Vector.
 * @param index The index of the element to remove.
 */
void vector_erase(Vector *v, size_t index);

/**
 * @brief Insert an element into a Vector at a specified index.
 *
 * If the index is out of bounds, this function does nothing.
 * If the Vector is at capacity, its size is doubled before the new element is inserted.
 *
 * @param v A pointer to the Vector.
 * @param index The index at which to insert the new element.
 * @param value The value of the new element to be inserted.
 */
void vector_insert(Vector *v, size_t index, int value);

/**
 * @brief Get a pointer to the data array used by a Vector.
 *
 * @param v A pointer to the Vector.
 * @return A pointer to the data array used by the Vector, or NULL if the Vector is empty.
 */
int *vector_data(Vector *v);

/**
 * @brief Get the capacity of a Vector.
 *
 * @param v A pointer to the Vector.
 * @return The current capacity of the Vector.
 */
int vector_capacity(Vector *v);

/**
 * @brief Reduce the capacity of a Vector to match its size.
 *
 * If the size of the Vector is less than its capacity, its capacity is reduced to match its size.
 *
 * @param v A pointer to the Vector.
 */
void vector_shrink_to_fit(Vector *v);
