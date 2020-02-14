#include <stdio.h>

#include "../include/define.h"
#include "../include/menu.h"


void welcome()
{
    printf("This program provides analisys of two data structure:\n"
           "\t\tTREES and HASH TABLES\n\n"
           "Implemented CLOSED hashing\n"
           "Data type: integers (uploaded from the file)\n\n");
}


void print_menu()
{
    printf("Choose:\n"
           "\t1.  Make binary search tree (BST)\n"
           "\t2.  Print binary search tree (BST)\n"
           "\t3.  Make avl-tree\n"
           "\t4.  Print avl-tree\n"
           "\t5.  Build hash table\n"
           "\t6.  Print hash table\n"
           "\t7.  Set limit of compares for hash table\n"
           "\t8.  Delete element from all 3 data structures\n"
           "\t9.  Print stats of deleting element (isolated data)\n"
           "\t10. Tree traversal\n"
           "\t0.  Exit\n");
}


void print_error(const int err_code)
{
    switch (err_code)
    {
        case FILE_NFOUND_ERROR:
            printf("Error!\nFile can't be open!\n\n");

        case MEMORY_ERROR:
            printf("Error!\nMemory allocation error!\n\n");
            break;

        case DUPLICATE_ERROR:
            printf("Error!\nElement doesn't consist in the data!\n\n");
            break;

        case FULL_TABLE_ERROR:
            printf("Error!\nTable is full!\n\n");
            break;

        case NO_FUNCTION:
            printf("Error!\nThere is no such hash-function to build hash-table!\n\n");
            break;
        
        case CMP_ERROR:
            printf("Error!\nInvalid max. amount of compares entered (or doesn't set)!\n\n");
            break;

        case INTEGER_INPUT_ERROR:
            printf("Error!\nInvalid number entered; check your input!\n\n");
            break;

        case NOT_ALL_ERROR:
            printf("Error\nNot all of data structures have been entered!\n\n");
            break;        

        case NO_TREE_ERROR:
            printf("Error!\nTree hasn't been uploaded yet!\n\n");
            break; 

        case NO_TABLE_ERROR:
            printf("Error!\nHash table hasn't been uploaded yet!\n");
            break; 
    }
}


void clear_stream()
{
    char symbol;
    while (((symbol = getchar()) != '\n') && (symbol != EOF));
}
