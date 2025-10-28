#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::CalcComplements() {
  double determinant = 0;
  S21Matrix tempMatrix(*this);
  S21Matrix resultMatrix(rows_, cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      S21Matrix sMatrix = tempMatrix.smallMatrix(i, j);
      determinant = sMatrix.Determinant();
      resultMatrix.matrix_[i][j] = determinant * pow(-1, i + j);
    }
  }
  return resultMatrix;
};