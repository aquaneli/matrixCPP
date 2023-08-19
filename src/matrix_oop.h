#ifndef CPP_MATRIXPLUS_SRC_MATRIX_OOP_H_
#define CPP_MATRIXPLUS_SRC_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

constexpr double EPS = 1e-7;

class Matrix {
 public:
  Matrix();
  Matrix(const int rows, const int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other) noexcept;
  ~Matrix();

  bool EqMatrix(const Matrix& other) const;
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix& other);

  Matrix Transpose() const;
  Matrix CalcComplements() const;
  double Determinant() const;
  Matrix InverseMatrix() const;

  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix operator*(const double other);
  friend Matrix operator*(const double other, Matrix& tmp);
  bool operator==(const Matrix& other);
  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other) noexcept;
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*=(const double other);
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
  void CopyMatrix(const Matrix& tmp, const int rows, const int cols);
  double MinorSearch(const int& i, const int& j) const;
  Matrix MatrixDecr(const int& i, const int& j) const;
  void SumSubFunc(const Matrix& other, const int code);
  void MatrixСhange(const Matrix& tmp, const int rows, const int cols);
};

#endif  // CPP_MATRIXPLUS_SRC_MATRIX_OOP_H_