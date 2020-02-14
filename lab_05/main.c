#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "include/define.h"
#include "include/struct.h"
#include "include/menu.h"
#include "include/array.h"
#include "include/queue_list.h"
#include "include/queue_array.h"
#include "include/modeling.h"



int main()
{
    welcome();

    qList_t *queue_list = NULL;
    qArray_t *queue_array = NULL;
    array_t *memory = NULL;

    qArray_t *testing_array = NULL;
    qList_t *testing_list = NULL;
    array_t *memory_testing = NULL;
    task_t task;

    uint64_t start, end;

    int ltime_in, rtime_in;
    int ltime_out, rtime_out;
    int capacity;
    int repeats;

    int input_error[] = {INVALID_VALUE, INVALID_TYPE};

    int menu_key = -1;
    while (menu_key)
    {
        print_menu();

        // Invalid symbols
        if (scanf("%d", &menu_key) != 1)
        {
            printf("Error: unknown command!\nPlease try again.\n\n");
            clear_stream();
            continue;
        }

        switch (menu_key)
        {
            
            // Model linked list realization
            case 1:
                if (queue_list)
                {
                    printf("Oops!\nAlready modeled!\nRestart app to model again!\n");
                    return OK;
                }

                if (limits_input(&capacity, &ltime_in, &rtime_in, &ltime_out, &rtime_out, &repeats))
                {
                    printf("Error!\nInvalid input! Try again plz!\n");
                    break;
                }
                else
                {
                    queue_list = create_qlist(capacity);
                    memory = create_array(capacity);

                    start = tick();
                    model_list(queue_list, memory, ltime_in, rtime_in, ltime_out, rtime_out, repeats);
                    end = tick();

                    printf("Modeling time (list): %" PRIu64 "\n", end - start);
                }
                
                break;
            
            // Model array realization
            case 2:
                if (queue_array)
                {
                    printf("Oops!\nAlready modeled!\nRestart app to model again!\n");
                    break;
                }

                if (limits_input(&capacity, &ltime_in, &rtime_in, &ltime_out, &rtime_out, &repeats))
                {
                    printf("Error!\nInvalid input! Try again plz!\n");
                    break;
                }
                else
                {
                    queue_array = create_qarray(capacity);

                    start = tick();
                    model_array(queue_array, ltime_in, rtime_in, ltime_out, rtime_out, repeats);
                    end = tick();

                    printf("Modeling time (array): %" PRIu64 "\n", end - start);
                }

                break;

            // Testing list realization
            case 3:
                if (testing_list)
                {
                    printf("Oops!\nAlready tested!\nRestart app to test again!\n");
                    break;
                }

                testing_list = create_qlist(1000);
                memory_testing = create_array(1000);

                start = tick();
                for (int i = 0; i < 1000; i++)
                {
                    task.num = i;
                    task.time_out = (double)i;
                    add_qlist(testing_list, task);
                }
                end = tick();
                printf("\tEntering element (list): %" PRIu64 " ticks\n", (end - start) / 1000);

                start = tick();
                for (int i = 0; i < 1000; i++)
                {
                    out_qlist(testing_list, memory_testing);
                }
                end = tick();
                printf("\tLeaving element (list): %" PRIu64 " ticks\n", (end - start) / 1000);

                free_qlist(testing_list, memory_testing);
                free_array(memory_testing);

                break;
            
            // Testing array realization
            case 4:
                if (testing_array)
                {
                    printf("Oops!\nAlready tested!\nRestart app to test again!\n");
                    break;
                }

                testing_array = create_qarray(1000);

                start = tick();
                for (int i = 0; i < 1000; i++)
                {
                    task.num = i;
                    task.time_out = (double)i;
                    add_qarray(testing_array, task);
                }
                end = tick();
                printf("\tEntering element (array): %" PRIu64 " ticks\n", (end - start) / 1000);

                start = tick();
                for (int i = 0; i < 1000; i++)
                {
                    out_qarray(testing_array);
                }
                end = tick();
                printf("\tLeaving element (array): %" PRIu64 " ticks\n", (end - start) / 1000);
                
                free_qarray(testing_array);

                break;
            
            // Exit program
            case 0:
                printf("Ciao!\n");
                break;

            // Unknown key
            default:
                printf("Error: unknown command!\nPlease try again.\n\n");
                break;
        }
    }

    free_qarray(queue_array);
    free_qlist(queue_list, memory);
    free_array(memory);

    return OK;
}

// if (cmd == 5)
        // {
        //     printf("%s\n", "Array of freed adresses:");
        //     if (memory != NULL)
        //     {
        //         print_array(*memory);
        //     }
        // }