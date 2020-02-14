#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/define.h"
#include "../include/structs.h"
#include "../include/hash_function.h"
#include "../include/utils_hash.h"



// Initiallize hash table
void init_hash_table(hashTable_t *const hash_table, const int size)
{
    for (int element = 0; element < size; element++)
    {
        (hash_table + element)->value = 0;
        (hash_table + element)->flag = FREE;
    }
}


int add_hash_table(hashTable_t *const hash_table, const int value, const int max_collisions, 
                   const int divisor, int (*hfunc)(const int, const int))
{
    int idx = (*hfunc)(value, divisor);
    
    int checks = 0;
    int delta = 1;
    int counter = 1;

    while (hash_table[idx].flag == OCCUPIED)
    {

        if (checks == divisor - 1)
        {
            return FULL_TABLE_ERROR;
        }

        checks++;

        idx = (idx + delta) % divisor;
        delta = (int)pow(++counter, 2);

        if (checks == max_collisions + 1)
        {
            return COLLISIONS_EXCEED_ERROR;
        }
    }

    hash_table[idx].value = value;
    hash_table[idx].flag = OCCUPIED;

    return SUCCESS;
}


void delete_hash_table(hashTable_t *const hash_table, const int value)
{
    for (int i = 0; i < MAX_TABLE_DIME; i++)
    {
        if ((hash_table[i].value == value) && (hash_table[i].flag == OCCUPIED))
        {
            hash_table[i].flag = FREE;
            break;
        }
    }
}


hashTable_t *upload_hash_table(const char *const filename, const int divisor, const int max_collisions, int *const code)
{
    FILE *src = fopen(filename, "r");
    if (!src)
    {
        *code = FILE_NFOUND_ERROR;
        return NULL;
    }
    rewind(src);

    hashTable_t *hash_table = (hashTable_t *)calloc(MAX_TABLE_DIME, sizeof(hashTable_t));
    if (!hash_table)
    {
        *code = MEMORY_ERROR;
        return NULL;
    }

    init_hash_table(hash_table, MAX_TABLE_DIME);

    int temp_code;
    int value = 0;
    while (fscanf(src, "%d", &value) == 1)
    {
        temp_code = add_hash_table(hash_table, value, max_collisions, divisor, &mod_hash);
        if (temp_code != SUCCESS)
        {
            // *code = temp_code;
            free(hash_table);
            return NULL;
        }
    }

    fclose(src);

    *code = SUCCESS;
    return hash_table;
}


void print_hash_table(FILE *const output_stream, hashTable_t *const hash_table)
{
    fprintf(output_stream, "\t# Position\t|\tValue\n");

    for (int i = 0; i < MAX_TABLE_DIME; i++)
    {
        if (hash_table[i].flag == OCCUPIED)
        {
            fprintf(output_stream, "\t%8d\t|\t%-d\n", i , hash_table[i].value);
        }
    }
}
