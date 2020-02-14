#include <stdio.h>

#include "define.h"

#include "menu.h"


// About program
void welcome()
{
    printf("BASIC STACK v1.0\n\n\n");
    printf("About:\n");
    printf("This program realizes stack in two different data structures:\n"
           "\t* static array (1000 elements);\n"
           "\t* linked list.\n\n"
           "Each element of the linked list is a memory adress where its contains.\n"
           "Each element of the static array is also a memory adress, but entered\n"
           "by the user.\n\n");
    printf("The program can push/pop elements into/out of a stack, print current\n"
           "state of the stack.\n\n\n\n");
}


// Menu commands
void menu_info()
{
    printf("###############################################################################\n\n");
    printf("Commands:\n");
    printf("\t1. LIST: push element\n");
    printf("\t2. LIST: pop element\n");
    printf("\t3. LIST: print the head of the stack\n");
    printf("\t4. LIST: print complete stack\n");
    printf("\t5. ARRAY: push element\n");
    printf("\t6. ARRAY: pop element\n");
    printf("\t7. ARRAY: print the head of the stack\n");
    printf("\t8. ARRAY: print complete stack\n");
    printf("\t9. LIST: print freed memory\n");
    printf("\t10. Print stats\n");
    printf("\t0. Exit program\n");
}



// Remove trash from the input stream
void clear_stream()
{
    char symbol;
    while (((symbol = getchar()) != '\n') && (symbol != EOF));
}


// Show message to the user
void error_message(const int error_code)
{
    printf("Error!\n");
    switch (error_code)
    {
        case STACK_OVERFLOW_ERROR:
            printf("Stack overflow!\n\n");
            break;

        case ALLOCATE_NODE_ERROR:
            printf("Denied in allocating another node in the list!\n\n");
            break;

        case EMPTY_STACK_ERROR:
            printf("The stack is empty!\n");
            break;
        
        case NO_FREED_ERROR:
            printf("No memory was freed yet!\n");
            break;
    }
}

