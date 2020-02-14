#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <errno.h>

#include "../include/define.h"
#include "../include/struct.h"
#include "../include/array.h"
#include "../include/queue_array.h"
#include "../include/queue_list.h"
#include "../include/modeling.h"



// Get abstract time (units of time)
double get_abstract_time(const int lower_lim, const int upper_lim)
{
    double rseed = (double)rand() / (double)RAND_MAX;

    return rseed * (upper_lim - lower_lim) + lower_lim;
}


// Processor ticks' counter
uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}


// List modeling
void model_list(qList_t *const queue, array_t *const memory,
                const int llim_in, const int rlim_in,
                const int llim_out, const int rlim_out,
                const int repeats)
{
    srand(time(NULL));

    int in_tasks = 0;
    int out_tasks = 0;
    int failed_tasks = 0;
    int calls = 0;
    double service_time = 0;
    double idle_time = 0;

    double time_in = get_abstract_time(llim_in, rlim_in);
    double time_out = -1;

    task_t toDo;

    int reused_mem = 0;
    int new_mem = 0;
    int type;

    int overall_len = 0;

    while (out_tasks != 1000)
    {
        if ((time_out < 0) || (time_in < time_out))
        {
            if (time_out < 0)
            {
                idle_time += time_in;
            }

            service_time += time_in;
            time_out -= time_in;
            time_in = get_abstract_time(llim_in, rlim_in);

            task_t task = {.time_out = get_abstract_time(llim_out, rlim_out),
                           .num = 0};

            add_qlist(queue, task);

            if (errno == QUEUE_OVERFLOW)
            {
                // printf("QUEUE OVERFLOW!\tElement skipped!\n");
                failed_tasks++;
            }
            else
            {
                type = check_rear(queue, memory);
                if (type)
                {
                    reused_mem++;
                }
                else
                {
                    new_mem++;
                }
                in_tasks++;
            }

            if ((time_out < 0) && (queue->size))
            {
                toDo = out_qlist(queue, memory);
                time_out = toDo.time_out;
            }
        }
        else
        {
            time_in -= time_out;
            service_time += time_out;
            time_out = 0;

            toDo.num++;
            calls++;

            if (toDo.num < repeats)
            {
                toDo.time_out = get_abstract_time(llim_out, rlim_out);
                add_qlist(queue, toDo);

                if (errno == QUEUE_OVERFLOW)
                {
                    // printf("QUEUE OVERFLOW!\tElement skipped!\n");
                    failed_tasks++;
                }
                else
                {
                    type = check_rear(queue, memory);
                    if (type)
                    {
                        reused_mem++;
                    }
                    else
                    {
                        new_mem++;
                    }
                }
            }
            else
            {
                overall_len += queue->size;
                out_tasks++;

                if (out_tasks % 100 == 0)
                {
                    printf("\n#######################################\n"
                           "\tProcessed %d requests\n"
                           "\tCurrent queue length: %d\n"
                           "\tAverage queue length: %d\n"
                           "#######################################\n",
                           out_tasks, queue->size, overall_len / out_tasks);
                }
            }

            if (is_empty_qlist(queue))
            {
                time_out = -1;
            }
            else
            {
                toDo = out_qlist(queue, memory);
                time_out = toDo.time_out;
            }
        }
    }

    double expected_time;
    if (((llim_in + rlim_in) / 2 * 1000) > ((llim_out + rlim_out) / 2 * repeats * 1000))
    {
        expected_time = (llim_in + rlim_in) / 2 * 1000;
    }
    else
    {
        expected_time = calls * (llim_out + rlim_out) / 2;
    }

    double delta = fabs(service_time - expected_time) / expected_time * 100;

    printf("OVERALL:\n"
           "\tRequests entered: %d\n"
           "\tRequests left: %d\n"
           "\tRequests missed: %d\n"
           "\tAutomate calls: %d\n\n"
           "\tService time: %lf (expected service time: %lf, accuracy: %lf%%)\n"
           "\tIdle time: %lf\n\n"
           "\tReused memory adresses: %d\n"
           "\tNew memory adresses: %d\n\n",
           in_tasks, out_tasks, failed_tasks, calls, 
           service_time, expected_time, delta, idle_time, reused_mem, new_mem);
}


