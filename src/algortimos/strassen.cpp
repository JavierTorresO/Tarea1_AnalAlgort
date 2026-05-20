#include "strassen.h"

#include "../../utils/matrix.h"

// Multiplicación usando Strassen
Matrix strassenMultiply(
    const Matrix& A,
    const Matrix& B
) {

    int n = A.size();

    // Caso base
    if (n == 1) {
        Matrix C = createMatrix(1);
        C[0][0] = A[0][0] * B[0][0]; //multiplica directamente
        return C;
    }

    // Dividir matrices -> parte DIVIDE
    Matrix A11, A12, A21, A22;
    Matrix B11, B12, B21, B22;

    splitMatrix(A, A11, A12, A21, A22); //dividir A
    splitMatrix(B, B11, B12, B21, B22); //dividir B


    // Calcular M1 ... M7 -> parte CONQUER
    Matrix M1 = strassenMultiply(
        addMatrix(A11, A22),
        addMatrix(B11, B22)
    );

    Matrix M2 = strassenMultiply(
        addMatrix(A21, A22),
        B11
    );

    Matrix M3 = strassenMultiply(
        A11,
        subtractMatrix(B12, B22)
    );

    Matrix M4 = strassenMultiply(
        A22,
        subtractMatrix(B21, B11)
    );

    Matrix M5 = strassenMultiply(
        addMatrix(A11, A12),
        B22
    );

    Matrix M6 = strassenMultiply(
        subtractMatrix(A21, A11),
        addMatrix(B11, B12)
    );

    Matrix M7 = strassenMultiply(
        subtractMatrix(A12, A22),
        addMatrix(B21, B22)
    );

    // ==========================================

    // Construir C11, C12, C21, C22 -> parte COMBINE
    Matrix C11 = addMatrix(
        subtractMatrix(
            addMatrix(M1, M4),
            M5
        ),
        M7
    );

    Matrix C12 = addMatrix(
        M3,
        M5
    );

    Matrix C21 = addMatrix(
        M2,
        M4
    );

    Matrix C22 = addMatrix(
        subtractMatrix(
            addMatrix(M1, M3),
            M2
        ),
        M6
    );

    // ==========================================

    // Unir bloques, reconstruir la matriz final C
    Matrix C = joinMatrices(
        C11,
        C12,
        C21,
        C22
    );
    return C;
}