#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int ret = SUCCESS;
  double eps = 1e-7;
  if (A == NULL || B == NULL) {
    ret = FAILURE;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    ret = FAILURE;
  }

  for (int i = 0; i < A->rows && ret; i++) {
    for (int j = 0; j < A->columns && ret; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > eps) {
        ret = FAILURE;
      }
    }
  }
  return ret;
}