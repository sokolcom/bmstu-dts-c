#include <stdio.h>

#include "define.h"
#include "struct.h"

#include "stack_array.h"


// Check if stack empty
static int check_empty(stackArray_t *const stack)
{
    if (stack->head == stack->start - 1)
    {
        return EMPTY;
    }

    return NOT_EMPTY;
}


// Add element into the stack
int push_array(stackArray_t *const stack, size_t *value)
{
    if (stack->head == stack->end)
        return STACK_OVERFLOW_ERROR;

    int *pointer = NULL;

    if (value == NULL)
    {
        printf("Enter adress: ");
        while (scanf("%p", &pointer) != VALID_INPUT)
            printf("Error!\nInvalid memory adress entered!\nTry again please!\n");
    }
    else
    {
        pointer = (int *) value;
    }

    (stack->head)++;
    *(stack->head) = pointer;
    return SUCCESS;
}


// Pop element out of the stack
int pop_array(stackArray_t *const stack)
{
    if (check_empty(stack) == EMPTY)
        return EMPTY_STACK_ERROR;

    (stack->head)--;

    return SUCCESS;
}


// Print head element
int print_head_array(FILE *const output_stream, stackArray_t *const stack)
{
    if (check_empty(stack) == EMPTY)
        return EMPTY_STACK_ERROR;

    fprintf(output_stream, "Stack head:\n");
    fprintf(output_stream, "\t%p\n", *(stack->head));

    return SUCCESS;
}


// Print complete stack
int print_stack_array(FILE *const output_stream, stackArray_t *const stack)
{
    if (check_empty(stack) == EMPTY)
        return EMPTY_STACK_ERROR;

    fprintf(output_stream, "Stack head:\n");
    for (int **ptr = stack->head; ptr >= stack->start; ptr--)
    {
        fprintf(output_stream, "\t%p\n", *ptr);
    }

    return SUCCESS;
}
