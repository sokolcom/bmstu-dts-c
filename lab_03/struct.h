#ifndef _STRUCT_H_
#define _STRUCT_H_

#define MAX_DIME 100

// Sparse matrix
typedef struct
{
    int csr_values[MAX_DIME * MAX_DIME];
    int col_idx[MAX_DIME * MAX_DIME];
    int row_ptr[MAX_DIME + 1];
    int rows;
    int cols;
} sparseMatrix_t;


// Normal (trivial) matrix
typedef struct
{
    int matrix[MAX_DIME][MAX_DIME];
    int rows;
    int cols;
} stdMatrix_t;

#endif
