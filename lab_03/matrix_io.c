#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include "struct.h"
#include "defines.h"
#include "menu.h"
#include "matrix_io.h"
#include "algebra.h"



// Standard input of standard matrix
stdMatrix_t input_std(const type_t type)
{
    stdMatrix_t matrix;

    if (type == vector_input)
    {
        printf("Enter amount of cols (less than 100): ");
        if ((scanf("%d", &matrix.cols) != VALID_INPUT) && (matrix.cols <= 0))
        {
            matrix.cols = INPUT_ERROR;
            return matrix;
        }

        matrix.rows = 1;

        printf("Enter elements of the vector: ");
        for (int i = 0; i < matrix.cols; i++)
        {
            if (scanf("%d", &(matrix.matrix[0][i])) != VALID_INPUT)
            {
                matrix.cols = INPUT_ERROR;
                return matrix;
            }
        }
    }
    
    if (type == matrix_input)
    {
        printf("Enter amount of rows (1 <= n <= 100): ");
        if ((scanf("%d", &matrix.rows) != VALID_INPUT) && (matrix.rows <= 0) && (matrix.rows > MAX_DIME))
        {
            matrix.cols = INPUT_ERROR;
            return matrix;
        }

        printf("Enter amount of cols (1 <= n <= 100): ");
        if ((scanf("%d", &matrix.cols) != VALID_INPUT) && (matrix.cols < 0) && (matrix.cols > MAX_DIME))
        {
            matrix.cols = INPUT_ERROR;
            return matrix;
        }

        printf("Enter elements of the matrix %dx%d: ", matrix.rows, matrix.cols);
        for (int i = 0; i < matrix.rows; i++)
        {
            for (int j = 0; j < matrix.cols; j++)
            {
                if (scanf("%d", &(matrix.matrix[i][j])) != VALID_INPUT)
                {
                    matrix.cols = INPUT_ERROR;
                    return matrix;
                }
            }
        }
    }

     return matrix;
}


// Coordinates input of standard
stdMatrix_t input_std_by_coords(const type_t type)
{
    stdMatrix_t matrix;
    if (type == vector_input)
    {
        printf("Enter amount of cols: ");
        if ((scanf("%d", &matrix.cols) != VALID_INPUT) && (matrix.cols <= 0) && (matrix.cols > MAX_DIME))
        {
            matrix.cols = INPUT_ERROR;
            return matrix;
        }

        matrix.rows = 1;

        for (int i = 0; i < matrix.rows; i++)
            for (int j = 0; j < matrix.cols; j++)
                matrix.matrix[i][j] = 0;

        printf("Enter elements in specificated doubles: <column_index> <value>\n");
        printf("To stop entering enter -1\n");

        int row_index = 0, col_index = 0, value;
        int scanf_code;
        while (col_index != -1)
        {
            scanf_code = scanf("%d", &col_index);
            if (scanf_code && (col_index < 0))
                break;

            scanf_code = scanf("%d", &value);
            if ((scanf_code == 1) && (col_index >= 0) && (col_index < matrix.cols))
            {
                matrix.matrix[row_index][col_index] = value;
            }
            else
            {
                matrix.cols = INPUT_ERROR;
                return matrix;
            }
        }
    }
    
    if (type == matrix_input)
    {
        printf("Enter amount of rows (1 <= n <= 100): ");
        if ((scanf("%d", &matrix.rows) != VALID_INPUT) && (matrix.rows <= 0) && (matrix.rows > MAX_DIME))
        {
            matrix.cols = INPUT_ERROR;
            return matrix;
        }

        printf("Enter amount of cols (1 <= n <= 100): ");
        if ((scanf("%d", &matrix.cols) != VALID_INPUT) && (matrix.cols <= 0) && (matrix.cols > MAX_DIME))
        {
            matrix.cols = INPUT_ERROR;
            return matrix;
        }

        for (int i = 0; i < matrix.rows; i++)
            for (int j = 0; j < matrix.cols; j++)
                matrix.matrix[i][j] = 0;

        printf("Enter elements in specificated triplets: <row_index> <column_index> <value>\n");
        printf("To stop entering enter -1\n");

        int row_index = 0, col_index, value;
        int scanf_code;
        while (row_index != -1)
        {
            scanf_code = scanf("%d", &row_index);
            if (scanf_code && (row_index < 0))
                continue;
            
            scanf_code = scanf("%d %d", &col_index, &value);
            if ((scanf_code == 2) && (row_index < matrix.rows) && (col_index >= 0) && (col_index < matrix.cols))
            {
                matrix.matrix[row_index][col_index] = value;
            }
            else
            {
                matrix.cols = INPUT_ERROR;
                return matrix;
            }
        }
    }

     return matrix;
}


