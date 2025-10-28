#include "../s21_matrix_oop.h"

S21Matrix::S21Matrix(int rows, int cols)
    : rows_(0), cols_(0), matrix_(nullptr) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("The argument must be greater than zero.");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::S21Matrix() : rows_(1), cols_(1) {
  matrix_ = new double*[rows_]();
  matrix_[0] = new double[cols_]();
  matrix_[0][0] = 0.0;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
  }
}