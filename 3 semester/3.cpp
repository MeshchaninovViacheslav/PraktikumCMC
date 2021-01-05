#include <stdio.h>
#include <stdlib.h>

typedef struct Pair
{
    int key;
    int value;
} Pair;

int
compare_pairs(const void *arg1, const void *arg2)
{
    Pair *a = (Pair *) arg1;
    Pair *b = (Pair *) arg2;
    if (a->key > b->key){
        return 1;
    }
    if (a->key < b->key) {
        return -1;
    }
    if(a->value < b->value) {
        return -1;
    }
    return 1;
}

void
process(Pair *data, size_t size)
{
    int *mas = calloc(size, sizeof(*mas));
    for (size_t i = 0; i < size; i++) {
        mas[i] = data[i].value;
        data[i].value = i;
    }
    qsort(data, size, sizeof(Pair), compare_pairs);
    for (size_t i = 0; i < size; i++) {
        data[i].value = mas[data[i].value];
    }
    free(mas);
}