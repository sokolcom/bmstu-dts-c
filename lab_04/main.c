// lab_04

#include <stdio.h>

#include "define.h"
#include "struct.h"

#include "menu.h"
#include "stack_list.h"
#include "stack_array.h"
#include "stats.h"



int main()
{
    welcome();

    // Linked list realization
    stackList_t *stack_list = NULL;
    stackList_t *freed_list = NULL;
    size_t *memory = NULL;

    // Static array realization
    int *array[STACK_SIZE];
    stackArray_t stack_array;
    stack_array.start = array;
    stack_array.end = array + STACK_SIZE - 1;
    stack_array.head = array - 1;


    int error_code = SUCCESS;

    int menu_key = -1;
    while (menu_key != KEY_EXIT)
    {
        menu_info();

        // Invalid symbols
        if (scanf("%d", &menu_key) != VALID_INPUT)
        {
            printf("Error: unknown command!\n Please try again.\n\n");
            clear_stream();
            continue;
        }

        switch (menu_key)
        {
            // Push element (list)
            case PUSH_LIST:
                if ((error_code = push_list(&stack_list, NULL)))
                {
                    error_message(error_code);
                }
                break;

            // Pop element (list)
            case POP_LIST:
                if ((memory = (pop_list(&stack_list))) == NULL)
                {
                    error_message(EMPTY_STACK_ERROR);
                }
                else
                {
                    push_list(&freed_list, memory);
                }
                break;

            // Print stack head (list)
            case PRINT_HEAD_LIST:
                if ((error_code = print_head_list(stdout, stack_list)))
                {
                    error_message(error_code);
                }
                break; 

            // Print complete stack (list)
            case PRINT_STACK_LIST:
                if ((error_code = print_stack_list(stdout, stack_list)))
                {
                    error_message(error_code);
                }
                break; 

            // Push element (array)
            case PUSH_ARRAY:
                if ((error_code = push_array(&stack_array, NULL)))
                {
                    error_message(error_code);
                }
                break;

            // Pop element (array)
            case POP_ARRAY:
                if ((error_code = pop_array(&stack_array)))
                {
                    error_message(error_code);
                }
                break;
            
            // Print stack head (array)
            case PRINT_HEAD_ARRAY:
                if ((error_code = print_head_array(stdout, &stack_array)))
                {
                    error_message(error_code);
                }
                break; 

            // Print complete stack (array)
            case PRINT_STACK_ARRAY:
                if ((error_code = print_stack_array(stdout, &stack_array)))
                {
                    error_message(error_code);
                }
                break;

            // Print freed memory (list)
            case PRINT_FREED_MEMORY:
                if ((error_code = print_freed_memory(stdout, freed_list)))
                {
                    error_message(error_code);
                }
                break;

            // Statistics
            case STATS:
                print_stats();
                break;

            // Exit program
            case KEY_EXIT:
                printf("Ciao!\n");
                break;

            // Unknown key
            default:
                printf("Error: unknown command!\n Please try again.\n\n");
                break;
        }
    }

    free_stack_list(stack_list);
    free_stack_list(freed_list);

    return SUCCESS;
}

