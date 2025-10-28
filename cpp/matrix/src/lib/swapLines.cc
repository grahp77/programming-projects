#include "../s21_matrix_oop.h"

void S21Matrix::swapLines(int k) {
  for (int i = k + 1, j = 0; i < rows_ && j < rows_; i++) {
    if (matrix_[i][k] != 0) {
      for (; j < cols_; j++) {
        double tmp = matrix_[k][j];
        matrix_[k][j] = matrix_[i][j];
        matrix_[i][j] = tmp;
      }
    }
  }
};