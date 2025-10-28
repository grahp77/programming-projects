#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret = OK;
  if (A == NULL || result == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (check_matrix(*A)) {
    ret = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, A->columns, result)) {
    ret = INCORRECT_MATRIX;
  }

  for (int i = 0; i < A->rows && !ret; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return ret;
}