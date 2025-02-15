#include <iostream>
#include "Matrix.h"

using namespace std;
using namespace Matrixx;

int main() {
    try {
        setlocale(LC_ALL, "rus");
        // Создание матриц
        Matrix A(2, 2);
        Matrix B(2, 2);

        // Заполняем матрицы вручную для наглядности
        A(0, 0) = 1; A(0, 1) = 2;
        A(1, 0) = 3; A(1, 1) = 4;

        B(0, 0) = 5; B(0, 1) = 6;
        B(1, 0) = 7; B(1, 1) = 8;

        cout << "Матрица A:" << endl;
        A.print();
        cout << "Матрица B:" << endl;
        B.print();

        // Тест сложения
        cout << "A + B:" << endl;
        Matrix C = A + B;
        C.print();

        // Тест вычитания
        cout << "A - B:" << endl;
        Matrix D = A - B;
        D.print();

        // Тест умножения матриц
        cout << "A * B:" << endl;
        Matrix E = A * B;
        E.print();

        // Тест умножения на число
        cout << "A * 2:" << endl;
        Matrix F = A * 2;
        F.print();

        // Тест оператора ==
        cout << "A == B: " << (A == B ? "True" : "False") << endl;

        // Тест операторов += и -=
        cout << "A += B:" << endl;
        A += B;
        A.print();

        cout << "A -= B:" << endl;
        A -= B;
        A.print();

        // Тест оператора *= (умножение на число)
        cout << "A *= 3:" << endl;
        A *= 3;
        A.print();

        // Тест оператора *= (умножение матриц)
        cout << "B *= B:" << endl;
        B *= B;
        B.print();

        // Транспонирование
        cout << "Транспонированная матрица A:" << endl;
        Matrix G = A.Transpose();
        G.print();

        // Определитель
        cout << "Определитель A: " << A.Determinant() << endl;

        // Матрица алгебраических дополнений
        cout << "Матрица алгебраических дополнений A:" << endl;
        Matrix H = A.CalcComplements();
        H.print();

        // Обратная матрица
        cout << "Обратная матрица A:" << endl;
        Matrix I = A.InverseMatrix();
        I.print();
    }
    catch (const std::exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
