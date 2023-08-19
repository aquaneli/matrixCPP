#include <gtest/gtest.h>

#include "matrix_oop.h"

TEST(Constructor, test_1) {
  S21Matrix a;
  S21Matrix b(a);

  b.SetRows(1);
  b.SetCols(2);

  a.SetRows(5);
  a.SetCols(5);

  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;
  a(0, 3) = 5.0001;
  a(0, 4) = 10.0123;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;
  a(1, 3) = 8.0;
  a(1, 4) = 9.003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;
  a(2, 3) = 3.0;
  a(2, 4) = 2.003;

  a(3, 0) = 3.0;
  a(3, 1) = 5.0;
  a(3, 2) = 9.00003;
  a(3, 3) = 3.0;
  a(3, 4) = 10.003;

  a(4, 0) = 7.0;
  a(4, 1) = 8.0;
  a(4, 2) = 3.00003;
  a(4, 3) = 4.0;
  a(4, 4) = 8.003;

  b = a;

  EXPECT_EQ(a.GetRows(), 5);
  EXPECT_EQ(a.GetCols(), 5);

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j));
    }
  }
}

TEST(Constructor, test_2) {
  S21Matrix a(0, -1);

  a.SetRows(5);
  a.SetCols(5);

  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;
  a(0, 3) = 5.0001;
  a(0, 4) = 10.0123;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;
  a(1, 3) = 8.0;
  a(1, 4) = 9.003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;
  a(2, 3) = 3.0;
  a(2, 4) = 2.003;

  a(3, 0) = 3.0;
  a(3, 1) = 5.0;
  a(3, 2) = 9.00003;
  a(3, 3) = 3.0;
  a(3, 4) = 10.003;

  a(4, 0) = 7.0;
  a(4, 1) = 8.0;
  a(4, 2) = 3.00003;
  a(4, 3) = 4.0;
  a(4, 4) = 8.003;

  EXPECT_EQ(a.GetRows(), 5);
  EXPECT_EQ(a.GetCols(), 5);

  S21Matrix b = a;

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j));
    }
  }
}

TEST(Constructor, test_3) {
  S21Matrix a = S21Matrix(1, 1);
  S21Matrix b = a;
  b.SetCols(a.GetCols() + 1);
  EXPECT_EQ(a.GetCols() + 1, b.GetCols());
}

TEST(Constructor, test_4) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(-1, 0);

  b = a;

  EXPECT_EQ(a.GetCols(), b.GetCols());
}

TEST(Constructor, test_5) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix tmp = a;

  S21Matrix b(std::move(a));

  EXPECT_THROW(b(5, 0), std::length_error);

  EXPECT_EQ(tmp.GetCols(), b.GetCols());
}

TEST(Eq, test_6) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix tmp = a;
  S21Matrix b(std::move(a));
  EXPECT_EQ(tmp.GetCols(), b.GetCols());
  EXPECT_EQ(tmp.EqMatrix(b), true);
}

TEST(Eq, test_7) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix tmp = a;
  S21Matrix b(std::move(a));
  b(1, 2) = 6.000003;
  EXPECT_EQ(tmp.GetCols(), b.GetCols());
  EXPECT_EQ(tmp.EqMatrix(b), false);
}

TEST(Eq, test_8) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix tmp = a;
  S21Matrix b(std::move(a));
  EXPECT_EQ(tmp.GetCols(), b.GetCols());

  b.SetRows(5);
  b.SetCols(5);

  b(4, 1) = 6.000003;

  EXPECT_EQ(tmp.EqMatrix(b), false);
}

TEST(SumMatrix, test_9) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.SumMatrix(a);

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) - a(i, j));
    }
  }
}

TEST(SumMatrix, test_10) {
  S21Matrix a(3, 4);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.SetRows(5);

  EXPECT_THROW(b.SumMatrix(a), std::length_error);

  b.SetRows(3);

  a.SumMatrix(b * 2);

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ((a(i, j) - b(i, j) * 2), b(i, j));
    }
  }
}

TEST(SumMatrix, test_11) {
  S21Matrix a(1, 15);
  S21Matrix b(1, 15);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = i + j * 1.73;
    }
  }

  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      b(i, j) = i * 0.25 + j;
    }
  }

  a.SumMatrix(b);

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) + (i + j * 1.73));
    }
  }
}

