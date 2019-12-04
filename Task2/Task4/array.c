#include <malloc.h>
#include <assert.h>
#include "array.h"
#include <memory.h>

array *create() {
    array *array1 = malloc(sizeof(array));
    assert(array1 != NULL);
    array1->data = NULL;
    array1->size = 0;
    return array1;
}

void add(array *arr, void *item) {
    int oldSize = arr->size;
    if (arr->size == 0) {
        arr->data = malloc(sizeof(typeof(item)));
    } else {
        arr->data = realloc(arr->data, sizeof(typeof(item)) * arr->size + sizeof(typeof(arr)));
    }
    arr->data[oldSize] = malloc(sizeof(void *));
    arr->data[oldSize] = memcpy(arr->data[oldSize], item, sizeof(void *));
    arr->size = oldSize + 1;
}

void rem(array *arr, int index) {
    int size = arr->size;
    void *removed = arr->data[index];
    for (int i = index; i < size - 1; ++i) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->data = realloc(arr->data, size * sizeof(void *) - sizeof(void *));
    arr->size = size - 1;
    free(removed);
}

void *get(array *arr, int index) {
    return arr->data[index];
}

void clear(array *arr) {
    for (int i = 0; i < arr->size; ++i) {
        free(arr->data[i]);
    }
    arr->data = NULL;
    arr->size = 0;
}

void set(array *arr, int index, void *item) {
    arr->data[index] = memcpy(arr->data[index], item, sizeof(void *));
}

void insert(array *arr, int index, void *item) {
    int oldSize = arr->size;
    arr->data = realloc(arr->data, sizeof(void *) * (oldSize + 1));
    for (int i = oldSize; i > index; --i) {
        arr->data[i] = arr->data[i - 1];
    }
    arr->data[index] = malloc(sizeof(void *));
    arr->data[index] = memcpy(arr->data[index], item, sizeof(void *));
    arr->size = oldSize + 1;
}

int size(array *arr) {
    return arr->size;
}
