#include <errno.h>

#include "../include/define.h"
#include "../include/struct.h"
#include "../include/queue_list.h"



node_t *create_qnode(const task_t task)
{
    node_t *node = (node_t *)calloc(1, sizeof(node_t));
    if (!node)
    {
        return NULL;
    }

    node->task.time_out = task.time_out;
    node->task.num = task.num;
    node->next = NULL;

    return node;
}


qList_t *create_qlist(const int capacity)
{
    qList_t *queue = (qList_t *)calloc(1, sizeof(qList_t));
    if (!queue)
    {
        return NULL;
    }

    queue->size = 0;
    queue->capacity = capacity;
    queue->rear = NULL;
    queue->front = NULL;

    return queue;
}


int is_overflow_qlist(qList_t *const queue)
{
    return (queue->size == queue->capacity);
}


int is_empty_qlist(qList_t *const queue)
{
    return (queue->rear == NULL);
}


void add_qlist(qList_t *const queue, const task_t task)
{
    node_t *node = create_qnode(task);

    if (is_overflow_qlist(queue))
    {
        errno = QUEUE_OVERFLOW;
        return;
    }

    if (queue->rear == NULL)
    {
        queue->front = node;
        queue->rear = node;
        queue->size++;
        return;
    }

    queue->rear->next = node;
    queue->rear = node;
    queue->size++;
}


task_t out_qlist(qList_t *const queue, array_t *const memory)
{   
    if (queue->front == NULL)
    {
        errno = QUEUE_EMPTY;
        return;
    }

    node_t *node = queue->front; 
    memory->array[++memory->idx] = node;

    task_t data = node->task;

    if (queue->front == queue->rear)
    {
        queue->rear = NULL;
        queue->front = NULL;
    }
    else
    {
        queue->front = queue->front->next;
    }

    free(node);
    queue->size--;

    return data;
}


void free_qlist(qList_t *queue, array_t *const memory)
{
    if (queue == NULL)
    {
        return;
    }

    while (!is_empty_qlist(queue))
    {
        out_qlist(queue, memory);
    }
    free(queue);
}


// Check queue's rear address existance in `memory` array and delete if so
int check_rear(qList_t *queue, array_t *memory)
{
    int is_found = 0;
    size_t top = queue->rear;

    for (int i = 0; i < memory->idx; i++)
    {
        if (top == memory->array[i])
        {
            is_found = 1;

            for (int j = i; j < memory->idx - 1; j++)
            {
                size_t temp = memory->array[j];
                memory->array[j] = memory->array[j + 1];
                memory->array[j + 1] = temp;
            }
        }
    }

    if (is_found)
    {
        memory->idx--;
    }

    return is_found;
}