TEST(SubMatrix, test_12) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.SubMatrix(a);

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) + a(i, j));
    }
  }
}

TEST(SumMatrix, test_13) {
  S21Matrix a(3, 4);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.SetRows(5);

  EXPECT_THROW(b.SubMatrix(a), std::length_error);

  b.SetRows(3);

  a.SubMatrix(b * 2);

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ((a(i, j) + b(i, j) * 2), b(i, j));
    }
  }
}

TEST(SumMatrix, test_14) {
  S21Matrix a(3, 4);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.SetRows(5);

  EXPECT_THROW(b.SubMatrix(a), std::length_error);

  b.SetRows(3);

  a.SubMatrix(b * 2);

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ((a(i, j) + b(i, j) * 2), b(i, j));
    }
  }
}

TEST(MulNumber, test_15) {
  S21Matrix a(3, 4);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);

  b.SetRows(0);
  EXPECT_THROW(b.MulNumber(3), std::length_error);

  b = a;
  b.MulNumber(3);

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }
}

TEST(MulMatrix, test_16) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);

  b.MulMatrix(a);

  EXPECT_DOUBLE_EQ(b(0, 0), 74);
  EXPECT_DOUBLE_EQ(b(0, 1), 34);
  EXPECT_DOUBLE_EQ(b(0, 2), 20.000059999999998);
  EXPECT_DOUBLE_EQ(b(1, 0), 149.00036);
  EXPECT_DOUBLE_EQ(b(1, 1), 77.000149999999991);
  EXPECT_DOUBLE_EQ(b(1, 2), 74.000149999999991);
  EXPECT_DOUBLE_EQ(b(2, 0), 79);
  EXPECT_DOUBLE_EQ(b(2, 1), 49);
  EXPECT_DOUBLE_EQ(b(2, 2), 78.000149999999991);
}

TEST(MulMatrix, test_17) {
  S21Matrix a(1, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  S21Matrix b(3, 1);
  b(0, 0) = 2.0;
  b(1, 0) = 11.0;
  b(2, 0) = 12.0;

  a.MulMatrix(b);

  EXPECT_DOUBLE_EQ(a(0, 0), 74);
}

TEST(MulMatrix, test_18) {
  S21Matrix a(1, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  S21Matrix b(3, 1);
  b(0, 0) = 2.0;
  b(1, 0) = 11.0;
  b(2, 0) = 12.0;

  a.MulMatrix(b);

  EXPECT_DOUBLE_EQ(a(0, 0), 74);
}

TEST(MulMatrix, test_19) {
  S21Matrix a(4, 3);
  S21Matrix b(4, 3);
  S21Matrix result_full(4, 3);
  double res = 5.123f;

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 1.21030120f;
      b(i, j) = res * a(i, j);
    }
  }

  EXPECT_THROW(a.MulMatrix(b), std::length_error);
  b.SetRows(3);

  result_full = a * b;

  for (int i = 0; i < result_full.GetRows(); i++) {
    for (int j = 0; j < result_full.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(result_full(i, j), 22.512955999024761);
    }
  }
}

TEST(Transpose, test_20) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  S21Matrix result_full(3, 3);
  S21Matrix result1;
  S21Matrix result2;

  a(0, 0) = 0;
  a(0, 1) = 1;
  a(1, 0) = 2;
  a(1, 1) = 8;
  a(2, 0) = 7;
  a(2, 1) = 3;

  b(0, 0) = 5;
  b(0, 1) = 1;
  b(0, 2) = 2;
  b(1, 0) = 3;
  b(1, 1) = 7;
  b(1, 2) = 3;

  result1 = a * b;

  result_full(0, 0) = 3;
  result_full(0, 1) = 34;
  result_full(0, 2) = 44;
  result_full(1, 0) = 7;
  result_full(1, 1) = 58;
  result_full(1, 2) = 28;
  result_full(2, 0) = 3;
  result_full(2, 1) = 28;
  result_full(2, 2) = 23;

  result2 = result1.Transpose();
  EXPECT_EQ(result_full.EqMatrix(result2), true);
}

