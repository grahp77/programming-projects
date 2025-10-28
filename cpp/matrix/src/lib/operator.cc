#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      for (int i = 0; i < rows_; i++) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
      rows_ = other.rows_;
      cols_ = other.cols_;
      matrix_ = new double*[rows_];
      for (int i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_];
      }
    }
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  return *this = *this + other;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  return *this = *this - other;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  return *this = *this * other;
}

S21Matrix S21Matrix::operator*=(const double num) {
  return *this = *this * num;
}

double S21Matrix::operator()(int i, int j) const {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_) {
    throw std::out_of_range("Index out of bounds");
  }
  return this->get(i, j);
}

double S21Matrix::get(int rows, int cols) const {
  if (rows < 0 || rows >= rows_ || cols < 0 || cols >= cols_) {
    throw std::out_of_range("Index out of bounds");
  }
  return this->matrix_[rows][cols];
}

void S21Matrix::set(int rows, int cols, double num) const {
  if (rows < 0 || rows >= rows_ || cols < 0 || cols >= cols_) {
    throw std::out_of_range("Index out of bounds");
  }
  this->matrix_[rows][cols] = num;
}

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

void S21Matrix::setRows(int newRows) { this->set(newRows, cols_); }

void S21Matrix::setCols(int newCols) { this->set(rows_, newCols); }

void S21Matrix::set(int newRows, int newCols) {
  if (newRows == rows_ && newCols == cols_) {
    return;
  }
  if (newRows < 1 || newCols < 1) {
    throw std::invalid_argument("Rows must be greater than zero");
  }

  S21Matrix temp(newRows, newCols);
  int minRows = std::min(rows_, newRows);
  int minCols = std::min(cols_, newCols);
  for (int i = 0; i < minRows; i++) {
    for (int j = 0; j < minCols; j++) {
      temp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  this->swap(temp);
}

void S21Matrix::swap(S21Matrix& other) noexcept {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}