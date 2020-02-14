#include <stdio.h>
#include <time.h>

#include "struct.h"
#include "defines.h"
#include "menu.h"
#include "algebra.h"
#include "matrix_io.h"



int main()
{
    welcome();

    int code; 

    sparseMatrix_t sparse_matrix, sparse_result_matrix;
    stdMatrix_t std_matrix, std_vector_row, std_result_matrix, sparse_vector_row;

    bool_t sparse_input_flag = FALSE, sparse_calc_flag = FALSE;
    bool_t std_input_flag = FALSE, std_calc_flag = FALSE;

    int menu_key = -1; 
    while (menu_key != 0)
    {
        menu_info();

        if (scanf("%d", &menu_key) != VALID_INPUT)
        {
            printf("Error: unknown command!\n Please try again.\n\n");
            clear_stream();
            continue;
        }

        switch (menu_key)
        {
            case 20:
                sparse_vector_row = input_std_matrix(vector_input);
                std_vector_row = sparse_vector_row;
                std_matrix = input_std_matrix(matrix_input);
                sparse_matrix = transform_to_sparse(std_matrix);

                sparse_input_flag = TRUE;
                std_input_flag = TRUE;
                break;
            
            case 21:
                printf("Entered sparse matrix %dx%d\n", sparse_matrix.rows, sparse_matrix.cols);
                print_sparse(&sparse_matrix);
                printf("\n\n");
                break;


            // Enter in CSR format
            case 1: 
                sparse_vector_row = input_std_matrix(vector_input);
                if (sparse_vector_row.cols == INPUT_ERROR)
                {
                    printf("ERROR!\n"
                           "Invalid input!\n\n");
                    break;
                }

                sparse_matrix = input_sparse_matrix(matrix_input);
                if (sparse_matrix.cols == INPUT_ERROR)
                {
                    printf("ERROR!\n"
                           "Invalid input!\n\n");
                    break;
                }

                sparse_input_flag = TRUE;
                sparse_calc_flag = FALSE;
                break;

            // Enter in standard format
            case 2: 
                std_vector_row = input_std_matrix(vector_input);
                if (std_vector_row.cols == INPUT_ERROR)
                {
                    printf("ERROR!\n"
                           "Invalid input!\n\n");
                    break;
                }

                std_matrix = input_std_matrix(matrix_input);
                if (std_matrix.cols == INPUT_ERROR)
                {
                    printf("ERROR!\n"
                           "Invalid input!\n\n");
                    break;
                }

                std_input_flag = TRUE;
                std_calc_flag = FALSE;
                break;

            // Calculate sparse multiplication
            case 3:
                if (sparse_input_flag == FALSE)
                {
                    printf("ERROR!\n"
                           "Impossible to multiplicate (nothing in CSR format entered)!\n\n");
                    break;
                }

                sparse_result_matrix = sparse_m12n(&sparse_vector_row, &sparse_matrix);
                if (sparse_result_matrix.cols == MULTIPLICATION_ERROR)
                {
                    printf("ERROR!\n"
                        "Impossible to multiplicate (invalid dimensions)!\n\n");
                    break;
                }

                sparse_calc_flag = TRUE;
                break;

            // Calculate standard multiplication
            case 4:
                if (std_input_flag == FALSE)
                {
                    printf("ERROR!\n"
                           "Impossible to multiplicate (nothing in STD format entered)!\n\n");
                    break;
                }

                std_result_matrix = std_m12n(&std_vector_row, &std_matrix);
                if (std_result_matrix.cols == MULTIPLICATION_ERROR)
                {
                    printf("ERROR!\n"
                        "Impossible to multiplicate (invalid dimensions)!\n\n");
                    break;
                }
            
                std_calc_flag = TRUE;
                break;

            // Generate sparse
            case 5:
                code = sparse_random_generation(&sparse_vector_row, &sparse_matrix);
                if (code)
                {
                    printf("ERROR!\n"
                           "Invalid input!\n\n");
                    break; 
                }

                sparse_input_flag = TRUE;
                break;

            // Generate standard
            case 6:
                code = std_random_generation(&std_vector_row, &std_matrix);
                if (code)
                {
                    printf("ERROR!\n"
                           "Invalid input!\n\n");
                    break; 
                }

                std_input_flag = TRUE;
                break;

            // Print standard
            case 7:
                if (std_input_flag == FALSE)
                {
                    printf("ERROR!\n"
                           "Impossible to print (nothing in STD format entered)!\n\n");
                    break;
                }

                printf("VECTOR-ROW 1x%d\n", std_vector_row.cols);
                print_std_matrix(&std_vector_row);
                printf("]\n\n");

                printf("MATRIX %dx%d\n", std_matrix.rows, std_matrix.cols);
                print_std_matrix(&std_matrix);
                printf("\n\n");
                break;

            // Print sparse by coordinates
            case 8:
                if (sparse_input_flag == FALSE)
                {
                    printf("ERROR!\n"
                           "Impossible to print (nothing in CSR format entered)!\n\n");
                    break;
                }

                printf("VECTOR-ROW 1x%d\n", sparse_vector_row.cols);
                print_std_by_coords(&sparse_vector_row);
                printf("]\n\n");

                printf("MATRIX %dx%d\n", sparse_matrix.rows, sparse_matrix.cols);
                print_sparse_by_coords(&sparse_matrix);
                printf("\n\n");
                break;

            // Print standard result
            case 9:
                if (std_calc_flag == FALSE)
                {
                    printf("ERROR!\n"
                           "Impossible to print (nothing in STD format has been calculated yet)!\n\n");
                    break;
                }

                if (std_result_matrix.rows == ZERO_MULTIPLICATION)
                    printf("Result is the zero-vector!\n\n");
                else
                {

                    printf("RESULT VECTOR-ROW 1x%d\n", std_result_matrix.cols);
                    print_std_matrix(&std_result_matrix);
                    printf("\n\n");
                    break;
                }
                
            // Print standard result by coordinates
            case 10:
                if (std_calc_flag == FALSE)
                {
                    printf("ERROR!\n"
                           "Impossible to print (nothing in STD format has been calculated yet)!\n\n");
                    break;
                }

                if (std_result_matrix.rows == ZERO_MULTIPLICATION)
                    printf("Result is the zero-vector!\n\n");
                else
                {
                    printf("RESULT VECTOR-ROW 1x%d\n", std_result_matrix.cols);
                    print_std_by_coords(&std_result_matrix);
                    printf("\n\n");
                    break;
                }

            // Print sparse result by coordinates
            case 11:
                if (sparse_calc_flag == FALSE)
                {
                    printf("ERROR!\n"
                           "Impossible to print (nothing in CSR format has been calculated yet)!\n\n");
                    break;
                }

                if (sparse_result_matrix.col_idx[0] == ZERO_MULTIPLICATION)
                    printf("Result is the zero-vector!\n\n");
                else
                {
                    printf("RESULT VECTOR-ROW 1x%d\n", sparse_result_matrix.cols);
                    print_sparse_by_coords(&sparse_result_matrix);
                    printf("\n\n");
                    break;
                }
            
            // Print sparse result in std way
            case 12:
                if (sparse_calc_flag == FALSE)
                {
                    printf("ERROR!\n"
                           "Impossible to print (nothing in CSR format has been calculated yet)!\n\n");
                    break;
                }

                if (sparse_result_matrix.col_idx[0] == ZERO_MULTIPLICATION)
                    printf("Result is the zero-vector!\n\n");
                else
                {
                    printf("RESULT VECTOR-ROW 1x%d\n", sparse_result_matrix.cols);
                    print_sparse_to_std(&sparse_result_matrix);
                    printf("\n\n");
                    break;
                }

            // Print sparse by 3 arrays
            case 13:
                if (sparse_calc_flag == FALSE)
                {
                    printf("ERROR!\n"
                           "Impossible to print (nothing in CSR format has been calculated yet)!\n\n");
                    break;
                }

                if (sparse_result_matrix.col_idx[0] == ZERO_MULTIPLICATION)
                    printf("Result is the zero-vector!\n\n");
                else
                {
                    printf("RESULT VECTOR-ROW 1x%d\n", sparse_result_matrix.cols);
                    print_sparse(&sparse_result_matrix);
                    printf("\n\n");
                    break;
                }

            // Stats
            case 14:
                // if ((std_calc_flag == FALSE) || (sparse_calc_flag == FALSE))
                // {
                //     printf("ERROR!\n"
                //            "Impossible to print stats (do both types of multiplication)!\n\n");
                //     break;   
                // }

                print_stats();
                break;

            // Exit program
            case 0:
                continue;

            // Unknown command         
            default:
                printf("Error: unknown command!\nPlease try again.\n\n");
                break;
        }
    }

    return SUCCESS;
}