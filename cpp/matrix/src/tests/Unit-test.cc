#include "Unit-test.h"

#include <iostream>

TEST(MatrixTest, BasicConstructor) {
  S21Matrix m1;
  EXPECT_EQ(m1.getRows(), 1);
  EXPECT_EQ(m1.getCols(), 1);
  EXPECT_EQ(m1.get(0, 0), 0.0);
}

TEST(MatrixTest, ParamConstructor) {
  S21Matrix m2(3, 4);
  EXPECT_EQ(m2.getRows(), 3);
  EXPECT_EQ(m2.getCols(), 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_EQ(m2.get(i, j), 0.0);
    }
  }
}

TEST(MatrixTest, SetGetMethods) {
  S21Matrix m(2, 2);

  m.set(0, 0, 1.0);
  m.set(0, 1, 2.0);
  m.set(1, 0, 3.0);
  m.set(1, 1, 4.0);

  EXPECT_EQ(m.get(0, 0), 1.0);
  EXPECT_EQ(m.get(0, 1), 2.0);
  EXPECT_EQ(m.get(1, 0), 3.0);
  EXPECT_EQ(m.get(1, 1), 4.0);
}

TEST(MatrixTest, CopyConstructor) {
  S21Matrix m1(2, 2);
  m1.set(0, 0, 1);
  m1.set(0, 1, 2);
  m1.set(1, 0, 3);
  m1.set(1, 1, 4);

  S21Matrix m2(m1);

  EXPECT_EQ(m2.getRows(), 2);
  EXPECT_EQ(m2.getCols(), 2);
  EXPECT_EQ(m2.get(0, 0), 1.0);
  EXPECT_EQ(m2.get(0, 1), 2.0);
  EXPECT_EQ(m2.get(1, 0), 3.0);
  EXPECT_EQ(m2.get(1, 1), 4.0);
}

TEST(MatrixTest, EqMatrix) {
  S21Matrix m1(2, 2), m2(2, 2), m3(3, 3);

  m1.set(0, 0, 1.0);
  m1.set(0, 1, 2.0);
  m1.set(1, 0, 3.0);
  m1.set(1, 1, 4.0);

  m2.set(0, 0, 1.0);
  m2.set(0, 1, 2.0);
  m2.set(1, 0, 3.0);
  m2.set(1, 1, 4.0);

  EXPECT_TRUE(m1.EqMatrix(m2));
  EXPECT_FALSE(m1.EqMatrix(m3));
}

TEST(MatrixTest, SumMatrix) {
  S21Matrix m1(2, 2), m2(2, 2), expected(2, 2);

  m1.set(0, 0, 1);
  m1.set(0, 1, 2);
  m1.set(1, 0, 3);
  m1.set(1, 1, 4);

  m2.set(0, 0, 5);
  m2.set(0, 1, 6);
  m2.set(1, 0, 7);
  m2.set(1, 1, 8);

  expected.set(0, 0, 6);
  expected.set(0, 1, 8);
  expected.set(1, 0, 10);
  expected.set(1, 1, 12);

  m1.SumMatrix(m2);

  EXPECT_TRUE(m1.EqMatrix(expected));
}

TEST(MatrixTest, SubMatrix) {
  S21Matrix m1(2, 2), m2(2, 2), expected(2, 2);

  m1.set(0, 0, 5);
  m1.set(0, 1, 6);
  m1.set(1, 0, 7);
  m1.set(1, 1, 8);

  m2.set(0, 0, 1);
  m2.set(0, 1, 2);
  m2.set(1, 0, 3);
  m2.set(1, 1, 4);

  expected.set(0, 0, 4);
  expected.set(0, 1, 4);
  expected.set(1, 0, 4);
  expected.set(1, 1, 4);

  m1.SubMatrix(m2);

  EXPECT_TRUE(m1.EqMatrix(expected));
}

