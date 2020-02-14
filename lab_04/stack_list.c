#include <stdio.h>
#include <stdlib.h>

#include "define.h"
#include "struct.h"

#include "stack_list.h"


static int check_empty(stackList_t *head)
{
    if (head == NULL)
    {
        return EMPTY;
    }

    return NOT_EMPTY;
}


int push_list(stackList_t **head, size_t *memory)
{
    stackList_t *temp = calloc(1, sizeof(stackList_t));

    if (!temp)
    {
        return ALLOCATE_NODE_ERROR;
    }

    temp->next = *head;
    if (memory == NULL)
    {
        temp->value = (size_t *) &(temp->value);
    }
    else
    {
        temp->value = memory;
    }
    *head = temp;

    return SUCCESS;
}


size_t *pop_list(stackList_t **head)
{
    size_t *delete_memory = NULL; 

    if (*head == NULL)
    {
        return NULL;
    }    

    delete_memory = (*head)->value;
    stackList_t *temp = *head;
    *head = (*head)->next;
    free(temp); 

    return delete_memory;
}


// Print head element
int print_head_list(FILE *const output_stream, stackList_t *head)
{
    if (check_empty(head) == EMPTY)
        return EMPTY_STACK_ERROR;

    fprintf(output_stream, "Stack head:\n");
    fprintf(output_stream, "\t%p\n", head->value);
    return SUCCESS;
}


// Print complete stack
int print_stack_list(FILE *const output_stream, stackList_t *head)
{
    if (check_empty(head) == EMPTY)
        return EMPTY_STACK_ERROR;

    fprintf(output_stream, "Stack head:\n");
    while (head)
    {
        fprintf(output_stream, "\t%p\n", head->value);
        head = head->next;
    }    

    return SUCCESS;
}


// Free linked list 
void free_stack_list(stackList_t *head)
{
    stackList_t *temp_node = NULL;

    while (head)
    {
        temp_node = head->next;
        free(head);
        head = temp_node;
    }
}


// Print freed memory
int print_freed_memory(FILE* output_stream, stackList_t *head)
{
    if (head == NULL)
        return NO_FREED_ERROR;

    fprintf(output_stream, "From the last freed to the first:\n");
    while (head)
    {
        fprintf(output_stream, "\t%p\n", head->value);
        head = head->next;
    }    

    return SUCCESS;
}