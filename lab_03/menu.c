#include <stdio.h>

#include "menu.h"



// About program
void welcome()
{
    printf("SPARSE MATRICES & co.\n\n\n");
    printf("About:\n");
    printf("This program allows to multiplicate vector-row and matrix in\n"
           "standard format and in CSR (compressed sparse rows) format.\n");
    printf("Also it can compare algorithms of multiplication in standard and\n"
           "sparse format.\n\n\n");
}


// Menu commands
void menu_info()
{
    printf("###############################################################################\n\n");
    printf("Commands:\n");
    printf("\t1. Enter vector-row & matrix in CSR format\n");
    printf("\t2. Enter vector-row & matrix in standard format\n");
    printf("\t3. Calculate sparse multiplication\n");
    printf("\t4. Calculate standard multiplication\n");
    printf("\t5. Generate vector-row & matrix in CSR format\n");
    printf("\t6. Generate vector-row & matrix in standard format\n");
    printf("\t7. Print entered (generated) standard vector-row & matrix\n");
    printf("\t8. Print entered (generated) sparse vector-row & matrix in coordinates format\n");
    printf("\t9. Print standard result in standard format\n");
    printf("\t10. Print standard result in coordinates format\n");
    printf("\t11. Print sparse result in coordinates format\n");
    printf("\t12. Print sparse result in standard format\n");
    printf("\t13. Print sparse result in CSR format\n");
    printf("\t14. Print result stats\n");
    printf("\t0. Exit program\n");
}



// Remove trash from the input stream
void clear_stream()
{
    char symbol;
    while (((symbol = getchar()) != '\n') && (symbol != EOF));
}
