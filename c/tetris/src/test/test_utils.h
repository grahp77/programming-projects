#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdlib.h>

#include "test.h"

int matrixesAreReset(GameInfo_t *CurrentState);
int matricesAreEqual(int **matrix1, int **matrix2);
int matricesAreEqualField(int **matrix1, int **matrix2);

#endif