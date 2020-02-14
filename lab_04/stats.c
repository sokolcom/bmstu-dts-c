#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>


#include "define.h"
#include "struct.h"

#include "stack_list.h"
#include "stack_array.h"
#include "stats.h"



uint64_t tick()
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );

    uint64_t ticks = ((uint64_t)high << 32) | low;
    return ticks;
}

void print_stats()
{
    // Linked list realization
    stackList_t *stack_list = NULL;

    // Static array realization
    int *array[STACK_SIZE];
    stackArray_t stack_array;
    stack_array.start = array;
    stack_array.end = array + STACK_SIZE - 1;
    stack_array.head = array - 1;


    uint64_t start = 0, finish = 0;
    int elements_amount = 0;

    printf("Enter size of the stack (less than 1000 elements):\n");
    int code = scanf("%d", &elements_amount);
    while ((code != VALID_INPUT) || (elements_amount < 1) || (elements_amount > STACK_SIZE))
    {
        printf("Error!\nInvalid size entered!\nTryy again please!\n");
        code = scanf("%d", &elements_amount);
    }

    printf("Time execution:\n");

    // Pushing the element
    start = tick();
    for (size_t i = 0; i < elements_amount; i++)
    {
        size_t *p = (size_t *)(i + 1);
        push_array(&stack_array, p);
    }
    finish = tick(); 
    printf("\t*ARRAY: push elements - %.12lf seconds\n", (double)(finish - start) / Hz);
    
    start = tick();
    for (int i = 0; i < elements_amount; i++)
    {
        push_list(&stack_list, NULL);   
    }
    finish = tick();
    printf("\t*LIST: push elements -  %.12lf seconds\n", (double)(finish - start) / Hz);


    // Clear up the stack
    start = tick();
    for (int i = 0; i < elements_amount; i++)
    {
        pop_array(&stack_array);
    }
    finish = tick();
    printf("\t*ARRAY: pop elements -  %.12lf seconds\n", (double)(finish - start) / Hz);

    start = tick();
    for (int i = 0; i < elements_amount; i++)
    {
        pop_list(&stack_list);
    }
    finish = tick();
    printf("\t*LIST: pop elements -   %.12lf seconds\n", (double)(finish - start) / Hz);    

    printf("\nMemory usage:\n");
    printf("\tStatic array: %" PRId64 " bytes\n", sizeof(int *) * elements_amount);
    printf("\tLinked list:  %" PRId64 " bytes\n", sizeof(stackList_t) * elements_amount);



    free_stack_list(stack_list);
}