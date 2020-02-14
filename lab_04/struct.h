#ifndef _STRUCT_H_
#define _STRUCT_H_

#define STACK_SIZE 1000

// Array stack realization
typedef struct
{
    int **start;
    int **end;
    int **head;
} stackArray_t;


// Linked list stack realization
struct stackList_t
{
    size_t *value;
    struct stackList_t *next;
};

typedef struct stackList_t stackList_t;

#endif
