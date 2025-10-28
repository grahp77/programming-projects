#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>
#include <random>
#include <stdexcept>
using namespace std;

class S21Matrix {
 public:
  bool EqMatrix(
      const S21Matrix& other);  // Проверяет матрицы на равенство между собой.
  void SumMatrix(
      const S21Matrix& other);  // Прибавляет вторую матрицу к текущей
  void SubMatrix(const S21Matrix& other);  // Вычитает из текущей матрицы другую
  void MulNumber(const double num);        // Умножает текущую матрицу на число.
  void MulMatrix(
      const S21Matrix& other);  // Умножает текущую матрицу на вторую.
  S21Matrix Transpose();  // Создает новую транспонированную матрицу из текущей
                          // и возвращает ее.
  S21Matrix CalcComplements();  // Вычисляет матрицу алгебраических дополнений
                                // текущей матрицы и возвращает ее.
  double Determinant();  // Вычисляет и возвращает определитель текущей матрицы.
  S21Matrix InverseMatrix();  // Вычисляет и возвращает обратную матрицу.

  S21Matrix();  // Базовый конструктор, инициализирующий матрицу некоторой
                // заранее заданной размерностью.

  S21Matrix(int rows, int cols);  // Параметризированный конструктор с
                                  // количеством строк и столбцов.

  S21Matrix(const S21Matrix& other);  // Конструктор копирования.

  S21Matrix(S21Matrix&& other) noexcept;  // Конструктор переноса.

  ~S21Matrix();  // Деструктор.

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);

  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);
  double operator()(int i, int j) const;
  int getRows() const;
  int getCols() const;
  void setRows(int newRows);
  void setCols(int newCols);
  void swap(S21Matrix& other) noexcept;
  void set(int rows, int cols, double num) const;
  double get(int rows, int cols) const;

 private:
  int rows_, cols_;
  double** matrix_;

  void set(int newRows, int newCols);
  void swapLines(int k);
  S21Matrix smallMatrix(int i, int j);
};

#endif