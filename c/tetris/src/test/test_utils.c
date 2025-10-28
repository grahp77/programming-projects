#include "test_utils.h"

int matrixesAreReset(GameInfo_t *CurrentState) {
  int flag = 1;  // Матрица обнулена
  for (int i = 0; i < 4 && flag; i++) {
    for (int j = 0; j < 4 && flag; j++) {
      if (CurrentState->next[i][j]) {
        flag = 0;  // Матрица не обнулена
      }
    }
  }
  return flag;
}

int matricesAreEqual(int **matrix1, int **matrix2) {
  int flag = 1;
  for (int i = 0; i < 4 && flag; i++) {
    for (int j = 0; j < 4 && flag; j++) {
      if (matrix1[i][j] != matrix2[i][j]) {
        flag = 0;  // Матрицы не равны
      }
    }
  }
  return flag;  // Матрицы равны
}

int matricesAreEqualField(int **matrix1, int **matrix2) {
  int flag = 1;
  for (int i = 0; i < 20 && flag; i++) {
    for (int j = 0; j < 10 && flag; j++) {
      if (matrix1[i][j] != matrix2[i][j]) {
        flag = 0;  // Матрицы не равны
      }
    }
  }
  return flag;  // Матрицы равны
}