#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::smallMatrix(int rows, int cols) {
  S21Matrix sMatrix(rows_ - 1, cols_ - 1);
  for (int i = 0, i1 = 0; i < rows_ - 1; i++, i1++) {
    if (i1 == rows) i1++;
    for (int j = 0, j1 = 0; j < cols_ - 1; j++, j1++) {
      if (j1 == cols) j1++;
      sMatrix.matrix_[i][j] = this->matrix_[i1][j1];
    }
  }
  return sMatrix;
}