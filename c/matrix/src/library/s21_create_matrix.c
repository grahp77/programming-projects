#include "../s21_matrix.h"

int s21_create_matrix(int rows, int cols, matrix_t *result) {
  int ret = OK;

  if (rows <= 0 || cols <= 0 || result == NULL) {
    return INCORRECT_MATRIX;
  }
  if (!ret) {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      ret = INCORRECT_MATRIX;
    }

    for (int i = 0; i < rows && ret == OK; i++) {
      result->matrix[i] = (double *)calloc(cols, sizeof(double));
      if (result->matrix[i] == NULL) {
        for (int k = 0; k < i; k++) {
          free(result->matrix[k]);
        }
        free(result->matrix);
        result->matrix = NULL;
        ret = INCORRECT_MATRIX;
      }
    }
  }
  if (!ret) {
    result->rows = rows;
    result->columns = cols;
  }
  return ret;
}