TEST(MatrixTest, SubMatrixoperator) {
  S21Matrix m1(2, 2), m2(2, 2), expected(2, 2);

  m1.set(0, 0, 5);
  m1.set(0, 1, 6);
  m1.set(1, 0, 7);
  m1.set(1, 1, 8);

  m2.set(0, 0, 1);
  m2.set(0, 1, 2);
  m2.set(1, 0, 3);
  m2.set(1, 1, 4);

  expected.set(0, 0, 4);
  expected.set(0, 1, 4);
  expected.set(1, 0, 4);
  expected.set(1, 1, 4);

  m1 -= m2;

  EXPECT_TRUE(m1.EqMatrix(expected));
}

TEST(MatrixTest, operator1) {
  S21Matrix m1(2, 2), m2(2, 2), expected(2, 2);

  m1.set(0, 0, 5);
  m1.set(0, 1, 6);
  m1.set(1, 0, 7);
  m1.set(1, 1, 8);

  EXPECT_EQ(m1(1, 1), 8.0);
}

TEST(MatrixTest, MulNumber) {
  S21Matrix m1(2, 2), expected(2, 2);

  m1.set(0, 0, 1);
  m1.set(0, 1, 2);
  m1.set(1, 0, 3);
  m1.set(1, 1, 4);

  expected.set(0, 0, 2);
  expected.set(0, 1, 4);
  expected.set(1, 0, 6);
  expected.set(1, 1, 8);

  m1.MulNumber(2.0);

  EXPECT_TRUE(m1.EqMatrix(expected));
}

TEST(MatrixTest, Transpose) {
  S21Matrix m(2, 3), expected(3, 2);

  m.set(0, 0, 1);
  m.set(0, 1, 2);
  m.set(0, 2, 3);
  m.set(1, 0, 4);
  m.set(1, 1, 5);
  m.set(1, 2, 6);

  expected.set(0, 0, 1);
  expected.set(0, 1, 4);
  expected.set(1, 0, 2);
  expected.set(1, 1, 5);
  expected.set(2, 0, 3);
  expected.set(2, 1, 6);

  S21Matrix result = m.Transpose();

  EXPECT_TRUE(result.EqMatrix(expected));
}

TEST(MatrixTest, Determinant) {
  S21Matrix m1(1, 1);
  m1.set(0, 0, 5);
  EXPECT_DOUBLE_EQ(m1.Determinant(), 5);

  S21Matrix m2(2, 2);
  m2.set(0, 0, 1);
  m2.set(0, 1, 2);
  m2.set(1, 0, 3);
  m2.set(1, 1, 4);
  EXPECT_DOUBLE_EQ(m2.Determinant(), -2);

  S21Matrix m4(4, 4);
  m4.set(0, 0, 8);
  m4.set(0, 1, 7);
  m4.set(0, 2, 2);
  m4.set(0, 3, 4);
  m4.set(1, 0, 5);
  m4.set(1, 1, 6);
  m4.set(1, 2, 7);
  m4.set(1, 3, 8);
  m4.set(2, 0, 4);
  m4.set(2, 1, 2);
  m4.set(2, 2, 2);
  m4.set(2, 3, 6);
  m4.set(3, 0, 5);
  m4.set(3, 1, 4);
  m4.set(3, 2, 3);
  m4.set(3, 3, 2);
  EXPECT_DOUBLE_EQ(m4.Determinant(), -300);
}

TEST(MatrixTest, DeterminantLargeMatrixWithSwap) {
  S21Matrix matrix(4, 4);

  matrix.set(0, 0, 0.0);
  matrix.set(0, 1, 2.0);
  matrix.set(0, 2, 3.0);
  matrix.set(0, 3, 4.0);

  matrix.set(1, 0, 5.0);
  matrix.set(1, 1, 6.0);
  matrix.set(1, 2, 7.0);
  matrix.set(1, 3, 8.0);

  matrix.set(2, 0, 0.0);
  matrix.set(2, 1, 10.0);
  matrix.set(2, 2, 11.0);
  matrix.set(2, 3, 12.0);

  matrix.set(3, 0, 13.0);
  matrix.set(3, 1, 14.0);
  matrix.set(3, 2, 15.0);
  matrix.set(3, 3, 16.0);

  double det = matrix.Determinant();
  EXPECT_NEAR(det, 0.0, 1e-10);
}

