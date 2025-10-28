#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::logic_error("Matrix is not square");
  }
  S21Matrix resultMatrix(rows_, cols_);

  double determinant = this->Determinant();
  if (fabs(determinant) < 1e-7) {
    throw std::logic_error("Matrix is not square");
  }
  S21Matrix tempMatrix1(*this);

  if (rows_ == 1) {
    resultMatrix.matrix_[0][0] = 1 / tempMatrix1.matrix_[0][0];
  } else {
    S21Matrix tempMatrix2 = tempMatrix1.CalcComplements();
    resultMatrix = tempMatrix2.Transpose();
    resultMatrix.MulNumber(1 / determinant);
  }
  return resultMatrix;
};