#include <stdio.h>
#include <stdlib.h>

#include "../include/define.h"
#include "../include/struct.h"
#include "../include/menu.h"



void welcome()
{
    printf("This program models queue via:\n"
           "\t1) Array realization\n"
           "\t2) Linked list realization\n\n");
}


void print_menu()
{
    printf("Choose option:\n"
           "\t1 - Model queue (linked list realization) & print statistics\n"
           "\t2 - Model queue (array realization) & print statistics\n"
           "\t3 - Operations on the queue stats (linked list realization)\n"
           "\t4 - Operations on the queue stats (array realization)\n"
           "\t0 - Exit program\n");
}


// Remove trash from the input stream
void clear_stream()
{
    char symbol;
    while (((symbol = getchar()) != '\n') && (symbol != EOF));
}


int limits_input(int *const number, int *const left_lim_in, int *const right_lim_in,
                 int *const left_lim_out, int *const right_lim_out,
                 int *const repeats)
{
    int code;

    *number = 10000;

    printf("Enter time limits of entering the queue (integers): ");
    code = scanf("%d %d", left_lim_in, right_lim_in);
    if ((code != 2) || (*left_lim_in >= right_lim_in) || (left_lim_in < 0))
    {
        errno = INVALID_VALUE;
        return INVALID_VALUE;
    }

    printf("Enter time limits of servicing elements (integers): ");
    code = scanf("%d %d", left_lim_out, right_lim_out);
    if ((code != 2) || (*left_lim_out >= right_lim_out) || (left_lim_out < 0))
    {
        errno = INVALID_VALUE;
        return INVALID_VALUE;
    }

    printf("Enter amount of repeats of each element (integer): ");
    code = scanf("%d", repeats);
    if ((code != 1) || (repeats < 0))
    {
        errno = INVALID_VALUE;
        return INVALID_VALUE;
    }

    return OK;
}