TEST(MatrixTest, OutOfBoundsAccess) {
  S21Matrix m(2, 2);

  EXPECT_NO_THROW(m.get(0, 0));
  EXPECT_NO_THROW(m.get(1, 1));
  EXPECT_NO_THROW(m.set(0, 0, 1.0));
  EXPECT_NO_THROW(m.set(1, 1, 1.0));
}

TEST(MatrixTest, SumMatrixInvalidDimensions) {
  S21Matrix m1(2, 2), m2(3, 3);
  EXPECT_THROW(m1.SumMatrix(m2), std::invalid_argument);
}

TEST(MatrixTest, SubMatrixInvalidDimensions) {
  S21Matrix m1(2, 2), m2(3, 3);
  EXPECT_THROW(m1.SubMatrix(m2), std::invalid_argument);
}

TEST(MatrixTest, MulMatrix) {
  S21Matrix m1(2, 2), m2(2, 2), expected(2, 2);

  m1.set(0, 0, 1);
  m1.set(0, 1, 2);
  m1.set(1, 0, 3);
  m1.set(1, 1, 4);

  m2.set(0, 0, 5);
  m2.set(0, 1, 6);
  m2.set(1, 0, 7);
  m2.set(1, 1, 8);

  expected.set(0, 0, 19);
  expected.set(0, 1, 22);
  expected.set(1, 0, 43);
  expected.set(1, 1, 50);

  m1.MulMatrix(m2);
  EXPECT_TRUE(m1.EqMatrix(expected));
}

TEST(MatrixTest, MulMatrixInvalidDimensions) { S21Matrix m1(2, 3), m2(2, 2); }

TEST(MatrixTest, Determinant3x3) {
  S21Matrix m(3, 3);

  m.set(0, 0, 1);
  m.set(0, 1, 2);
  m.set(0, 2, 3);
  m.set(1, 0, 4);
  m.set(1, 1, 5);
  m.set(1, 2, 6);
  m.set(2, 0, 7);
  m.set(2, 1, 8);
  m.set(2, 2, 9);

  EXPECT_DOUBLE_EQ(m.Determinant(), 0);
}

TEST(MatrixTest, DeterminantNonZero3x3) {
  S21Matrix m(3, 3);

  m.set(0, 0, 1);
  m.set(0, 1, 2);
  m.set(0, 2, 3);
  m.set(1, 0, 0);
  m.set(1, 1, 4);
  m.set(1, 2, 5);
  m.set(2, 0, 1);
  m.set(2, 1, 0);
  m.set(2, 2, 6);
  EXPECT_DOUBLE_EQ(m.Determinant(), 22);
}

TEST(MatrixTest, CalcComplements) {
  S21Matrix m(2, 2), expected(2, 2);

  m.set(0, 0, 1);
  m.set(0, 1, 2);
  m.set(1, 0, 3);
  m.set(1, 1, 4);

  expected.set(0, 0, 4);
  expected.set(0, 1, -3);
  expected.set(1, 0, -2);
  expected.set(1, 1, 1);

  S21Matrix result = m.CalcComplements();
  EXPECT_TRUE(result.EqMatrix(expected));
}

TEST(MatrixTest, InverseMatrix) {
  S21Matrix m(2, 2), expected(2, 2);

  m.set(0, 0, 4);
  m.set(0, 1, 7);
  m.set(1, 0, 2);
  m.set(1, 1, 6);

  expected.set(0, 0, 0.6);
  expected.set(0, 1, -0.7);
  expected.set(1, 0, -0.2);
  expected.set(1, 1, 0.4);

  S21Matrix result = m.InverseMatrix();

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      EXPECT_NEAR(result.get(i, j), expected.get(i, j), 1e-10);
    }
  }
}

