
typedef struct array {
    void **data;
    int size;
} array;

array *create();

void add(array *arr, void *item);

void rem(array *arr, int index);

void *get(array *arr, int index);

void clear(array *arr);

void insert(array *arr, int index, void *item);

void set(array *arr, int index, void *item);

int size(array *arr);

