#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <stdint.h>
// #pragma pack(push, 1)


// Hash table
typedef struct
{   
    int value;
    int flag;
} hashTable_t;


// Linked list nodes (tree)
typedef struct node_t
{
    int value;
    struct node_t *left;
    struct node_t *right;
} treeNode_t;


// Linked list nodes (avl_tree)
typedef struct node
{
    int value;
    int balance;
    struct node *left;
    struct node *right;
} avlNode_t;


// Statistics info
typedef struct
{
    uint64_t time_add_file;
    uint64_t time_add_bst;
    uint64_t time_add_avl;
    uint64_t time_add_hash_table;

    int cmps_file;
    int cmps_hash_table;
    int cmps_bst;
    int cmps_avl;

    int avg_file_cmps;
    uint64_t avg_file_time;

    int avg_ht_cmps;
    uint64_t avg_ht_time;

    int avg_bst_cmps;
    uint64_t avg_bst_time;

    int avg_avl_cmps;
    uint64_t avg_avl_time;

    size_t memory_file;
    size_t memory_hash_table;
    size_t memory_bst;
    size_t memory_avl;
} statData_t;

#endif