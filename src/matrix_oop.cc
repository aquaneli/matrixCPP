#include "matrix_oop.h"

/* Базовый конструктор, инициализирующий матрицу некоторой заранее заданной
 * размерностью */
Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

/* Параметризированный конструктор с количеством строк и столбцов */
Matrix::Matrix(const int rows, const int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows > 0 && cols > 0) {
    CreateMatrix();
  }
}

/* Конструктор копирования */
Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(nullptr) {
  if (other.matrix_) {
    CreateMatrix();
    CopyMatrix(other, other.rows_, other.cols_);
  }
}

/* Конструктор переноса */
Matrix::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

/* Деструктор */
Matrix::~Matrix() { ClearMatrix(); }

/* Проверяет матрицы на равенство между собой */
bool Matrix::EqMatrix(const Matrix& other) const {
  bool res = true;
  if (rows_ == other.rows_ && cols_ == other.cols_ && matrix_ &&
      other.matrix_) {
    for (int i = 0; i < other.rows_ && res; i++) {
      for (int j = 0; j < other.cols_ && res; j++) {
        if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
          res = false;
        }
      }
    }
  } else {
    res = false;
  }

  return res;
}

/* Прибавляет вторую матрицы к текущей */
void Matrix::SumMatrix(const Matrix& other) {
  if ((rows_ != other.rows_ || cols_ != other.cols_) || !matrix_ ||
      !other.matrix_) {
    throw std::length_error("different matrix dimensions or no matrix exists");
  }
  SumSubFunc(other, 0);
}

/* Вычитает из текущей матрицы другую */
void Matrix::SubMatrix(const Matrix& other) {
  if ((rows_ != other.rows_ || cols_ != other.cols_) || !matrix_ ||
      !other.matrix_) {
    throw std::length_error("different matrix dimensions or no matrix exists");
  }
  SumSubFunc(other, 1);
}

/* Сложение или вычитание */
void Matrix::SumSubFunc(const Matrix& other, const int code) {
  if (code == 0) {
    for (int i = 0; i < other.rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  } else if (code == 1) {
    for (int i = 0; i < other.rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

/* Умножает текущую матрицу на число */
void Matrix::MulNumber(const double num) {
  if (!matrix_) {
    throw std::length_error("no matrix exists");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

/* Умножает текущую матрицу на вторую */
void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_ || !matrix_ || !other.matrix_) {
    throw std::length_error(
        "the number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix or no matrix exists");
  }
  double sum = 0.0;
  Matrix tmp(std::move(*this));
  rows_ = tmp.rows_;
  cols_ = other.cols_;

  CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++, sum = 0.0) {
      for (int k = 0; k < tmp.cols_; k++) {
        sum = tmp.matrix_[i][k] * other.matrix_[k][j] + sum;
      }
      matrix_[i][j] = sum;
    }
  }
}

/* Создает новую транспонированную матрицу из текущей и возвращает ее */
Matrix Matrix::Transpose() const {
  if (!matrix_) {
    throw std::length_error("no matrix exists");
  }
  Matrix tmp(cols_, rows_);
  for (int i = 0; i < tmp.rows_; i++) {
    for (int j = 0; j < tmp.cols_; j++) {
      tmp.matrix_[i][j] = matrix_[j][i];
    }
  }

  return tmp;
}

/* Вычисляет матрицу алгебраических дополнений текущей
матрицы и возвращает ее */
Matrix Matrix::CalcComplements() const {
  if (rows_ != cols_ || !matrix_) {
    throw std::length_error("the matrix is not square or no matrix exists");
  }
  Matrix res(rows_, cols_);
  if (res.rows_ > 1 && res.cols_ > 1) {
    for (int i = 0; i < res.rows_; i++)
      for (int j = 0; j < res.cols_; j++)
        res.matrix_[i][j] = MinorSearch(i, j) * pow(-1, i + j);
  } else {
    res.matrix_[0][0] = matrix_[0][0];
  }

  return res;
}

/* Поиск минора*/
double Matrix::MinorSearch(const int& i, const int& j) const {
  double res = 0.0;
  Matrix minor(MatrixDecr(i, j));
  if (minor.rows_ > 2) {
    for (int m = 0, k = 0; m < minor.cols_; m++) {
      res += minor.MinorSearch(k, m) * pow(-1, m) * minor.matrix_[0][m];
    }
  } else if (minor.rows_ == 2) {
    res = (minor.matrix_[0][0] * minor.matrix_[1][1]) -
          (minor.matrix_[0][1] * minor.matrix_[1][0]);
  } else {
    res = minor.matrix_[0][0];
  }
  return res;
}

/* Создание матрицы меньшего размера */
Matrix Matrix::MatrixDecr(const int& i, const int& j) const {
  Matrix minor(rows_ - 1, cols_ - 1);
  for (int rows = 0, rows_minor = 0, cols_minor = 0; rows < rows_; rows++) {
    for (int cols = 0; cols < cols_; cols++) {
      if (i != rows && j != cols) {
        minor.matrix_[rows_minor][cols_minor] = matrix_[rows][cols];
        cols_minor++;
        if (cols_minor == minor.cols_) {
          cols_minor = 0;
          rows_minor++;
        }
      }
    }
  }

  return minor;
}

/* Вычисляет и возвращает определитель текущей матрицы */
double Matrix::Determinant() const {
  if (rows_ != cols_ || !matrix_) {
    throw std::length_error("the matrix is not square or no matrix exists");
  }
  double res = 0.0f;
  Matrix det(CalcComplements());
  if (rows_ > 1 && cols_ > 1) {
    for (int j = 0; j < det.cols_; j++)
      res += det.matrix_[0][j] * matrix_[0][j];
  } else if (rows_ == 1 && cols_ == 1) {
    res = matrix_[0][0];
  }

  return res;
}

/* Вычисляет и возвращает обратную матрицу */
Matrix Matrix::InverseMatrix() const {
  if (!matrix_) {
    throw std::length_error("no matrix exists");
  }
  double det_res = 0.0f;
  Matrix inverse(*this);
  det_res = inverse.Determinant();
  if (det_res == 0.0) {
    throw std::length_error("matrix determinant is 0");
  }
  if (rows_ > 1 && cols_ > 1) {
    inverse = inverse.CalcComplements();
    inverse = inverse.Transpose();
    inverse.MulNumber(1 / det_res);
  } else {
    inverse.matrix_[0][0] = 1 / det_res;
  }

  return inverse;
}

/* Сложение двух матриц */
Matrix Matrix::operator+(const Matrix& other) {
  Matrix tmp(*this);
  tmp += other;
  return tmp;
}

/* Присвоение сложения */
Matrix& Matrix::operator+=(const Matrix& other) {
  SumMatrix(other);
  return *this;
}

/* Вычитание одной матрицы из другой */
Matrix Matrix::operator-(const Matrix& other) {
  Matrix tmp(*this);
  tmp -= other;
  return tmp;
}

/* Присвоение разности */
Matrix& Matrix::operator-=(const Matrix& other) {
  SubMatrix(other);
  return *this;
}

/* Умножение матриц */
Matrix Matrix::operator*(const Matrix& other) {
  Matrix tmp(*this);
  tmp *= other;
  return tmp;
}

/* Умножение матрицы на число */
Matrix Matrix::operator*(const double other) {
  Matrix tmp(*this);
  tmp *= other;
  return tmp;
}

/* Умножение числа на матрицу */
Matrix operator*(const double other, Matrix& tmp) {
  tmp *= other;
  return tmp;
}

/* Присвоение умножения матриц*/
Matrix& Matrix::operator*=(const Matrix& other) {
  MulMatrix(other);
  return *this;
}

/* Присвоение умножения матрицы на число*/
Matrix& Matrix::operator*=(const double other) {
  MulNumber(other);
  return *this;
}

/* Проверка на равенство матриц */
bool Matrix::operator==(const Matrix& other) { return EqMatrix(other); }

/* Оператор присваивания копированием */
Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    this->~Matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    CreateMatrix();
    CopyMatrix(other, other.rows_, other.cols_);
  }
  return *this;
}

