#include "algoritmos/strassen.h"
#include "utils/matrix.h"

// Función auxiliar (Core recursivo por índices)
void strassen_core(
    const Matrix& A, int rA, int cA,
    const Matrix& B, int rB, int cB,
    Matrix& C, int rC, int cC,
    int n
) {
    // Caso base
    if (n == 1) {
        C[rC][cC] = A[rA][cA] * B[rB][cB];
        return;
    }

    int half = n / 2;

    // Buffers temporales estrictamente necesarios (tamaño half x half)
    Matrix T1 = createMatrix(half);
    Matrix T2 = createMatrix(half);
    
    // Matrices para almacenar los 7 productos de Strassen
    Matrix M1 = createMatrix(half);
    Matrix M2 = createMatrix(half);
    Matrix M3 = createMatrix(half);
    Matrix M4 = createMatrix(half);
    Matrix M5 = createMatrix(half);
    Matrix M6 = createMatrix(half);
    Matrix M7 = createMatrix(half);

    // parte 1, calcular M1 a M7 usando buffers T1 y T2 para sumas/restas intermedias

    // M1 = (A11 + A22) * (B11 + B22)
    addSubMatrix(A, rA, cA,          A, rA + half, cA + half,  T1, 0, 0, half); // T1 = A11 + A22
    addSubMatrix(B, rB, cB,          B, rB + half, cB + half,  T2, 0, 0, half); // T2 = B11 + B22
    strassen_core(T1, 0, 0, T2, 0, 0, M1, 0, 0, half);                          // M1 = T1 * T2

    // M2 = (A21 + A22) * B11
    addSubMatrix(A, rA + half, cA,   A, rA + half, cA + half,  T1, 0, 0, half); // T1 = A21 + A22
    strassen_core(T1, 0, 0, B, rB, cB, M2, 0, 0, half);                         // M2 = T1 * B11

    // M3 = A11 * (B12 - B22)
    subSubMatrix(B, rB, cB + half,   B, rB + half, cB + half,  T2, 0, 0, half); // T2 = B12 - B22
    strassen_core(A, rA, cA, T2, 0, 0, M3, 0, 0, half);                         // M3 = A11 * T2

    // M4 = A22 * (B21 - B11)
    subSubMatrix(B, rB + half, cB,   B, rB, cB,                T2, 0, 0, half); // T2 = B21 - B11
    strassen_core(A, rA + half, cA + half, T2, 0, 0, M4, 0, 0, half);           // M4 = A22 * T2

    // M5 = (A11 + A12) * B22
    addSubMatrix(A, rA, cA,          A, rA, cA + half,         T1, 0, 0, half); // T1 = A11 + A12
    strassen_core(T1, 0, 0, B, rB + half, cB + half, M5, 0, 0, half);           // M5 = T1 * B22

    // M6 = (A21 - A11) * (B11 + B12)
    subSubMatrix(A, rA + half, cA,   A, rA, cA,                T1, 0, 0, half); // T1 = A21 - A11
    addSubMatrix(B, rB, cB,          B, rB, cB + half,         T2, 0, 0, half); // T2 = B11 + B12
    strassen_core(T1, 0, 0, T2, 0, 0, M6, 0, 0, half);                          // M6 = T1 * T2

    // M7 = (A12 - A22) * (B21 + B22)
    subSubMatrix(A, rA, cA + half,   A, rA + half, cA + half,  T1, 0, 0, half); // T1 = A12 - A22
    addSubMatrix(B, rB + half, cB,   B, rB + half, cB + half,  T2, 0, 0, half); // T2 = B21 + B22
    strassen_core(T1, 0, 0, T2, 0, 0, M7, 0, 0, half);                          // M7 = T1 * T2

    // parte 2, construir directamente en C usando coordenadas y buffers

    // C11 = M1 + M4 - M5 + M7
    addSubMatrix(M1, 0, 0, M4, 0, 0, C, rC, cC, half);          // C11 = M1 + M4
    subSubMatrix(C, rC, cC, M5, 0, 0, C, rC, cC, half);         // C11 = C11 - M5
    addSubMatrix(C, rC, cC, M7, 0, 0, C, rC, cC, half);         // C11 = C11 + M7

    // C12 = M3 + M5
    addSubMatrix(M3, 0, 0, M5, 0, 0, C, rC, cC + half, half);

    // C21 = M2 + M4
    addSubMatrix(M2, 0, 0, M4, 0, 0, C, rC + half, cC, half);

    // C22 = M1 - M2 + M3 + M6
    subSubMatrix(M1, 0, 0, M2, 0, 0, C, rC + half, cC + half, half); // C22 = M1 - M2
    addSubMatrix(C, rC + half, cC + half, M3, 0, 0, C, rC + half, cC + half, half); // C22 = C22 + M3
    addSubMatrix(C, rC + half, cC + half, M6, 0, 0, C, rC + half, cC + half, half); // C22 = C22 + M6
}

// Función principal (Wrapper expuesto en strassen.h)
Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C = createMatrix(n); // Se pide memoria una sola vez para la matriz resultante
    strassen_core(A, 0, 0, B, 0, 0, C, 0, 0, n);
    return C;
}