// Standard matrix/vector-row input
// const type_t type indicates what to input
stdMatrix_t input_std_matrix(const type_t type)
{
    stdMatrix_t matrix;

    if (type == vector_input)
    {
        printf("How you'd like to enter vector-row?\n"
               "\t1 - standard\n"
               "\t2 - by coordinates\n");

        int key = -1; 
        while (key != 1 && key != 2)
        {
            printf("Your decision: ");
            if (scanf("%d", &key) != VALID_INPUT)
            {
                printf("Error: unknown command!\n Please try again.\n\n");
                clear_stream();
                continue;
            }

            switch (key)
            {
                // Standard
                case 1:
                    matrix = input_std(vector_input);
                    break;

                // Coordinates
                case 2:
                    matrix = input_std_by_coords(vector_input);
                    break;

                // Unknown command         
                default:
                    printf("Error: unknown command!\nPlease try again.\n\n");
                    break;
            }
        }

    }

    if (type == matrix_input)
    {
        printf("How you'd like to enter matrix?\n"
               "\t1 - standard\n"
               "\t2 - by coordinates\n");

        int key = -1; 
        while (key != 1 && key != 2)
        {
            printf("Your decision: ");
            if (scanf("%d", &key) != VALID_INPUT)
            {
                printf("Error: unknown command!\n Please try again.\n\n");
                clear_stream();
                continue;
            }

            switch (key)
            {
                // Standard
                case 1:
                    matrix = input_std(matrix_input);
                    break;

                // Sparse
                case 2:
                    matrix = input_std_by_coords(matrix_input);
                    break;

                // Unknown command         
                default:
                    printf("Error: unknown command!\nPlease try again.\n\n");
                    break;
            }
        }
    }
    
    return matrix;
}


// Input in sparse matrix/vector-row in sparse format
sparseMatrix_t input_std_into_sparse(const type_t type)
{
    sparseMatrix_t matrix;
    stdMatrix_t temp_matrix;

    if (type == matrix_input)
    {
        temp_matrix = input_std(matrix_input);
        // std_transpose(&temp_matrix);
        matrix = transform_to_sparse(temp_matrix);
    }

    return matrix;
}


sparseMatrix_t input_crd_into_sparse(const type_t type)
{
    sparseMatrix_t matrix;
    stdMatrix_t temp_matrix;

    if (type == vector_input)
    {
        temp_matrix = input_std_by_coords(vector_input);
        matrix = transform_to_sparse(temp_matrix); 
    }

    if (type == matrix_input)
    {
        temp_matrix = input_std_by_coords(matrix_input);
        matrix = transform_to_sparse(temp_matrix); 
    }

    return matrix;
}