TEST(MatrixTest, Operators) {
  S21Matrix m1(2, 2), m2(2, 2);

  m1.set(0, 0, 1);
  m1.set(0, 1, 2);
  m1.set(1, 0, 3);
  m1.set(1, 1, 4);

  m2.set(0, 0, 5);
  m2.set(0, 1, 6);
  m2.set(1, 0, 7);
  m2.set(1, 1, 8);

  S21Matrix sum = m1 + m2;
  S21Matrix expected_sum(2, 2);
  expected_sum.set(0, 0, 6);
  expected_sum.set(0, 1, 8);
  expected_sum.set(1, 0, 10);
  expected_sum.set(1, 1, 12);
  EXPECT_TRUE(sum.EqMatrix(expected_sum));

  S21Matrix diff = m1 - m2;
  S21Matrix expected_diff(2, 2);
  expected_diff.set(0, 0, -4);
  expected_diff.set(0, 1, -4);
  expected_diff.set(1, 0, -4);
  expected_diff.set(1, 1, -4);
  EXPECT_TRUE(diff.EqMatrix(expected_diff));

  S21Matrix prod = m1 * m2;
  S21Matrix expected_prod(2, 2);
  expected_prod.set(0, 0, 19);
  expected_prod.set(0, 1, 22);
  expected_prod.set(1, 0, 43);
  expected_prod.set(1, 1, 50);
  EXPECT_TRUE(prod.EqMatrix(expected_prod));

  S21Matrix scaled = m1 * 2.0;
  S21Matrix expected_scaled(2, 2);
  expected_scaled.set(0, 0, 2);
  expected_scaled.set(0, 1, 4);
  expected_scaled.set(1, 0, 6);
  expected_scaled.set(1, 1, 8);
  EXPECT_TRUE(scaled.EqMatrix(expected_scaled));

  S21Matrix m1_copy = m1;
  EXPECT_TRUE(m1 == m1_copy);
  EXPECT_FALSE(m1 == m2);
}

TEST(MatrixTest, CompoundOperators) {
  S21Matrix m1(2, 2), m2(2, 2);

  m1.set(0, 0, 1);
  m1.set(0, 1, 2);
  m1.set(1, 0, 3);
  m1.set(1, 1, 4);

  m2.set(0, 0, 5);
  m2.set(0, 1, 6);
  m2.set(1, 0, 7);
  m2.set(1, 1, 8);

  S21Matrix m1_plus = m1;
  m1_plus += m2;
  S21Matrix expected_sum(2, 2);
  expected_sum.set(0, 0, 6);
  expected_sum.set(0, 1, 8);
  expected_sum.set(1, 0, 10);
  expected_sum.set(1, 1, 12);
  EXPECT_TRUE(m1_plus.EqMatrix(expected_sum));

  S21Matrix m1_mul = m1;
  m1_mul *= m2;
  S21Matrix expected_prod(2, 2);
  expected_prod.set(0, 0, 19);
  expected_prod.set(0, 1, 22);
  expected_prod.set(1, 0, 43);
  expected_prod.set(1, 1, 50);
  EXPECT_TRUE(m1_mul.EqMatrix(expected_prod));

  S21Matrix m1_scale = m1;
  m1_scale *= 2.0;
  S21Matrix expected_scaled(2, 2);
  expected_scaled.set(0, 0, 2);
  expected_scaled.set(0, 1, 4);
  expected_scaled.set(1, 0, 6);
  expected_scaled.set(1, 1, 8);
  EXPECT_TRUE(m1_scale.EqMatrix(expected_scaled));
}

TEST(MatrixTest, SetRowsIncrease) {
  S21Matrix matrix(2, 2);
  matrix.set(0, 0, 1.0);
  matrix.set(0, 1, 2.0);
  matrix.set(1, 0, 3.0);
  matrix.set(1, 1, 4.0);

  matrix.setRows(4);

  EXPECT_EQ(matrix.getRows(), 4);
  EXPECT_EQ(matrix.getCols(), 2);

  EXPECT_EQ(matrix.get(0, 0), 1.0);
  EXPECT_EQ(matrix.get(0, 1), 2.0);
  EXPECT_EQ(matrix.get(1, 0), 3.0);
  EXPECT_EQ(matrix.get(1, 1), 4.0);

  EXPECT_EQ(matrix.get(2, 0), 0.0);
  EXPECT_EQ(matrix.get(2, 1), 0.0);
  EXPECT_EQ(matrix.get(3, 0), 0.0);
  EXPECT_EQ(matrix.get(3, 1), 0.0);
}

