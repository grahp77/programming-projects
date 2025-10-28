#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = OK;
  if (A == NULL || B == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (check_matrix(*A) || check_matrix(*B)) {
    ret = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    ret = CALCULATION_ERROR;
  } else if (s21_create_matrix(A->rows, B->columns, result)) {
    ret = INCORRECT_MATRIX;
  }
  double AB = 0;
  for (int i = 0; i < A->rows && !ret; i++) {
    for (int j = 0; j < B->columns; j++) {
      for (int k = 0; k < A->columns; k++) {
        AB = A->matrix[i][k] * B->matrix[k][j];
        result->matrix[i][j] = AB + result->matrix[i][j];
      }
    }
  }
  return ret;
}