// Sparse matrix/vector-row input
// const type_t type indicates what to input
sparseMatrix_t input_sparse_matrix(const type_t type)
{
    sparseMatrix_t matrix;

    if (type == vector_input)
    {
        printf("How you'd like to enter vector-row?\n"
               "\t1 - standard\n"
               "\t2 - by coordinates\n");

        int key = -1; 
        while (key != 1 && key != 2)
        {
            printf("Your decision: ");
            if (scanf("%d", &key) != VALID_INPUT)
            {
                printf("Error: unknown command!\n Please try again.\n\n");
                clear_stream();
                continue;
            }

            switch (key)
            {
                // Standard
                case 1:
                    matrix = input_std_into_sparse(vector_input);
                    break;

                // Coordinates
                case 2:
                    matrix = input_crd_into_sparse(vector_input);
                    break;

                // Unknown command         
                default:
                    printf("Error: unknown command!\nPlease try again.\n\n");
                    break;
            }
        }

    }

    if (type == matrix_input)
    {
        printf("How you'd like to enter matrix?\n"
               "\t1 - standard\n"
               "\t2 - by coordinates\n");

        int key = -1; 
        while (key != 1 && key != 2)
        {
            printf("Your decision: ");
            if (scanf("%d", &key) != VALID_INPUT)
            {
                printf("Error: unknown command!\n Please try again.\n\n");
                clear_stream();
                continue;
            }

            switch (key)
            {
                // Standard
                case 1:
                    matrix = input_std_into_sparse(matrix_input);
                    break;

                // Sparse
                case 2:
                    matrix = input_crd_into_sparse(matrix_input);
                    break;

                // Unknown command         
                default:
                    printf("Error: unknown command!\nPlease try again.\n\n");
                    break;
            }
        }
    }

    return matrix;
}


// Random generation with entered percentage of non-zero elements
stdMatrix_t generate_trivial(const int row_amount, const int col_amount, const int percentage)
{
    srand(time(NULL));

    stdMatrix_t matrix;

    matrix.rows = row_amount;
    matrix.cols = col_amount;

    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            matrix.matrix[i][j] = 0;
        }
    }

    int non_zero_amount = row_amount * col_amount * percentage / 100;
    int g_row;
    int g_col;
    for (int i = 0; i < non_zero_amount; i++)
    {
        g_row = rand() % row_amount;
        g_col = rand() % col_amount;
        while (matrix.matrix[g_row][g_col] != 0)   
        {
            g_row = rand() % row_amount;
            g_col = rand() % col_amount;
        }

        matrix.matrix[g_row][g_col] = rand() % 100 + 1;  // randint in range of 100
    }

    return matrix;
}


sparseMatrix_t transform_to_sparse(stdMatrix_t matrix)
{
    sparseMatrix_t result_matrix;

    result_matrix.rows = matrix.rows;
    result_matrix.cols = matrix.cols;

    int rows_counter = 0;

    for (int i = 0; i < matrix.rows; i++)
    {
        result_matrix.row_ptr[i] = rows_counter;

        for (int j = 0; j < matrix.cols; j++)
        {
            if (matrix.matrix[i][j])
            {
                result_matrix.csr_values[rows_counter] = matrix.matrix[i][j];
                result_matrix.col_idx[rows_counter] = j;
                rows_counter++;
            }
        }
    }

    result_matrix.row_ptr[matrix.rows] = rows_counter;

    return result_matrix;
}


// Random generation with entered percentage of non-zero elements
sparseMatrix_t generate_sparse(const int row_amount, const int col_amount, const int percentage)
{
    stdMatrix_t temp_matrix = generate_trivial(row_amount, col_amount, percentage);
    // std_transpose(&temp_matrix);
    sparseMatrix_t matrix = transform_to_sparse(temp_matrix);
    return matrix;
}


int sparse_random_generation(stdMatrix_t *const vector_row, sparseMatrix_t *const matrix)
{
    int rows, cols, percentage;

    printf("VECTOR-ROW\n");
    printf("Enter amount of cols (less than 100): ");
    scanf("%d", &cols);
    if ((cols > MAX_DIME) || (cols < 1))
        return GENERATION_ERROR;
    
    printf("Enter percentage of non-zero elements (integer): ");
    scanf("%d", &percentage);
    if ((percentage > 100) || (percentage < 1))
        return GENERATION_ERROR;
    
    *vector_row = generate_trivial(1, cols, percentage);

    printf("\n\nMATRIX\n");
    printf("Enter amount of rows (less than 100): ");
    scanf("%d", &rows);
    if ((rows > MAX_DIME) || (rows < 1))
        return GENERATION_ERROR;

    printf("Enter amount of cols (less than 100): ");
    scanf("%d", &cols);
    if ((cols > MAX_DIME) || (cols < 1))
        return GENERATION_ERROR;
    
    printf("Enter percentage of non-zero elements (integer): ");
    scanf("%d", &percentage);
    if ((percentage > 100) || (percentage < 1))
        return GENERATION_ERROR;
    
    *matrix = generate_sparse(rows, cols, percentage);

    return SUCCESS;
}


