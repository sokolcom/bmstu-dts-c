#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_

void std_transpose(stdMatrix_t *const matrix);

stdMatrix_t std_m12n(stdMatrix_t *vector_row, stdMatrix_t *matrix);
sparseMatrix_t sparse_m12n(stdMatrix_t *vector_row, sparseMatrix_t *matrix);

#endif