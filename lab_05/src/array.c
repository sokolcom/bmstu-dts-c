#include <stdlib.h>
#include <errno.h>

#include "../include/define.h"
#include "../include/struct.h"
#include "../include/array.h"


array_t *create_array(const int capacity)
{
    array_t *array = (array_t *)calloc(1, sizeof(array_t));
    if (!array)
    {
        return NULL;
    }

    array->capacity = capacity;
    array->idx = -1;

    array->array = (size_t *)calloc(array->capacity, sizeof(size_t));

    return array;
}


void print_array(const array_t array)
{
    if (array.idx == -1)
    {
        printf("%s", "Array is empty!\n");
    }
    else
    {
        for (int i = 0; i < array.idx + 1; i++)
        {
            printf("%x ", array.array[i]);
        }
    }

    printf("\n");
}


void free_array(array_t *array)
{
    if (array)
    {
        if (array->array)
        {
            free(array->array);
            free(array);

            errno = OK;

            return;
        }

        free(array);

        errno = OK;
        return;
    }

    errno = MEMORY_ARRAY;
}