#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int ret = OK;
  if (A->rows < 1 || A->columns < 1 || result == NULL) {
    return INCORRECT_MATRIX;
  }
  matrix_t temp_A;

  if (A == NULL || result == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, A->columns, &temp_A)) {
    ret = INCORRECT_MATRIX;
  }
  copy_matrix(*A, &temp_A);
  if (s21_create_matrix(A->columns, A->rows, result)) {
    ret = INCORRECT_MATRIX;
  }
  for (int i = 0; i < A->columns && !ret; i++) {
    for (int j = 0; j < A->rows; j++) {
      result->matrix[i][j] = temp_A.matrix[j][i];
    }
  }
  s21_remove_matrix(&temp_A);
  return ret;
}