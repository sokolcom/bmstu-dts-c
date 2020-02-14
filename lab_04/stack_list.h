#ifndef _STACK_LIST_H_
#define _STACK_LIST_H_

int push_list(stackList_t **head, size_t *memory);
size_t *pop_list(stackList_t **head);
int print_head_list(FILE *const output_stream, stackList_t *head);
int print_stack_list(FILE *const output_stream, stackList_t *head);

void free_stack_list(stackList_t *head);

int print_freed_memory(FILE* output_stream, stackList_t *head);

#endif
