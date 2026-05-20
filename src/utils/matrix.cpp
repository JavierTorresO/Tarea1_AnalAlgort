#include "utils/matrix.h"

#include <cmath>

// Crear matriz n x n llena de ceros
Matrix createMatrix(int n) {
    return Matrix(n, vector<double>(n, 0));
}

// Suma de matrices
Matrix addMatrix(const Matrix& A, const Matrix& B) {

    int n = A.size();
    Matrix C = createMatrix(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

// Resta de matrices
Matrix subtractMatrix(const Matrix& A, const Matrix& B) {

    int n = A.size();
    Matrix C = createMatrix(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;
}

// Imprimir matriz
void printMatrix(const Matrix& A) {

    int n = A.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << "\t";
        }

        cout << endl;
    }
}

// Comparar matrices con tolerancia
bool areEqual(
    const Matrix& A,
    const Matrix& B,
    double epsilon
) {

    int n = A.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (abs(A[i][j] - B[i][j]) > epsilon) {
                return false;
            }

        }
    }

    return true;
}

// Dividir matriz en 4 bloques
void splitMatrix(
    const Matrix& A,
    Matrix& A11,
    Matrix& A12,
    Matrix& A21,
    Matrix& A22
) {

    int n = A.size();
    int half = n / 2;

    A11 = createMatrix(half);
    A12 = createMatrix(half);
    A21 = createMatrix(half);
    A22 = createMatrix(half);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            // Superior izquierda
            A11[i][j] = A[i][j];
            // Superior derecha
            A12[i][j] = A[i][j + half];
            // Inferior izquierda
            A21[i][j] = A[i + half][j];
            // Inferior derecha
            A22[i][j] = A[i + half][j + half];
        }
    }
}

// Unir 4 bloques en una matriz grande
Matrix joinMatrices(
    const Matrix& C11,
    const Matrix& C12,
    const Matrix& C21,
    const Matrix& C22
) {

    int half = C11.size();
    int n = half * 2;
    Matrix C = createMatrix(n);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            // Superior izquierda
            C[i][j] = C11[i][j];
            // Superior derecha
            C[i][j + half] = C12[i][j];
            // Inferior izquierda
            C[i + half][j] = C21[i][j];
            // Inferior derecha
            C[i + half][j + half] = C22[i][j];
        }
    }

    return C;
}

void addSubMatrix(
    const Matrix& A, int rA, int cA,
    const Matrix& B, int rB, int cB,
    Matrix& Result, int rR, int cR, 
    int size
) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Result[rR + i][cR + j] = A[rA + i][cA + j] + B[rB + i][cB + j];
        }
    }
}

void subSubMatrix(
    const Matrix& A, int rA, int cA,
    const Matrix& B, int rB, int cB,
    Matrix& Result, int rR, int cR, 
    int size
) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Result[rR + i][cR + j] = A[rA + i][cA + j] - B[rB + i][cB + j];
        }
    }
}