#include "Matrix.h"
#include <iostream>
#include <cmath>

namespace Matrixx {

    // ��������������� �������
    void Matrix::AllocateMemory() {
        matrix_ = new double* [rows_];
        for (int i = 0; i < rows_; i++) {
            matrix_[i] = new double[cols_]();
        }
    }

    void Matrix::CopyMatrix(const Matrix& other) {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] = other.matrix_[i][j];
            }
        }
    }

    void Matrix::FreeMemory() {
        if (matrix_) {
            for (int i = 0; i < rows_; i++)
                delete[] matrix_[i];
            delete[] matrix_;
        }
    }

    // ������������ � ����������
    Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

    Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
        if (rows <= 0 || cols <= 0) throw std::invalid_argument("������� ������� ������ ���� ��������������.");
        AllocateMemory();
    }

    Matrix::Matrix(const Matrix& other) : Matrix(other.rows_, other.cols_) {
        CopyMatrix(other);
    }

    Matrix::Matrix(Matrix&& other) noexcept : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
        other.rows_ = 0;
        other.cols_ = 0;
        other.matrix_ = nullptr;
    }

    Matrix::~Matrix() {
        FreeMemory();
    }

    // �������� �� ���������
    bool Matrix::EqMatrix(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) return false;
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                if (matrix_[i][j] != other.matrix_[i][j]) return false;
            }
        }
        return true;
    }

    // ��������� ������������
    Matrix& Matrix::operator=(const Matrix& other) {
        if (this != &other) {
            FreeMemory();
            rows_ = other.rows_;
            cols_ = other.cols_;
            AllocateMemory();
            CopyMatrix(other);
        }
        return *this;
    }

    Matrix& Matrix::operator=(Matrix&& other) noexcept {
        if (this != &other) {
            FreeMemory();
            rows_ = other.rows_;
            cols_ = other.cols_;
            matrix_ = other.matrix_;

            other.rows_ = 0;
            other.cols_ = 0;
            other.matrix_ = nullptr;
        }
        return *this;
    }

    // ����� �������
    void Matrix::print() const {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                std::cout << matrix_[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // ���������� ������� � ����������
    void Matrix::fill() {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                std::cout << "������� �������� ��� [" << i << "][" << j << "]: ";
                std::cin >> matrix_[i][j];
            }
        }
    }
    // �������� ������
    void Matrix::SumMatrix(const Matrix& other) {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            throw std::invalid_argument("������� ������ ���� ������ �������.");
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++)
                matrix_[i][j] += other.matrix_[i][j];
    }

    // ��������� ������
    void Matrix::SubMatrix(const Matrix& other) {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            throw std::invalid_argument("������� ������ ���� ������ �������.");
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++)
                matrix_[i][j] -= other.matrix_[i][j];
    }

    // ��������� ������
    void Matrix::MulMatrix(const Matrix& other) {
        try {
            if (cols_ != other.rows_)
                throw std::invalid_argument("�������� ������� ������ ��� ���������.");

            Matrix result(rows_, other.cols_);

            for (int i = 0; i < rows_; i++)
                for (int j = 0; j < other.cols_; j++)
                    for (int k = 0; k < cols_; k++)
                        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];

            *this = std::move(result);
        }
        catch (const std::exception& e) {
            std::cerr << "������ ��� ��������� ������: " << e.what() << std::endl;
        }
    }


    // ���������������� �������
    Matrix Matrix::Transpose() const {
        Matrix result(cols_, rows_);
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++)
                result.matrix_[j][i] = matrix_[i][j];
        return result;
    }

    void Matrix::MulNumber(double num) {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] *= num;
            }
        }
    }

    double Matrix::Determinant() const {
        if (rows_ != cols_) {
            throw std::invalid_argument("������������ ����� ��������� ������ ��� ���������� ������.");
        }

        if (rows_ == 1) {
            return matrix_[0][0];  // ������������ 1x1 ������� � ��� ��� �������
        }

        if (rows_ == 2) {
            return (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]); // ������� 2x2
        }

        double det = 0.0;
        for (int j = 0; j < cols_; j++) {
            Matrix minor = GetMinor(0, j);
            double cofactor = ((j % 2 == 0) ? 1 : -1) * matrix_[0][j] * minor.Determinant();
            det += cofactor;
        }
        return det;
    }

    // ������� ��� ���������� �������������� ����������
    Matrix Matrix::CalcComplements() const {
        if (rows_ != cols_) {
            throw std::invalid_argument("�������������� ���������� ����� ��������� ������ ��� ���������� ������.");
        }

        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                Matrix minor = GetMinor(i, j);
                result.matrix_[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minor.Determinant();
            }
        }
        return result;
    }

    // ������� ��� ���������� �������� �������
    Matrix Matrix::InverseMatrix() const {
        double det = Determinant();
        if (det == 0) {
            throw std::runtime_error("�������� ������� �� ���������� (������������ ����� 0).");
        }

        Matrix complements = CalcComplements();
        Matrix transposed = complements.Transpose();
        transposed.MulNumber(1.0 / det);
        return transposed;
    }

    // ��������������� ������� ��� ��������� ������ (�������� ������ � �������)
    Matrix Matrix::GetMinor(int row, int col) const {
        Matrix minor(rows_ - 1, cols_ - 1);
        for (int i = 0, mi = 0; i < rows_; i++) {
            if (i == row) continue;
            for (int j = 0, mj = 0; j < cols_; j++) {
                if (j == col) continue;
                minor.matrix_[mi][mj] = matrix_[i][j];
                mj++;
            }
            mi++;
        }
        return minor;
    }

    // �������� ���� ������
    Matrix Matrix::operator+(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            throw std::invalid_argument("������� ������ �� ��������� ��� ��������.");
        Matrix result(*this);
        result += other;
        return result;
    }

    // ��������� ���� ������
    Matrix Matrix::operator-(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            throw std::invalid_argument("������� ������ �� ��������� ��� ���������.");
        Matrix result(*this);
        result -= other;
        return result;
    }

    // ��������� ���� ������
    Matrix Matrix::operator*(const Matrix& other) const {
        if (cols_ != other.rows_)
            throw std::invalid_argument("������� ������ �� ��������� ��� ���������.");
        Matrix result(rows_, other.cols_);
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < other.cols_; j++)
                for (int k = 0; k < cols_; k++)
                    result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        return result;
    }

    // ��������� ������� �� �����
    Matrix Matrix::operator*(const double num) const {
        Matrix result(*this);
        result *= num;
        return result;
    }

    // �������� �� ��������� ���� ������
    bool Matrix::operator==(const Matrix& other) const {
        return EqMatrix(other);
    }

    // �������� += (���������� � ������� ������� ������)
    Matrix& Matrix::operator+=(const Matrix& other) {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            throw std::invalid_argument("������� ������ �� ��������� ��� ��������.");
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++)
                matrix_[i][j] += other.matrix_[i][j];
        return *this;
    }

    // �������� -= (�������� ������ �������)
    Matrix& Matrix::operator-=(const Matrix& other) {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            throw std::invalid_argument("������� ������ �� ��������� ��� ���������.");
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++)
                matrix_[i][j] -= other.matrix_[i][j];
        return *this;
    }

    // �������� *= (�������� ������� ������� �� ������)
    Matrix& Matrix::operator*=(const Matrix& other) {
        *this = *this * other;
        return *this;
    }

    // �������� *= (�������� ������� ������� �� �����)
    Matrix& Matrix::operator*=(const double num) {
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++)
                matrix_[i][j] *= num;
        return *this;
    }

    // ������ � �������� ������� �� ������� (�������� ())
    double& Matrix::operator()(int i, int j) {
        if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
            throw std::out_of_range("������� ������� �� ������� �������.");
        return matrix_[i][j];
    }

}
