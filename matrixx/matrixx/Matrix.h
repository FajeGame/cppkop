#ifndef MATRIXX_MATRIX_H
#define MATRIXX_MATRIX_H

#include <iostream>
#include <stdexcept>

namespace Matrixx {
    class Matrix {
    private:
        int rows_, cols_;
        double** matrix_;

        void AllocateMemory();
        void CopyMatrix(const Matrix& other);
        void FreeMemory();

    public:
        Matrix();
        Matrix(int rows, int cols);
        Matrix(const Matrix& other);
        Matrix(Matrix&& other) noexcept;
        ~Matrix();

        Matrix& operator=(const Matrix& other);
        Matrix& operator=(Matrix&& other) noexcept;

        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const;
        Matrix operator*(const double num) const;

        bool operator==(const Matrix& other) const;

        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(const Matrix& other);
        Matrix& operator*=(const double num);

        double& operator()(int i, int j);

        double Determinant() const;
        Matrix CalcComplements() const;
        Matrix InverseMatrix() const;
        Matrix Transpose() const;

        bool EqMatrix(const Matrix& other) const;

        void SumMatrix(const Matrix& other);
        void SubMatrix(const Matrix& other);
        void MulNumber(double num);
        void MulMatrix(const Matrix& other);
        Matrix GetMinor(int row, int col) const;

        void print() const;
        void fill();
    };
}

#endif