TEST(Transpose, test_21) {
  S21Matrix a(3, 5);
  S21Matrix result;

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(0, 3) = 4;
  a(0, 4) = 5;
  a(1, 0) = 6;
  a(1, 1) = 7;
  a(1, 2) = 8;
  a(1, 3) = 9;
  a(1, 4) = 10;
  a(2, 0) = 11;
  a(2, 1) = 12;
  a(2, 2) = 13;
  a(2, 3) = 14;
  a(2, 4) = 15;

  result = a.Transpose();

  EXPECT_EQ(result.GetRows(), 5);
  EXPECT_EQ(result.GetCols(), 3);

  EXPECT_DOUBLE_EQ(a(0, 0), result(0, 0));
  EXPECT_DOUBLE_EQ(a(0, 1), result(1, 0));
  EXPECT_DOUBLE_EQ(a(0, 2), result(2, 0));
  EXPECT_DOUBLE_EQ(a(0, 3), result(3, 0));
  EXPECT_DOUBLE_EQ(a(0, 4), result(4, 0));

  EXPECT_DOUBLE_EQ(a(1, 0), result(0, 1));
  EXPECT_DOUBLE_EQ(a(1, 1), result(1, 1));
  EXPECT_DOUBLE_EQ(a(1, 2), result(2, 1));
  EXPECT_DOUBLE_EQ(a(1, 3), result(3, 1));
  EXPECT_DOUBLE_EQ(a(1, 4), result(4, 1));

  EXPECT_DOUBLE_EQ(a(2, 0), result(0, 2));
  EXPECT_DOUBLE_EQ(a(2, 1), result(1, 2));
  EXPECT_DOUBLE_EQ(a(2, 2), result(2, 2));
  EXPECT_DOUBLE_EQ(a(2, 3), result(3, 2));
  EXPECT_DOUBLE_EQ(a(2, 4), result(4, 2));
}

TEST(Transpose, test_22) {
  S21Matrix a(0, 5);
  EXPECT_THROW(a.Transpose(), std::length_error);
}

TEST(Transpose, test_23) {
  S21Matrix a(2, 2);
  S21Matrix b(0, 5);
  S21Matrix result(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  result(0, 0) = 4.0;
  result(0, 1) = -3.0;
  result(1, 0) = -2.0;
  result(1, 1) = 1.0;

  b = a.CalcComplements();

  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(b(i, j), result(i, j));
    }
  }
}

TEST(Transpose, test_24) {
  S21Matrix a(2, 1);
  S21Matrix b(0, 5);
  S21Matrix result(2, 2);

  a(0, 0) = 1;
  a(1, 0) = 3;

  EXPECT_THROW(a.CalcComplements(), std::length_error);

  a.SetRows(1);
  a.SetCols(1);

  EXPECT_DOUBLE_EQ(a.CalcComplements()(0, 0), 1);
}

TEST(Transpose, test_25) {
  S21Matrix a(5, 5);
  S21Matrix b(0, 5);
  S21Matrix result(5, 5);

  double res1 = 0.0;
  double res2 = 0.0;

  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;
  a(0, 3) = 5.0001;
  a(0, 4) = 10.0123;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;
  a(1, 3) = 8.0;
  a(1, 4) = 9.003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;
  a(2, 3) = 3.0;
  a(2, 4) = 2.003;

  a(3, 0) = 3.0;
  a(3, 1) = 5.0;
  a(3, 2) = 9.00003;
  a(3, 3) = 3.0;
  a(3, 4) = 10.003;

  a(4, 0) = 7.0;
  a(4, 1) = 8.0;
  a(4, 2) = 3.00003;
  a(4, 3) = 4.0;
  a(4, 4) = 8.003;

  b = a.CalcComplements();

  result(0, 0) = 539.5924786;
  result(0, 1) = -1350.4021189;
  result(0, 2) = -1140.4050000;
  result(0, 3) = -1169.5906778;
  result(0, 4) = 1890.0014400;

  result(1, 0) = -568.1006721;
  result(1, 1) = 502.4746836;
  result(1, 2) = 791.9354081;
  result(1, 3) = 2456.5039660;
  result(1, 4) = -1530.0435600;

  result(2, 0) = 1464.1752928;
  result(2, 1) = -1249.2578551;
  result(2, 2) = -488.3028072;
  result(2, 3) = -2368.6530088;
  result(2, 4) = 1335.0457200;

  result(3, 0) = 468.0843532;
  result(3, 1) = -366.4284224;
  result(3, 2) = 900.4813991;
  result(3, 3) = -1512.0276994;
  result(3, 4) = 375.0439201;

  result(4, 0) = -987.4974783;
  result(4, 1) = 1894.8517495;
  result(4, 2) = -467.4700000;
  result(4, 3) = 1182.5081333;
  result(4, 4) = -585.0291601;

  res1 = (a(0, 0) * b(0, 0)) + (a(0, 1) * b(0, 1)) + (a(0, 2) * b(0, 2)) +
         (a(0, 3) * b(0, 3)) + (a(0, 4) * b(0, 4));
  res2 = a.Determinant();

  EXPECT_EQ(b.EqMatrix(result), true);
  EXPECT_EQ(res1, res2);
}

