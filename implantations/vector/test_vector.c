#include <stdio.h>
#include "vector.h"

int main() {
    Vector *v = vector_new();
    if (!v) {
        printf("Failed to create vector\n");
        return -1;
    }

    // Add some elements to the vector
    vector_push_back(v, 1);
    vector_push_back(v, 2);
    vector_push_back(v, 3);
    vector_push_back(v, 4);
    vector_push_back(v, 5);

    // Print the size and capacity of the vector
    printf("Vector size: %zu\n", vector_size(v));
    printf("Vector capacity: %d\n", vector_capacity(v));

    // Print the contents of the vector
    printf("Vector contents: ");
    for (size_t i = 0; i < vector_size(v); i++) {
        printf("%d ", vector_at(v, i));
    }
    printf("\n");

    // Remove the last element from the vector
    vector_pop_back(v);

    // Print the updated contents of the vector
    printf("Vector contents after pop_back: ");
    for (size_t i = 0; i < vector_size(v); i++) {
        printf("%d ", vector_at(v, i));
    }
    printf("\n");

    // Insert a new element at index 2
    vector_insert(v, 2, 6);

    // Print the updated contents of the vector
    printf("Vector contents after insert: ");
    for (size_t i = 0; i < vector_size(v); i++) {
        printf("%d ", vector_at(v, i));
    }
    printf("\n");

    // Resize the vector to a smaller size
    vector_resize(v, 3, 0);

    // Print the updated contents of the vector
    printf("Vector contents after resize: ");
    for (size_t i = 0; i < vector_size(v); i++) {
        printf("%d ", vector_at(v, i));
    }
    printf("\n");

    // Clear the vector
    vector_clear(v);

    // Print the size and capacity of the vector after clearing
    printf("Vector size after clear: %zu\n", vector_size(v));
    printf("Vector capacity after clear: %d\n", vector_capacity(v));

    vector_delete(v);
    return 0;
}
