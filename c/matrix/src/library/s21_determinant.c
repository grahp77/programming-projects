#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int ret = OK;
  double determinant = 1;
  matrix_t temp_A = {0};
  if (A == NULL || result == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (check_matrix(*A)) {
    ret = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    ret = CALCULATION_ERROR;
  } else if (s21_create_matrix(A->rows, A->columns, &temp_A)) {
    ret = CALCULATION_ERROR;
  } else
    copy_matrix(*A, &temp_A);

  double temp2 = 0;

  for (int k = 0; k < A->rows && !ret; k++) {
    if (temp_A.matrix[k][k] == 0) {
      swap_lines(&temp_A, k);
      determinant *= -1;
    }
    determinant *= temp_A.matrix[k][k];
    for (int i = k; i < A->rows; i++) {
      if (temp_A.matrix[k][k] == 0 || temp_A.matrix[i][k] == 0) {
        temp2 = 0;
      } else
        temp2 = temp_A.matrix[i][k] / temp_A.matrix[k][k];
      for (int j = k; j < A->columns; j++) {
        double temp = temp_A.matrix[i][j];
        if (i > k) {
          temp_A.matrix[i][j] = temp - 1 * temp_A.matrix[k][j] * temp2;
        }
      }
    }
  }
  *result = determinant;

  s21_remove_matrix(&temp_A);
  return ret;
}