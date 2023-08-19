#ifndef CPP_MATRIXPLUS_SRC_MATRIX_OOP_H_
#define CPP_MATRIXPLUS_SRC_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

constexpr double EPS = 1e-7;

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(const int rows, const int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);

  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double other);
  friend S21Matrix operator*(const double other, S21Matrix& tmp);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double other);
  double& operator()(int i, int j);
  double operator()(int i, int j) const;

  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

 private:
  int rows_, cols_;
  double** matrix_;

  void CreateMatrix();
  void ClearMatrix();
  void CopyMatrix(const S21Matrix& tmp, const int rows, const int cols);
  double MinorSearch(const int& i, const int& j) const;
  S21Matrix MatrixDecr(const int& i, const int& j) const;
  void SumSubFunc(const S21Matrix& other, const int code);
  void MatrixСhange(const S21Matrix& tmp, const int rows, const int cols);
};

#endif  // CPP_MATRIXPLUS_SRC_MATRIX_OOP_H_