int std_random_generation(stdMatrix_t *const vector_row, stdMatrix_t *const matrix)
{
    int rows, cols, percentage;

    printf("VECTOR-ROW\n");
    printf("Enter amount of cols (less than 100): ");
    scanf("%d", &cols);
    if ((cols > MAX_DIME) || (cols < 1))
        return GENERATION_ERROR;
    
    printf("Enter percentage of non-zero elements (integer): ");
    scanf("%d", &percentage);
    if ((percentage > 100) || (percentage < 1))
        return GENERATION_ERROR;
    
    *vector_row = generate_trivial(1, cols, percentage);

    printf("\n\nMATRIX\n");
    printf("Enter amount of rows (less than 100): ");
    scanf("%d", &rows);
    if ((rows > MAX_DIME) || (rows < 1))
        return GENERATION_ERROR;

    printf("Enter amount of cols (less than 100): ");
    scanf("%d", &cols);
    if ((cols > MAX_DIME) || (cols < 1))
        return GENERATION_ERROR;
    
    printf("Enter percentage of non-zero elements (integer): ");
    scanf("%d", &percentage);
    if ((percentage > 100) || (percentage < 1))
        return GENERATION_ERROR;
    
    *matrix = generate_trivial(rows, cols, percentage);

    return SUCCESS;

}


void print_border(const int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("-");
    }
    printf("\n");
}


// Print standard matrix
void print_std_matrix(const stdMatrix_t *const matrix)
{
    print_border(5 * matrix->cols);

    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            if (matrix->matrix[i][j]  == 0)
                printf("     ");
            else
                printf("%5d", matrix->matrix[i][j]);
        }

        printf("\n");
    }

    print_border(5 * matrix->cols);
}


// Print standard by coordinates
void print_std_by_coords(const stdMatrix_t *const matrix)
{
    bool_t flag = FALSE;
    printf("Print specification: [<row> <column> <value>]\n");

    for (int i = 0; i < matrix->rows; i++)
    {
        flag = FALSE;

        for (int j = 0; j < matrix->cols; j++)
        {
            if (matrix->matrix[i][j] != 0)
            {
                flag = TRUE;
                printf("| %d %d %d ", i, j, matrix->matrix[i][j]);
            }
        }

        if (flag)
        {
            printf("|\n");    
        }
    }

}


// Print sparse by coordinates
void print_sparse_by_coords(const sparseMatrix_t *const matrix)
{
    printf("Print specification: [<row> <column> <value>]\n");

    for (int i = 1; i <= matrix->rows; i++)
    {
        for (int j = matrix->row_ptr[i - 1]; j < matrix->row_ptr[i]; j++)
        {
            printf("| %d %d %d ", i - 1, matrix->col_idx[j], matrix->csr_values[j]);
        }

        if (matrix->row_ptr[i] - matrix->row_ptr[i - 1] > 0)
        {
            printf("|\n");
        }
    }
}


int get_element(const sparseMatrix_t *const matrix, const int i, const int j)
{
    for (int k = matrix->row_ptr[i]; k < matrix->row_ptr[i + 1]; k++)
    {
        if (matrix->col_idx[k] == j)
        {
            return matrix->csr_values[k];
        }
    }

    return 0;
}

// Print sparse like standard
void print_sparse_to_std(const sparseMatrix_t *const matrix)
{
    int element;
    print_border(5 * matrix->cols);

    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            element = get_element(matrix, i, j);
            if (element)
                printf("%5d", element);
            else
                printf("     ");
        }

        printf("\n");
    }

    print_border(5 * matrix->cols);
}


int count_percentage(const stdMatrix_t *const matrix)
{
    int total = matrix->rows * matrix->cols;
    int amount = 0;

    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->cols; j++)
            if (matrix->matrix[i][j] != 0)  
                amount++;
    
    int percentage = (amount * 100) / total;
    return percentage;
}


