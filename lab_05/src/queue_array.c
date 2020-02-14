#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#include "../include/define.h"
#include "../include/struct.h"
#include "../include/queue_array.h"



qArray_t *create_qarray(const int capacity)
{
    qArray_t *queue = (qArray_t *)calloc(1, sizeof(qArray_t));
    if (!queue)
    {
        return NULL;
    }

    queue->size = 0;
    queue->capacity = capacity;

    queue->front = 0;
    queue->rear = capacity - 1;

    queue->array = (task_t *)calloc(queue->capacity, sizeof(task_t));
    if (!queue->array)
    {
        free(queue);
        return NULL;
    }

    return queue;
}


int is_overflow_qarray(qArray_t *const queue)
{
    return (queue->size == queue->capacity);
}


int is_empty_qarray(qArray_t *const queue)
{
    return (queue->size == 0);
}


void add_qarray(qArray_t *const queue, const task_t task)
{
    if (is_overflow_qarray(queue))
    {
        errno = QUEUE_OVERFLOW;
        return;
    }
    else
    {    
        queue->size++;
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->array[queue->rear] = task;
    }
}


task_t out_qarray(qArray_t *const queue)
{
    if (is_empty_qarray(queue))
    {
        errno = QUEUE_EMPTY;
        return;
    }

    task_t task = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return task;
}


void free_qarray(qArray_t *queue)
{
    if (queue)
    {
        if (queue->array)
        {
            free(queue->array);
            free(queue);
            errno = OK;
            return;
        }

        free(queue);
        errno = OK;
        return;
    }
}