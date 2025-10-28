#include "../s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = OK;
  if (A == NULL || B == NULL || result == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (check_matrix(*A) || check_matrix(*B)) {
    ret = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    ret = CALCULATION_ERROR;
  } else if (s21_create_matrix(A->rows, A->columns, result)) {
    ret = INCORRECT_MATRIX;
  }

  for (int i = 0; i < A->rows && !ret; i++) {
    for (int j = 0; j < A->columns && !ret; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }
  return ret;
}