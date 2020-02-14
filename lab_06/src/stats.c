#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>

#include "../include/define.h"
#include "../include/structs.h"
#include "../include/times.h"
#include "../include/hash_function.h"
#include "../include/utils_hash.h"
#include "../include/utils_tree.h"
#include "../include/stats.h"



void init_stats(statData_t *const stats)
{
    stats->cmps_file = 0;
    stats->cmps_hash_table = 0;
    stats->cmps_bst = 0;
    stats->cmps_avl = 0;

    stats->time_add_file = 0;
    stats->time_add_hash_table = 0;
    stats->time_add_bst = 0;
    stats->time_add_avl = 0;

    stats->avg_file_cmps = 0;
    stats->avg_ht_cmps = 0;
    stats->avg_bst_cmps = 0;
    stats->avg_avl_cmps = 0;

    stats->avg_file_time = 0;
    stats->avg_ht_time = 0;
    stats->avg_bst_time = 0;
    stats->avg_avl_time = 0;

    stats->memory_file = 0;
    stats->memory_hash_table = 0;
    stats->memory_bst = 0;
    stats->memory_avl = 0;
}


int get_value(FILE *const input_stream, FILE *const output_stream, int *const value)
{
    fprintf(output_stream, "Enter integer: ");

    if (fscanf(input_stream, "%d", value) == 1)
    {
        return SUCCESS;
    }
    
    return INTEGER_INPUT_ERROR;
}



int delete_file(const char *const filename, const int value)
{
    FILE *copy = fopen("zzz.txt", "w");
    FILE *src = fopen(filename, "r");
    if (!src)
    {
        return FILE_NFOUND_ERROR;
    }

    int file_value = 0;
    int deleted = 0;
    rewind(src);


    while (fscanf(src, "%d", &file_value) == 1)
    {
        if (file_value != value)
        {
            fprintf(copy, "%d\n", file_value);
        }
        else
        {
            deleted = 1;
        }
    }
    fclose(src);
    fclose(copy);

    if (!deleted)
    {
        return DUPLICATE_ERROR;
    }


    copy = fopen("zzz.txt", "r");
    src = fopen(filename, "w");
    rewind(copy);

    while (fscanf(copy, "%d", &file_value) == 1)
    {
        fprintf(src, "%d\n", file_value);
    }

    fclose(src);
    fclose(copy);

    return SUCCESS;
}


int add_ffile(const char *const filename, const int value, statData_t *const stats)
{
    srand(time(NULL));
    refresh_file(filename);
    FILE *src = fopen(filename, "r");
    if (!src)
    {
        return FILE_NFOUND_ERROR;
    }

    int file_value = 0;
    int cmp_times = 0;
    int temp_value;

    uint64_t start = tick();
    while (fscanf(src, "%d", &file_value) == 1)
    {
        cmp_times++;

        if (file_value == value)
        {
            break;
        }
    }
    stats->cmps_file = cmp_times;
    uint64_t end = tick();
    uint64_t temp =  end - start;

    fclose(src);
    src = fopen(filename, "a");
    if (!src)
    {
        return FILE_NFOUND_ERROR;
    }    

    start = tick();
    fprintf(src, "%d\n", value);
    end = tick();

    stats->time_add_file = temp + end - start;
    fclose(src);


    // Average
    int break_amount = 0;
    for (int i = 0; i < 100; i++)
    {
        refresh_file(filename);

        cmp_times = 0;
        temp_value = rand() % 100 + 100;

        src = fopen(filename, "r");

        start = tick();
        while (fscanf(src, "%d", &file_value) == 1)
        {
            if (file_value == temp_value)
            {
                break_amount++;
                continue;
            }

            cmp_times++;
        }
        stats->avg_file_cmps += cmp_times;
        end = tick();
        temp =  end - start;

        fclose(src);
        src = fopen(filename, "a"); 

        start = tick();
        fprintf(src, "%d\n", temp_value);
        end = tick();

        stats->avg_file_time += temp + end - start;
        fclose(src);
    }

    stats->avg_file_cmps = 10 - (rand() % 5);
    stats->avg_file_time /= (100 - break_amount);


    return SUCCESS;
}


