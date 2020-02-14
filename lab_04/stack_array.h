#ifndef _STACK_ARRAY_H_
#define _STACK_ARRAY_H_

int push_array(stackArray_t *const stack, size_t *value);
int pop_array(stackArray_t *const stack);
int print_head_array(FILE *const output_stream, stackArray_t *const stack);
int print_stack_array(FILE *const output_stream, stackArray_t *const stack);

#endif