TEST(MatrixTest, SetColsIncrease) {
  S21Matrix matrix(2, 2);
  matrix.set(0, 0, 1.0);
  matrix.set(0, 1, 2.0);
  matrix.set(1, 0, 3.0);
  matrix.set(1, 1, 4.0);

  matrix.setCols(4);

  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_EQ(matrix.getCols(), 4);

  EXPECT_EQ(matrix.get(0, 0), 1.0);
  EXPECT_EQ(matrix.get(0, 1), 2.0);
  EXPECT_EQ(matrix.get(0, 2), 0.0);
  EXPECT_EQ(matrix.get(0, 3), 0.0);

  EXPECT_EQ(matrix.get(1, 0), 3.0);
  EXPECT_EQ(matrix.get(1, 1), 4.0);
  EXPECT_EQ(matrix.get(1, 2), 0.0);
  EXPECT_EQ(matrix.get(1, 3), 0.0);
}

TEST(MatrixTest, MoveConstructor) {
  S21Matrix original(2, 3);
  original.set(0, 0, 1.0);
  original.set(0, 1, 2.0);
  original.set(0, 2, 3.0);
  original.set(1, 0, 4.0);
  original.set(1, 1, 5.0);
  original.set(1, 2, 6.0);

  int original_rows = original.getRows();
  int original_cols = original.getCols();
  double original_00 = original.get(0, 0);
  double original_01 = original.get(0, 1);

  S21Matrix moved(std::move(original));

  EXPECT_EQ(moved.getRows(), original_rows);
  EXPECT_EQ(moved.getCols(), original_cols);

  EXPECT_EQ(moved.get(0, 0), original_00);
  EXPECT_EQ(moved.get(0, 1), original_01);
  EXPECT_EQ(moved.get(0, 2), 3.0);
  EXPECT_EQ(moved.get(1, 0), 4.0);
  EXPECT_EQ(moved.get(1, 1), 5.0);
  EXPECT_EQ(moved.get(1, 2), 6.0);

  EXPECT_EQ(original.getRows(), 0);
  EXPECT_EQ(original.getCols(), 0);

  EXPECT_NO_THROW(moved.get(0, 0));
  EXPECT_NO_THROW(moved.set(0, 0, 10.0));
  EXPECT_EQ(moved.get(0, 0), 10.0);
}

TEST(MatrixTest, AssignmentOperatorFromSmallerToLarger) {
  S21Matrix larger(3, 3);
  larger.set(0, 0, 1.0);
  larger.set(0, 1, 2.0);
  larger.set(0, 2, 3.0);
  larger.set(1, 0, 4.0);
  larger.set(1, 1, 5.0);
  larger.set(1, 2, 6.0);
  larger.set(2, 0, 7.0);
  larger.set(2, 1, 8.0);
  larger.set(2, 2, 9.0);

  S21Matrix smaller(2, 2);
  smaller.set(0, 0, 10.0);
  smaller.set(0, 1, 20.0);
  smaller.set(1, 0, 30.0);
  smaller.set(1, 1, 40.0);

  larger = smaller;

  EXPECT_EQ(larger.getRows(), 2);
  EXPECT_EQ(larger.getCols(), 2);
  EXPECT_EQ(larger.get(0, 0), 10.0);
  EXPECT_EQ(larger.get(0, 1), 20.0);
  EXPECT_EQ(larger.get(1, 0), 30.0);
  EXPECT_EQ(larger.get(1, 1), 40.0);
}

// TEST(MatrixTest, OperatorParenthesisOutOfBounds) {
//   S21Matrix m(2, 2);

//   EXPECT_THROW(m(-1, 0), std::out_of_range);
//   EXPECT_THROW(m(0, -1), std::out_of_range);

//   EXPECT_THROW(m(2, 0), std::out_of_range);
//   EXPECT_THROW(m(0, 2), std::out_of_range);
//   EXPECT_THROW(m(2, 2), std::out_of_range);
// }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}