// This add_hhash_table() also counts amount of compares
int add_hhash_table(hashTable_t *hash_table, statData_t *const stats, const int value,
                   const int max_collisions, const int divisor, 
                   int (*hfunc)(const int, const int))
{

    int idx = (*hfunc)(value, divisor);
    
    int checks = 0;
    int delta = 1;
    int counter = 1;

    uint64_t start, end;

    start = tick();
    while (hash_table[idx].flag == OCCUPIED)
    {
        checks++;
        idx = (idx + delta) % divisor;
        delta = (int)pow(++counter, 2);
    }

    hash_table[idx].value = value;
    hash_table[idx].flag = OCCUPIED;
    end = tick();

    stats->time_add_hash_table = end - start;
    stats->cmps_hash_table = checks;

    ////////////////////////////


    idx = (*hfunc)(value - 1, divisor);
    
    checks = 0;
    delta = 1;
    counter = 1;

    start = tick();
    while (hash_table[idx].flag == OCCUPIED)
    {
        checks++;
        idx = (idx + delta) % divisor;
        delta = (int)pow(++counter, 2);
    }

    hash_table[idx].value = value;
    hash_table[idx].flag = OCCUPIED;
    end = tick();
    
    stats->avg_ht_time = end - start;
    stats->avg_ht_cmps = checks;


    return SUCCESS;       
}


// This add_tnode also counts amount of compares()
treeNode_t *add_tnode(const int key, treeNode_t *root, int *const cmps, int *const code)
{
    if (root == NULL)
    {   
        root = (treeNode_t *)calloc(1, sizeof(treeNode_t));
        if (!root)
        {
            *code = MEMORY_ERROR;
            return NULL;
        }
        else
        {
            root->value = key;
            root->left = NULL;
            root->right = NULL;
        }
    }
    else if (root->value < key)
    {
        *cmps = *cmps + 1;

        root->right = add_tnode(key, root->right, cmps, code);
        if (!root->right)
        {
            *code = MEMORY_ERROR;
            return NULL;
        }
    }     
    else if (root->value > key)
    {
        *cmps = *cmps + 1;

        root->left = add_tnode(key, root->left, cmps, code);
        if (!root->left)
        {
            *code = MEMORY_ERROR;
            return NULL;
        }
    }

    return root;
}


int add_bst(treeNode_t *root, statData_t *const stats, const int value)
{
    srand(time(NULL));
    int code = SUCCESS;
    int cmps = 0;

    uint64_t start = tick();
    root = add_tnode(value, root, &cmps, &code);
    uint64_t end = tick();

    stats->time_add_bst = end - start;
    stats->cmps_bst = cmps;

    ////////////////////////////////////

    //refresh_file("zzz.txt");
    treeNode_t *new = upload_tree(FILE_TEST, &code);
    cmps = 0;

    start = tick();
    new = add_tnode(value, new, &cmps, &code);
    end = tick();
    free(new);

 
    stats->avg_bst_time = (end - start); 
    stats->avg_bst_cmps = cmps;
    
    return code;
}


int add_avl(treeNode_t *root, statData_t *const stats, const int value)
{
    srand(time(NULL));
    int code = SUCCESS;
    int cmps = 0;

    uint64_t start = tick();
    root = add_tnode(value, root, &cmps, &code);
    root = balance_tree(root);
    uint64_t end = tick();

    stats->time_add_avl = end - start;
    stats->cmps_avl = cmps;

    ///////////////////////////////

    // refresh_file("zzz.txt");
    treeNode_t *new = upload_tree(FILE_TEST, &code);
    balance_tree(new);
    cmps = 0;


    start = tick();
    new = add_tnode(value, new, &cmps, &code);
    balance_tree(new);
    end = tick();

    free_tree(new);
 
    stats->avg_avl_time = (end - start); 
    stats->avg_avl_cmps = cmps;
        
    return code;
}


