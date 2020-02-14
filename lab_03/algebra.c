#include <stdio.h>

#include "struct.h"
#include "defines.h"
#include "algebra.h"



// Dot product (compute ij-element)
int dot_product(stdMatrix_t *vector_row, stdMatrix_t *matrix, int row, int col)
{
    int element = 0;

    for (int i = 0; i < vector_row->cols; i++)
    {
        element += vector_row->matrix[row][i] * matrix->matrix[i][col];
    }
    return element;
}


// Normal (trivial) multiplication
stdMatrix_t std_m12n(stdMatrix_t *vector_row, stdMatrix_t *matrix)
{ 
    stdMatrix_t result_matrix;

    if (vector_row->cols != matrix->rows)
    {
        result_matrix.cols = MULTIPLICATION_ERROR;  // indicates error
        return result_matrix;
    }
    
    result_matrix.rows = vector_row->rows;
    result_matrix.cols = matrix->cols;

    int not_null = 0;
    int element;

    for (int i = 0; i < result_matrix.rows; i++)
    {
        for (int j = 0; j < result_matrix.cols; j++)
        {
            element = dot_product(vector_row, matrix, i, j);
            result_matrix.matrix[i][j] = element;
            if (element)
                not_null++;
        }
    }

    if (!not_null)
        result_matrix.rows = ZERO_MULTIPLICATION;

    return result_matrix;
}


stdMatrix_t copy_matrix(const stdMatrix_t *const matrix)
{
    stdMatrix_t copy;
    copy.rows = matrix->rows;
    copy.cols = matrix->cols;

    for (int i = 0; i < copy.rows; i++)
    {
        for (int j = 0; j < copy.cols; j++)
        {
            copy.matrix[i][j] = matrix->matrix[i][j];
        }
    }
    return copy;
}


void std_transpose(stdMatrix_t *const matrix)
{
    stdMatrix_t temp_matrix = copy_matrix(matrix);
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            matrix->matrix[j][i] = temp_matrix.matrix[i][j];
        }
    }

    int temp = matrix->rows;
    matrix->rows = matrix->cols;
    matrix->cols = temp;
}


// // Fill buffer in sparse multiplication
// void fill_invalid_values(int *array, const int cell)
// {
//     for (int i = 0; i < cell; i++)
//     {
//         array[i] = UNREAL_VALUE;;
//     }
// }


sparseMatrix_t sparse_m12n(stdMatrix_t *vector_row, sparseMatrix_t *matrix)
{
    sparseMatrix_t result_matrix;

    if (vector_row->cols != matrix->rows)
    {
        result_matrix.cols = MULTIPLICATION_ERROR;  // in case of error it will indicate it
        return result_matrix;
    }

    int temp = 0;
    result_matrix.rows = 0;
    result_matrix.cols = 0;

    int not_null = 0;
    int temp_row;

    int j;
    for (int column = 0; column < matrix->cols; column++)
    {
        temp = 0;
        for (j = 0; j < matrix->cols; j++)
        {
            if (matrix->col_idx[j] == column)
            {
                for (int i = 0; i < matrix->rows; i++)
                {
                    if (i == matrix->rows - 1)
                    {
                        if (j >= matrix->row_ptr[i] && j < matrix->cols)
                        {
                            temp_row = i;
                            break;
                        }

                    }
                    else
                    {
                        if (j >= matrix->row_ptr[i] && j < matrix->row_ptr[i + 1])
                        {
                            temp_row = i;
                            break;
                        }
                    }
                }
                temp += matrix->csr_values[j] * vector_row->matrix[0][temp_row];
            }
        }
        if (temp != 0)
        {
            not_null++;
            if (result_matrix.rows == 0)
            {
                result_matrix.rows++;
                result_matrix.row_ptr[0] = 0;
            }
            result_matrix.col_idx[result_matrix.cols] = column;
            result_matrix.csr_values[result_matrix.cols++] = temp;
        }
    }

    if (!not_null)
        result_matrix.col_idx[0] = ZERO_MULTIPLICATION;
    
    result_matrix.rows = vector_row->rows;
    result_matrix.cols = matrix->cols;

    result_matrix.row_ptr[1] = not_null;

    return result_matrix;


    // int buffer[MAX_DIME];

    // int fill_index = 0;
    // fill_invalid_values(buffer, vector_row->cols); 

    // for (int i = 0; i < temp_matrix.rows; i++)
    // {
    //     for (int j = temp_matrix.row_ptr[i]; j < temp_matrix.row_ptr[i + 1]; j++)
    //     {
    //         buffer[temp_matrix.col_idx[j]] = j;
    //     }

    //     for (int col = 0; col < vector_row->cols; col++)
    //     {
    //         int sum = 0;
    //         result_matrix.row_ptr[i] = fill_index;

    //         for (int k = vector_row->row_ptr[col]; k < vector_row->row_ptr[col + 1]; k++)
    //         {
    //             if (buffer[vector_row->col_idx[k]] != -1)
    //             {
    //                 sum += vector_row->csr_values[k] * temp_matrix.csr_values[buffer[temp_matrix.col_idx[k]]]; 
    //             }
    //         }

    //         if (sum)
    //         {
    //             result_matrix.csr_values[fill_index] = sum;
    //             result_matrix.col_idx[fill_index] = i;
    //             fill_index++;
    //         } 
    //     }
 
    //     fill_invalid_values(buffer, vector_row->cols);
    // }

    // result_matrix.row_ptr[result_matrix.rows] = fill_index;

    // return result_matrix;
}
