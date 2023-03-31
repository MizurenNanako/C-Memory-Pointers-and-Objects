#include "vector.h"


Vector *vector_new() {
    Vector *v = (Vector *) malloc(sizeof(Vector));
    if (!v) {
        return NULL;
    }
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return v;
}

void vector_delete(Vector *v) {
    if (!v) {
        return;
    }
    free(v->data);
    free(v);
}

void vector_push_back(Vector *v, int value) {
    if (!v) {
        return;
    }
    if (v->size == v->capacity) {
        size_t new_capacity = v->capacity == 0 ? 1 : v->capacity * 2;
        int *new_data = (int *) realloc(v->data, new_capacity * sizeof(int));
        if (!new_data) {
            return;
        }
        v->data = new_data;
        v->capacity = new_capacity;
    }
    v->data[v->size] = value;
    v->size++;
}

void vector_pop_back(Vector *v) {
    if (!v || v->size == 0) {
        return;
    }
    v->size--;
}

size_t vector_size(Vector *v) {
    if (!v) {
        return 0;
    }
    return v->size;
}

int vector_empty(Vector *v) {
    if (!v || v->size == 0) {
        return 1;
    }
    return 0;
}

void vector_clear(Vector *v) {
    if (!v) {
        return;
    }
    v->size = 0;
}

int vector_at(Vector *v, size_t index) {
    if (!v || index >= v->size) {
        return -1;
    }
    return v->data[index];
}

int *vector_front(Vector *v) {
    if (!v || v->size == 0) {
        return NULL;
    }
    return &v->data[0];
}

int *vector_back(Vector *v) {
    if (!v || v->size == 0) {
        return NULL;
    }
    return &v->data[v->size - 1];
}

void vector_reserve(Vector *v, size_t new_capacity) {
    if (!v || new_capacity <= v->capacity) {
        return;
    }
    int *new_data = (int *) realloc(v->data, new_capacity * sizeof(int));
    if (!new_data) {
        return;
    }
    v->data = new_data;
    v->capacity = new_capacity;
}

void vector_resize(Vector *v, size_t new_size, int default_value) {
    if (!v) {
        return;
    }
    if (new_size > v->size) {
        if (new_size > v->capacity) {
            size_t new_capacity = new_size;
            int *new_data = (int *) realloc(v->data, new_capacity * sizeof(int));
            if (!new_data) {
                return;
            }
            v->data = new_data;
            v->capacity = new_capacity;
        }
        for (size_t i = v->size; i < new_size; i++) {
            v->data[i] = default_value;
        }
    }
    v->size = new_size;
}

void vector_erase(Vector *v, size_t index) {
    if (!v || index >= v->size) {
        return;
    }
    for (size_t i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i+1];
    }
    v->size--;
}

void vector_insert(Vector *v, size_t index, int value) {
    if (!v || index > v->size) {
        return;
    }
    if (v->size == v->capacity) {
        size_t new_capacity = v->capacity == 0 ? 1 : v->capacity * 2;
        int *new_data = (int *) realloc(v->data, new_capacity * sizeof(int));
        if (!new_data) {
            return;
        }
        v->data = new_data;
        v->capacity = new_capacity;
    }
    for (size_t i = v->size; i > index; i--) {
        v->data[i] = v->data[i-1];
    }
    v->data[index] = value;
    v->size++;
}

int *vector_data(Vector *v) {
    if (!v) {
        return NULL;
    }
    return v->data;
}

int vector_capacity(Vector *v) {
    if (!v) {
        return 0;
    }
    return v->capacity;
}

void vector_shrink_to_fit(Vector *v) {
    if (!v) {
        return;
    }
    if (v->size < v->capacity) {
        int *new_data = (int *) realloc(v->data, v->size * sizeof(int));
        if (!new_data) {
            return;
        }
        v->data = new_data;
        v->capacity = v->size;
    }
}