/* Оператор присваивания перемещением */
Matrix& Matrix::operator=(Matrix&& other) noexcept {
  if (this != &other) {
    this->~Matrix();
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

/* Индексация по элементам матрицы */
double& Matrix::operator()(int i, int j) {
  if (rows_ <= i || cols_ <= j || i < 0 || j < 0 || !matrix_) {
    throw std::length_error("index is outside the matrix or no matrix exists");
  }
  return matrix_[i][j];
}

/* Индексация по элементам матрицы с константными значением */
double Matrix::operator()(int i, int j) const {
  if (rows_ <= i || cols_ <= j || i < 0 || j < 0 || !matrix_) {
    throw std::length_error("index is outside the matrix or no matrix exists");
  }

  return matrix_[i][j];
}

/* Создание новой матрицы */
void Matrix::CreateMatrix() {
  if (rows_ > 0 && cols_ > 0) {
    matrix_ = new double* [rows_] {};
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]{};
    }
  }
}

/* Очистка матрицы */
void Matrix::ClearMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i]) {
        delete[] matrix_[i];
      }
    }
    delete[] matrix_;
  }
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

/* Вернуть количество строк */
int Matrix::GetRows() const { return rows_; }

/* Вернуть количество столбцов */
int Matrix::GetCols() const { return cols_; }

/* Добавить новые строки */
void Matrix::SetRows(int rows) {
  if (rows != rows_ && rows >= 0) {
    Matrix tmp(std::move(*this));
    MatrixСhange(tmp, rows, tmp.cols_);
  }
}

/* Добавить новые столбцы */
void Matrix::SetCols(int cols) {
  if (cols != cols_ && cols >= 0) {
    Matrix tmp(std::move(*this));
    MatrixСhange(tmp, tmp.rows_, cols);
  }
}

void Matrix::MatrixСhange(const Matrix& tmp, const int rows, const int cols) {
  rows_ = rows;
  cols_ = cols;
  CreateMatrix();
  if (rows > tmp.rows_ || cols > tmp.cols_) {
    CopyMatrix(tmp, tmp.rows_, tmp.cols_);
  } else if (rows < tmp.rows_ || cols < tmp.cols_) {
    CopyMatrix(tmp, rows_, cols_);
  }
}

/* скопировать данные из матрицы в текущую матрицу*/
void Matrix::CopyMatrix(const Matrix& tmp, const int rows, const int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix_[i][j] = tmp.matrix_[i][j];
    }
  }
}