TEST(Determinant, test_26) {
  S21Matrix a(1, 2);
  EXPECT_THROW(a.Determinant(), std::length_error);
  a.SetCols(1);
  a(0, 0) = 1.0;
  EXPECT_DOUBLE_EQ(a.Determinant(), 1.0);
}

TEST(operator, test_26) {
  S21Matrix a(1, 2);
  EXPECT_THROW(a.Determinant(), std::length_error);
  a.SetCols(1);
  a(0, 0) = 1.0;
  EXPECT_DOUBLE_EQ(a.Determinant(), 1.0);
}

TEST(InverseMatrix, test_27) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix result(3, 3);

  a(0, 0) = 2.0;
  a(0, 1) = 5.0;
  a(0, 2) = 7.0;
  a(1, 0) = 6.0;
  a(1, 1) = 3.0;
  a(1, 2) = 4.0;
  a(2, 0) = 5.0;
  a(2, 1) = -2.0;
  a(2, 2) = -3.0;

  b(0, 0) = 1.0;
  b(0, 1) = -1.0;
  b(0, 2) = 1.0;
  b(1, 0) = -38.0;
  b(1, 1) = 41.0;
  b(1, 2) = -34.0;
  b(2, 0) = 27.0;
  b(2, 1) = -29.0;
  b(2, 2) = 24.0;

  result = a.InverseMatrix();

  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++)
      EXPECT_DOUBLE_EQ(b(i, j), result(i, j));
  }
}

TEST(InverseMatrix, test_28) {
  S21Matrix a(1, 1);
  S21Matrix b(1, 1);
  S21Matrix result(1, 1);

  a(0, 0) = 2.0;
  b(0, 0) = 0.5;

  result = a.InverseMatrix();

  EXPECT_DOUBLE_EQ(b(0, 0), result(0, 0));
}

TEST(InverseMatrix, test_29) {
  S21Matrix a(3, 3);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 3.0;
  a(1, 0) = 4.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.0;
  a(2, 0) = 7.0;
  a(2, 1) = 8.0;
  a(2, 2) = 9.0;
  EXPECT_THROW(a.InverseMatrix(), std::length_error);
  S21Matrix b(0, 0);
  EXPECT_THROW(b.InverseMatrix(), std::length_error);
}

TEST(SumOperator, test_30) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b = b + a;

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) - a(i, j));
    }
  }

  b = b - a;
  b += a;

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) - a(i, j));
    }
  }
}

TEST(SubOperator, test_31) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b = b - a;

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) + a(i, j));
    }
  }

  b = b + a;
  b -= a;

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) + a(i, j));
    }
  }
}

TEST(MulNumOperator, test_32) {
  S21Matrix a(3, 4);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  S21Matrix tmp = b;
  b = b * 3;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }

  b = tmp;
  b = 3 * b;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }

  b = tmp;
  b *= 3;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }
}

TEST(EqOperator, test_33) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  EXPECT_EQ(a.GetCols(), b.GetCols());
  EXPECT_EQ(b == a, true);
}

TEST(EqOperator, test_34) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b(0, 0) = a(0, 0) - 1.00001;
  b(1, 2) = a(1, 2) - 0.00001;
  b(2, 2) = a(2, 2) + 0.00001;

  EXPECT_EQ(b == a, false);
}

TEST(BrktOperator, test_35) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  const S21Matrix b(a);

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j));
    }
  }

  EXPECT_THROW(b(-1, 0), std::length_error);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