// Array modeling
void model_array(qArray_t *const queue,
                 const int llim_in, const int rlim_in,
                 const int llim_out, const int rlim_out,
                 const int repeats)
{
    srand(time(NULL));

    int in_tasks = 0;
    int out_tasks = 0;
    int failed_tasks = 0;
    int calls = 0;
    double service_time = 0;
    double idle_time = 0;

    double time_in = get_abstract_time(llim_in, rlim_in);
    double time_out = -1;

    task_t toDo;

    int overall_len = 0;

    while (out_tasks != 1000)
    {
        if ((time_out < 0) || (time_in < time_out))
        {
            if (time_out < 0)
            {
                idle_time += time_in;
            }

            service_time += time_in;
            time_out -= time_in;
            time_in = get_abstract_time(llim_in, rlim_in);

            task_t task = {.time_out = get_abstract_time(llim_out, rlim_out),
                           .num = 0};

            add_qarray(queue, task);

            if (errno == QUEUE_OVERFLOW)
            {
                // printf("QUEUE OVERFLOW!\tElement skipped!\n");
                failed_tasks++;
            }
            else
            {
                in_tasks++;
            }

            if ((time_out < 0) && (queue->size))
            {
                toDo = out_qarray(queue);
                time_out = toDo.time_out;
            }
        }
        else
        {
            time_in -= time_out;
            service_time += time_out;
            time_out = 0;

            toDo.num++;
            calls++;

            if (toDo.num < repeats)
            {
                toDo.time_out = get_abstract_time(llim_out, rlim_out);
                add_qarray(queue, toDo);

                if (errno == QUEUE_OVERFLOW)
                {
                    // printf("QUEUE OVERFLOW!\tElement skipped!\n");
                    failed_tasks++;
                }
            }
            else
            {
                overall_len += queue->size;
                out_tasks++;
                
                if (out_tasks % 100 == 0)
                {
                    printf("\n#######################################\n"
                           "\tProcessed %d requests\n"
                           "\tCurrent queue length: %d\n"
                           "\tAverage queue length: %d\n"
                           "#######################################\n",
                           out_tasks, queue->size, overall_len / out_tasks);
                }
            }

            if (is_empty_qarray(queue))
            {
                time_out = -1;
            }
            else
            {
                toDo = out_qarray(queue);
                time_out = toDo.time_out;
            }
        }
    }

    double expected_time;
    if ((llim_in + rlim_in) / 2 * 1000 > (llim_out + rlim_out) / 2 * repeats * 1000)
    {
        expected_time = (llim_in + rlim_in) / 2 * 1000;
    }
    else
    {
        expected_time = calls * (llim_out + rlim_out) / 2;
    }
    double delta = fabs(service_time - expected_time) / expected_time * 100;

    printf("OVERALL:\n"
           "\tRequests entered: %d\n"
           "\tRequests left: %d\n"
           "\tRequests missed: %d\n"
           "\tAutomate calls: %d\n\n"
           "\tService time: %lf (expected service time: %lf, accuracy: %lf%%)\n"
           "\tIdle time: %lf\n\n",
           in_tasks, out_tasks, failed_tasks, calls, 
           service_time, expected_time, delta, idle_time);
}



// int in_tasks = 0;
//     int out_tasks = 0;
//     int failed_tasks = 0;
//     int calls = 0;
//     double service_time = 0;
//     double hold_time = 0;

//     double time_in = get_abstract_time(llim_in, rlim_in);
//     double time_out = -1;

//     task_t task_todo;

//     int overall_len = 0;

//     while (out_tasks != 1000)
//     {
//         if (time_out < 0 || time_in < time_out)
//         {
//             if (time_out < 0)
//             {
//                 hold_time += time_in;
//             }

//             service_time += time_in;
//             time_out -= time_in;
//             time_in = get_abstract_time(llim_in, rlim_in);

//             task_t task = {.num = 0,
//                            .time_out = get_abstract_time(llim_out, rlim_out)};

//             add_qarray(queue, task);

//             if (errno == QUEUE_OVERFLOW)
//             {
//                 // printf("Очередь переполнена! Новый элемент не будет добавлен!\n");
//                 failed_tasks++;
//             }
//             else
//             {
//                 in_tasks++;
//             }

//             if (time_out < 0 && queue->size)
//             {
//                 task_todo = out_qarray(queue);
//                 time_out = task_todo.time_out;
//             }
//         }
//         else
//         {
//             time_in -= time_out;
//             service_time += time_out;
//             time_out = 0;

//             task_todo.num++;
//             calls++;

//             if (task_todo.num < repeats)
//             {
//                 task_todo.time_out = get_abstract_time(llim_out, rlim_out);
//                 add_qarray(queue, task_todo);

//                 if (errno == QUEUE_OVERFLOW)
//                 {
//                     // printf("Очередь переполнена! Новый элемент не будет добавлен!\n");
//                     failed_tasks++;
//                 }
//             }
//             else
//             {
//                 overall_len += queue->size;
//                 out_tasks++;
//                 if (out_tasks % 100 == 0)
//                 {
//                     printf("\n#######################################\n"
//                            "\tProcessed %d requests\n"
//                            "\tCurrent queue length: %d\n"
//                            "\tAverage queue length: %d\n"
//                            "#######################################\n",
//                            out_tasks, queue->size, overall_len / out_tasks);
//                 }
//             }

//             if (is_empty_qarray(queue))
//             {
//                 time_out = -1;
//             }
//             else
//             {
//                 task_todo = out_qarray(queue);
//                 time_out = task_todo.time_out;
//             }
//         }
//     }

//     double expected_time;
//     if ((llim_in + rlim_in) / 2 * 1000 > (llim_out + rlim_out) / 2 * repeats * 1000)
//     {
//         expected_time = (llim_in + rlim_in) / 2 * 1000;
//     }
//     else
//     {
//         expected_time = calls * (llim_out + rlim_out) / 2;
//     }
//     double delta = fabs(service_time - expected_time) / expected_time * 100;