#ifndef _MATRIX_IO_H_
#define _MATRIX_IO_H_

sparseMatrix_t transform_to_sparse(stdMatrix_t matrix);

stdMatrix_t input_std_matrix(const type_t type);
sparseMatrix_t input_sparse_matrix(const type_t type);

stdMatrix_t generate_trivial(const int row_amount, const int col_amount, const int percentage);
sparseMatrix_t generate_sparse(const int row_amount, const int col_amount, const int percentage);

int std_random_generation(stdMatrix_t *const vector_row, stdMatrix_t *const matrix);
int sparse_random_generation(stdMatrix_t *const vector_row, sparseMatrix_t *const matrix);

void print_std_matrix(const stdMatrix_t *const matrix);
void print_std_by_coords(const stdMatrix_t *const matrix);
void print_sparse_by_coords(const sparseMatrix_t *const matrix);
void print_sparse_to_std(const sparseMatrix_t *const matrix);
void print_sparse(const sparseMatrix_t *const matrix);

void print_stats();

#endif
