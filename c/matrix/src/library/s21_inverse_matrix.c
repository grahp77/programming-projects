#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int ret = OK;
  double determinant = 0;
  if (A == NULL || result == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    ret = CALCULATION_ERROR;
  }
  matrix_t temp_A = {0};
  matrix_t temp_temp = {0};

  if (!ret) {
    ret = s21_determinant(A, &determinant);
    if (!determinant) ret = CALCULATION_ERROR;
  }
  if (!ret) {
    ret = s21_create_matrix(A->rows, A->columns, &temp_A);
  }
  if (!ret) {
    copy_matrix(*A, &temp_A);
    ret = s21_create_matrix(A->rows, A->columns, result);
  }

  if (!ret && temp_A.rows == 1) {
    result->matrix[0][0] = 1 / temp_A.matrix[0][0];
    s21_remove_matrix(&temp_A);
  } else {
    if (!ret) {
      ret = s21_calc_complements(&temp_A, &temp_temp);
    }
    if (!ret) {
      copy_matrix(temp_temp, &temp_A);
      s21_remove_matrix(&temp_temp);
      ret = s21_transpose(&temp_A, &temp_temp);
    }
    if (!ret) {
      s21_remove_matrix(result);
      ret = s21_mult_number(&temp_temp, 1 / determinant, result);
    }
    s21_remove_matrix(&temp_temp);
    s21_remove_matrix(&temp_A);
  }

  return ret;
}