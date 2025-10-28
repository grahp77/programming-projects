#include "../s21_matrix_oop.h"

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Matrix dimensions don't match for multiplication");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < this->cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  this->swap(result);
};