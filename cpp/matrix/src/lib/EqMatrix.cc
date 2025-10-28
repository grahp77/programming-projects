#include "../s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  const double eps = 1e-7;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > eps) {
        return false;
      }
    }
  }
  return true;
};