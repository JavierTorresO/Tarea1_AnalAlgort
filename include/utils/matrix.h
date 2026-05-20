#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

using namespace std;

// Definición de tipo para matrices
using Matrix = vector<vector<double>>;

//crear matriz n x n (inicializada en 0)
Matrix createMatrix(int n);

//suma de matrices
Matrix addMatrix(const Matrix& A, const Matrix& B);

//resta de matrices
Matrix subtractMatrix(const Matrix& A, const Matrix& B);

//imprimir matriz
void printMatrix(const Matrix& A);

//comparar matrices
bool areEqual(
    const Matrix& A,
    const Matrix& B,
    double epsilon = 1e-9
);

//dividir matriz en 4 bloques
void splitMatrix(
    const Matrix& A,
    Matrix& A11,
    Matrix& A12,
    Matrix& A21,
    Matrix& A22
);

//unir 4 bloques en una sola matriz
Matrix joinMatrices(
    const Matrix& C11,
    const Matrix& C12,
    const Matrix& C21,
    const Matrix& C22
);

void addSubMatrix(
    const Matrix& A, int rA, int cA,
    const Matrix& B, int rB, int cB,
    Matrix& Result, int rR, int cR, 
    int size
);

void subSubMatrix(
    const Matrix& A, int rA, int cA,
    const Matrix& B, int rB, int cB,
    Matrix& Result, int rR, int cR, 
    int size
);

#endif