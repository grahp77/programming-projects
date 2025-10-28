#include "../s21_matrix.h"

matrix_t small_matrix(matrix_t A, matrix_t temp, int rows, int columns) {
  for (int i = 0, i1 = 0; i < temp.rows; i++, i1++) {
    if (i1 == rows) i1++;
    for (int j = 0, j1 = 0; j < temp.columns; j++, j1++) {
      if (j1 == columns) j1++;
      temp.matrix[i][j] = A.matrix[i1][j1];
    }
  }
  return temp;
}

void copy_matrix(matrix_t A, matrix_t *copy) {
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      copy->matrix[i][j] = A.matrix[i][j];
    }
  }
}

void swap_lines(matrix_t *A, int k) {
  for (int i = k + 1, j = 0; i < A->rows && j < A->rows; i++) {
    if (A->matrix[i][k] != 0) {
      for (; j < A->columns; j++) {
        double tmp = A->matrix[k][j];
        A->matrix[k][j] = A->matrix[i][j];
        A->matrix[i][j] = tmp;
      }
    }
  }
}

int check_matrix(matrix_t A) {
  int ret = OK;
  if (A.rows < 1 || A.columns < 1) {
    ret = INCORRECT_MATRIX;
  }
  return ret;
}