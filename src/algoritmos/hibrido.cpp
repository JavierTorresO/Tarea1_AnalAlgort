#include "algoritmos/hibrido.h"
#include "algoritmos/clasico.h"


// Multiplicación híbrida

Matrix hybridMultiply(
    const Matrix& A,
    const Matrix& B,
    int n0
) {

    int n = A.size();

//===============================================    
    // Caso híbrido:
    // usar clásico bajo cierto umbral
    if (n <= n0) {
        return classicMultiply(A, B);
    }
//===============================================  


    // Dividir matrices
    Matrix A11, A12, A21, A22;
    Matrix B11, B12, B21, B22;

    splitMatrix(A, A11, A12, A21, A22);
    splitMatrix(B, B11, B12, B21, B22);

 
    // Calcular M1 ... M7
    Matrix M1 = hybridMultiply(
        addMatrix(A11, A22),
        addMatrix(B11, B22),
        n0
    );

    Matrix M2 = hybridMultiply(
        addMatrix(A21, A22),
        B11,
        n0
    );

    Matrix M3 = hybridMultiply(
        A11,
        subtractMatrix(B12, B22),
        n0
    );

    Matrix M4 = hybridMultiply(
        A22,
        subtractMatrix(B21, B11),
        n0
    );

    Matrix M5 = hybridMultiply(
        addMatrix(A11, A12),
        B22,
        n0
    );

    Matrix M6 = hybridMultiply(
        subtractMatrix(A21, A11),
        addMatrix(B11, B12),
        n0
    );

    Matrix M7 = hybridMultiply(
        subtractMatrix(A12, A22),
        addMatrix(B21, B22),
        n0
    );


    // Construir C11, C12, C21, C22
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


    // Unir resultado final
    return joinMatrices(
        C11,
        C12,
        C21,
        C22
    );
}