#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int ret = OK;

  double determinant = 0.;
  if (A == NULL || result == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    ret = CALCULATION_ERROR;
  } else if (check_matrix(*A)) {
    ret = INCORRECT_MATRIX;
  }
  matrix_t temp_small = {0};
  matrix_t temp_A = {0};
  if (!ret) {
    s21_create_matrix(A->rows - 1, A->columns - 1, &temp_small);
    s21_create_matrix(A->rows, A->columns, &temp_A);
    copy_matrix(*A, &temp_A);
  }
  if (!ret) {
    ret = s21_create_matrix(A->rows, A->columns, result);
  }

  for (int i = 0; i < temp_A.rows && !ret; i++) {
    for (int j = 0; j < temp_A.columns; j++) {
      temp_small = small_matrix(temp_A, temp_small, i, j);
      s21_determinant(&temp_small, &determinant);
      result->matrix[i][j] = determinant * pow(-1, i + j);
    }
  }
  if (!ret) {
    s21_remove_matrix(&temp_small);
    s21_remove_matrix(&temp_A);
  }
  return ret;
}