#include <stdio.h>
#include <stdlib.h>

#include "include/define.h"
#include "include/structs.h"
#include "include/menu.h"
#include "include/hash_function.h"
#include "include/utils_hash.h"
#include "include/utils_tree.h"
#include "include/stats.h"



int main()
{
    welcome();
    //printf("sizeof(avlNode_t) = %I64d\nsizeof(treeNode_t) = %I64d\n\n\n", sizeof(avlNode_t), sizeof(treeNode_t));

    treeNode_t *root = NULL, *copy_root = NULL;
    avlNode_t *avl = NULL;
    hashTable_t *hash_table = NULL;

    int prime_divisors[] = { 11, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
    int code = 0;
    int max_cmps = -1, value = 0, idx = 0;
    int divisor = 0;

    statData_t stats;
    int a, test;

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
            case 228:
                make_avl(root, &avl, &a);

                printf("OK BOOMER\n\n");

                print_avl(stdout, avl, 0);
                printf("OK BOOMER\n\n");

                FILE *png = fopen(FILE_PNG, "w");
                init_gv(png);
                print_avl_visualized(png, avl, 0);
                end_gv(png);
                fclose(png);
                    
                system("C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng tree.gv -o tree.png");
                system("start " VIEWER " tree.png");

                scanf("%d", &test);
                avl_remove(&avl, test, &a);
                png = fopen(FILE_PNG, "w");
                init_gv(png);
                print_avl_visualized(png, avl, 0);
                end_gv(png);
                fclose(png);
                    
                system("C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng tree.gv -o tree.png");
                system("start " VIEWER " tree.png");
                break;

            case CREATE_TREE:
                if (root)
                {
                    free_tree(root);
                    root = NULL;
                }

                if ((root = upload_tree(FILE_SRC, &code)) == NULL)
                {  
                    print_error(code);
                }
                break;
            
            case PRINT_TREE:
                if (root == NULL)
                {
                    print_error(NO_TREE_ERROR);
                }
                else
                {
                    print_tree(stdout, root, 0);

                    FILE *png = fopen(FILE_PNG, "w");
                    init_gv(png);
                    print_tree_visualized(png, root, 0);
                    end_gv(png);
                    fclose(png);
                    
                    system("C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng tree.gv -o tree.png");
                    system("start " VIEWER " tree.png");
                }
                break;

            case GET_BALANCED_TREE:
                if (avl)
                {
                    free_avl_tree(avl);
                    avl = NULL;
                    copy_root = NULL;
                }

                if ((copy_root = upload_tree(FILE_SRC, &code)) == NULL)
                {
                    print_error(code);
                }

                make_avl(copy_root, &avl, &a);

                break;
            
            case PRINT_BALANCED_TREE:
                if (avl == NULL)
                {
                    print_error(NO_TREE_ERROR);
                }
                else
                {
                    print_avl(stdout, avl, 0);

                    FILE *png = fopen(FILE_PNG, "w");
                    init_gv(png);
                    print_avl_visualized(png, avl, 0);
                    end_gv(png);
                    fclose(png);
                    
                    system("C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng tree.gv -o tree.png");
                    system("start " VIEWER " tree.png");
                }
                break;

            case CREATE_HASH:
                if (hash_table != NULL)
                {   
                    free(hash_table);
                }

                if (max_cmps < 1)
                {
                    print_error(CMP_ERROR);
                }
                else
                {
                    idx = 0;
                    divisor = prime_divisors[idx];

                    while ((hash_table = upload_hash_table(FILE_SRC, divisor, max_cmps, &code)) == NULL)
                    {
                        if (code)
                        {
                            print_error(code);
                            break;
                        }

                        divisor = prime_divisors[++idx];

                        if (idx > 20)
                        {
                            print_error(NO_FUNCTION);
                            break;
                        }
                    }
                }       
                break;

            case PRINT_HASH:
                if (hash_table == NULL)
                {
                    print_error(NO_TABLE_ERROR);
                }
                else
                {
                    print_hash_table(stdout, hash_table);
                } 
                break;

            case DELETE_ELEMENT:
                if (!root || !avl || !hash_table)
                {
                    print_error(NOT_ALL_ERROR);
                }
                else if (get_value(stdin, stdout, &value) == SUCCESS)
                {
                    if (delete_file(FILE_SRC, value) == SUCCESS)
                    {
                        bst_remove(&root, value, &a);
                        avl_remove(&avl, value, &a);

                        delete_hash_table(hash_table, value);

                        // idx = 0;
                        // divisor = prime_divisors[idx];
                        // while ((hash_table = upload_hash_table(FILE_SRC, divisor, max_cmps, &code)) == NULL)
                        // {
                        //     if (code)
                        //     {
                        //         print_error(code);
                        //         break;
                        //     }

                        //     divisor = prime_divisors[++idx];

                        //     if (idx > 20)
                        //     {
                        //         print_error(NO_FUNCTION);
                        //         break;
                        //     }
                        // }

                        // if (idx <= 20)
                        // {
                        //     add_hash_table(hash_table, value, max_cmps, divisor, mod_hash);
                        // }    
                    }
                    else
                    {
                        print_error(DUPLICATE_ERROR);
                    }
                }
                else
                {
                    print_error(INTEGER_INPUT_ERROR);
                }
                break;

            case STATS:
                init_stats(&stats);
                if ((code = get_value(stdin, stdout, &value)))
                {
                    print_error(code);
                }
                else
                {
                    int temp = run_stats(&stats, FILE_TEST, 17, 100, value);
                    if (!temp)
                    {
                        print_stats(stdout, &stats);
                    }
                    else
                    {
                        printf("Error!\nTesting failed (inputed value exists in data)!!\n\n");
                    }
                }
                break;

            case SET_COLLISIONS:
                if ((code = get_value(stdin, stdout, &max_cmps)) || (max_cmps < 1))
                {
                    print_error(CMP_ERROR);
                }
                break;
    
            case TRAVERSAL:
                if (!avl)
                {
                    print_error(NO_TREE_ERROR);
                }
                else
                {
                    traversal(stdout, avl);
                }
                break;
            
            case EXIT:
                printf("Ciao!\n");
                break;

            // Unknown key
            default:
                printf("Error: unknown command!\nPlease try again.\n\n");
                break;
        }
    }

    free_tree(root);
    free_avl_tree(avl);
    free(hash_table);

    return SUCCESS;
}