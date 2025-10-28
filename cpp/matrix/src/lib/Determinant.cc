#include "../s21_matrix_oop.h"

double S21Matrix::Determinant() {
  double determinant = 1;
  double temp2 = 0;
  S21Matrix tempMatrix(*this);
  for (int k = 0; k < rows_; k++) {
    if (tempMatrix.matrix_[k][k] == 0) {
      tempMatrix.swapLines(k);
      determinant *= -1;
    }
    determinant *= tempMatrix.matrix_[k][k];
    for (int i = k; i < rows_; i++) {
      if (tempMatrix.matrix_[k][k] == 0 || tempMatrix.matrix_[i][k] == 0) {
        temp2 = 0;
      } else
        temp2 = tempMatrix.matrix_[i][k] / tempMatrix.matrix_[k][k];
      for (int j = k; j < cols_; j++) {
        double temp = tempMatrix.matrix_[i][j];
        if (i > k) {
          tempMatrix.matrix_[i][j] =
              temp - 1 * tempMatrix.matrix_[k][j] * temp2;
        }
      }
    }
  }
  return determinant;
};