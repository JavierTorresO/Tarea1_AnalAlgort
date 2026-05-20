#include "clasico.h"

// Multiplicación clásica de matrices
Matrix classicMultiply(
    const Matrix& A,
    const Matrix& B
) {

    int n = A.size();

    Matrix C = createMatrix(n);

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            for (int k = 0; k < n; k++) {

                C[i][j] += A[i][k] * B[k][j];

            }
        }
    }

    return C;
}

//Recibe 2 matrices cuadradas A y B y devuelve una matriz C=A*B
//Tres loop anidadops (for), entonces la complejidad es O(n^3)