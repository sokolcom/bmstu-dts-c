#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <stdio.h>

typedef struct
{
    double time_out;
    int num;
} task_t;


typedef struct
{
    size_t *array;
    int capacity;
    int idx;
} array_t;


// Static array queue realization
typedef struct
{
    int capacity;
    int size;
    int rear;
    int front;
    task_t *array;
} qArray_t;


typedef struct node
{
    task_t task;
    struct node *next;
} node_t;


// Linked list queue realization
typedef struct
{
    int capacity;
    int size;
    node_t *front;
    node_t *rear;
} qList_t;


#endif