// Print sparse in sparse format
void print_sparse(const sparseMatrix_t *const matrix)
{
    printf("Values:\n");
    for (int i = 0; i < matrix->row_ptr[matrix->rows]; i++)
        printf("%5d", matrix->csr_values[i]);
    printf("\n");

    printf("Column indices:\n");
    for (int i = 0; i < matrix->row_ptr[matrix->rows]; i++)
        printf("%5d", matrix->col_idx[i]);
    printf("\n");

    printf("Row pointers:\n");
    for (int i = 0; i < matrix->rows + 1; i++)
        printf("%5d", matrix->row_ptr[i]);
    printf("\n\n");
}


sparseMatrix_t sparse_mult(sparseMatrix_t vector_row, sparseMatrix_t matrix)
{
    sparseMatrix_t result;
    result.rows = 1;
    result.cols = matrix.cols;

    int sum = 0, cur = 0, cur_m = 0;

    for (int i = 0; i < vector_row.row_ptr[vector_row.rows]; i++)
    {
        for (int j = 0; j < vector_row.row_ptr[vector_row.rows]; j++)
        {
            if (vector_row.col_idx[j] == matrix.col_idx[i])
                sum = sum + vector_row.csr_values[j] * matrix.csr_values[i];
        }

        for (int j = 0; j < matrix.rows; j++)
        {
            if (i + 1 == matrix.row_ptr[j])
            {
                if (sum)
                {
                    result.csr_values[cur] = sum;
                    result.col_idx[cur] = cur_m;
                    cur++;
                    cur_m++;
                    sum = 0;
                }
                else
                    cur_m++;
            }
            else if (!matrix.row_ptr[i] && !matrix.row_ptr[i + 1] && !cur_m)
                cur_m++;
        }
    }

    return result;
}


// Print  multiplication stats
void print_stats()
{
    printf("MULTIPLICATION STATS\n\n");

    int rows, cols, percentage;
    printf("VECTOR-ROW\n");
    printf("Enter amount of cols (less than 100): ");
    scanf("%d", &cols);
    
    printf("Enter percentage of non-zero elements (integer): ");
    scanf("%d", &percentage);
    
    stdMatrix_t vector_row_1 = generate_trivial(1, cols, percentage);
    sparseMatrix_t vector_row_2 = transform_to_sparse(vector_row_1);

    printf("\n\nMATRIX\n");
    printf("Enter amount of rows (less than 100): ");
    scanf("%d", &rows);
    printf("Enter amount of cols (less than 100): ");
    scanf("%d", &cols);
    
    printf("Enter percentage of non-zero elements (integer): ");
    scanf("%d", &percentage);
    
    stdMatrix_t std_matrix = generate_trivial(rows, cols, percentage);
    std_transpose(&std_matrix);
    sparseMatrix_t sparse_matrix = transform_to_sparse(std_matrix);
    std_transpose(&std_matrix);

    stdMatrix_t std_result;
    clock_t start = clock();
    for (int i = 0; i < 1000; i++)
        std_result = std_m12n(&vector_row_1, &std_matrix);
    clock_t end = clock();
    double time_std = (double)(end - start) / CLOCKS_PER_SEC;
    // time_std /= 1000;


    sparseMatrix_t sparse_result;
    start = clock();
    for (int i = 0; i < 1000; i++)
        sparse_result = sparse_mult(vector_row_2, sparse_matrix);
    end = clock();
    double time_sparse = (double)(end - start) / CLOCKS_PER_SEC;
    // time_sparse /= 1000;

    printf("\n\nMatrix dimensions: 1x%d\n", std_result.cols);
    printf("Amount of non_zero elements: %d%%\n\n", percentage);

    printf("Execution time\n");
    printf("\tstandard multiplication - %lf\n", time_std);
    printf("\tCSR multiplication - %lf\n\n", time_sparse);

    uint64_t memory_std = sizeof(int) * std_result.cols;
    uint64_t memory_sparse = 2 * sizeof(int) * sparse_matrix.row_ptr[sparse_result.rows] + sizeof(int) * (sparse_result.rows + 1);

    printf("Memory\n");
    printf("\tstandard method - %" PRId64 "\n", memory_std);
    printf("\tCSR method - %" PRId64 "\n\n", memory_sparse);
}