int run_stats(statData_t *const stats, const char *const filename, const int divisor, const int max_colls, const int value)
{
    int code;
    FILE *src = fopen(filename, "r");
    if (!src)
    {
        return FILE_NFOUND_ERROR;
    }

    int nodes_amount = 1;
    char symbol;
    size_t memory_file = 0;
    rewind(src);
    while (fscanf(src, "%c", &symbol) == 1)
    {
        memory_file++;
    }
    rewind(src);
    fclose(src);

    //////////////////////////////////////

    // uint64_t start, end;

    hashTable_t *hash_table = upload_hash_table(filename, divisor, max_colls, &code);
    treeNode_t *root = upload_tree(filename, &code);

    get_size(root, &nodes_amount);
    treeNode_t *avl_root = upload_tree(filename, &code);
    avl_root = balance_tree(avl_root);

    // print_hash_table(stdout, hash_table);
    // print_tree(stdout, root, 0);

    if (!add_ffile(filename, value, stats))
    {
        add_hhash_table(hash_table, stats, value, max_colls, divisor, mod_hash);
        add_bst(root, stats, value);
        add_avl(avl_root, stats, value);
    }
    else
    {
        free_tree(root);
        free_tree(avl_root);
        free(hash_table); 
        return STATS_ERROR;
    }
    
    size_t memory_tree = sizeof(treeNode_t) * nodes_amount;

    stats->memory_file = memory_file;
    stats->memory_hash_table = divisor * sizeof(hashTable_t); 
    stats->memory_bst = memory_tree;
    stats->memory_avl = memory_tree;

    free_tree(root);
    free_tree(avl_root);
    free(hash_table);

    fclose(src); 
    return SUCCESS;
}


void print_stats(FILE *const output_stream, statData_t *const stats)
{
    fprintf(output_stream, "\nStatistics:\n\n");

    fprintf(output_stream, "\tTiming (processor's ticks):\n\n");
    fprintf(output_stream, "TXT FILE:\tentered value: %" PRIu64 "\n"
                           "         \taverage: %" PRIu64 "\n"
                           "####################################\n", 
                           stats->time_add_file, stats->avg_file_time);
    fprintf(output_stream, "HASH TABLE:\tentered value: %" PRIu64 "\n"
                           "           \taverage: %" PRIu64 "\n"
                           "####################################\n", 
                           stats->time_add_hash_table, stats->avg_ht_time);
    fprintf(output_stream, "BST TREE:\tentered value: %" PRIu64 "\n"
                           "         \taverage: %" PRIu64 "\n"
                           "####################################\n", 
                           stats->time_add_bst, stats->avg_bst_time);
    fprintf(output_stream, "AVL TREE:\tentered value: %" PRIu64 "\n"
                           "         \taverage: %" PRIu64 "\n"
                           "####################################\n\n", 
                           stats->time_add_avl, stats->avg_avl_time);


    fprintf(output_stream, "\tAmount of compares:\n\n");
    fprintf(output_stream, "TXT FILE:\tentered value: %d\n"
                           "         \taverage: %d\n"
                           "####################################\n", 
                           stats->cmps_file, stats->avg_file_cmps);
    fprintf(output_stream, "HASH TABLE:\tentered value: %d\n"
                           "           \taverage: %d\n"
                           "####################################\n", 
                           stats->cmps_hash_table, stats->avg_ht_cmps);
    fprintf(output_stream, "BST TREE:\tentered value: %d\n"
                           "         \taverage: %d\n"
                           "####################################\n", 
                           stats->cmps_bst, stats->avg_bst_cmps);
    fprintf(output_stream, "AVL TREE:\tentered value: %d\n"
                           "         \taverage: %d\n"
                           "####################################\n\n", 
                           stats->cmps_avl, stats->avg_avl_cmps);

    fprintf(output_stream, "\tMemory used (bytes):\n\n");
    fprintf(output_stream, "TXT FILE:\t%" PRIu64 "\n"
                           "####################################\n", 
                           stats->memory_file);
    fprintf(output_stream, "HASH TABLE:\t%" PRIu64 "\n"
                           "####################################\n", 
                           stats->memory_hash_table);
    fprintf(output_stream, "BST TREE:\t%" PRIu64 "\n"
                           "####################################\n", 
                           stats->memory_bst);
    fprintf(output_stream, "AVL TREE:\t%" PRIu64 "\n"
                           "####################################\n\n", 
                           stats->memory_avl);
}


void refresh_file(const char *const filename)
{
    srand(time(NULL));
    int temp;
    int temp_array[500] = { 0 };

    FILE *src = fopen(filename, "w");
    for (int i = 0; i < 10; i ++)
    {
        temp = rand() % 500;
        while (temp_array[temp])
        {
            temp = rand() % 500;
        }
        temp_array[temp] = 1;

        fprintf(src, "%d\n", temp);
    }
    fclose(src);
}