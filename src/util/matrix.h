
#ifndef __MATRIX_H_INCLUDED__
#define __MATRIX_H_INCLUDED__

typedef struct t_matrix
{
  double *mat;
  int rows;
  int columns;
} Matrix;

// Helper functions
Matrix init_mat(int rows, int columns, double values[]);
void delete_mat(Matrix mat);

// Operatios
Matrix matrix_multiply(Matrix left, Matrix right);
Matrix transpose_matrix(Matrix matrix);

#endif  //  __MATRIX_H_INCLUDED__