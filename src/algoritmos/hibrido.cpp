#include "../../include/algoritmos/hibrido.h"
#include "../../include/utils/matrix.h"

// Función auxiliar (Core recursivo por índices para el Híbrido)
void hybrid_core(
    const Matrix& A, int rA, int cA,
    const Matrix& B, int rB, int cB,
    Matrix& C, int rC, int cC,
    int n, int n0
) {
    
    // CASO BASE: Umbral n0 alcanzado
    // Ejecutamos el algoritmo clásico sobre los índices actuales
    if (n <= n0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double sum = 0;
                for (int k = 0; k < n; k++) {
                    sum += A[rA + i][cA + k] * B[rB + k][cB + j];
                }
                C[rC + i][cC + j] = sum;
            }
        }
        return;
    }

    // logica de Strassen (dividir, calcular M1 a M7, combinar) con llamadas recursivas a hybrid_core
    int half = n / 2;

    // Buffers temporales estrictamente necesarios
    Matrix T1 = createMatrix(half);
    Matrix T2 = createMatrix(half);
    
    // Matrices para almacenar los 7 productos
    Matrix M1 = createMatrix(half);
    Matrix M2 = createMatrix(half);
    Matrix M3 = createMatrix(half);
    Matrix M4 = createMatrix(half);
    Matrix M5 = createMatrix(half);
    Matrix M6 = createMatrix(half);
    Matrix M7 = createMatrix(half);

    // Calcular M1 a M7 con llamadas recursivas a hybrid_core
    addSubMatrix(A, rA, cA,          A, rA + half, cA + half,  T1, 0, 0, half); 
    addSubMatrix(B, rB, cB,          B, rB + half, cB + half,  T2, 0, 0, half); 
    hybrid_core(T1, 0, 0, T2, 0, 0, M1, 0, 0, half, n0);                          

    addSubMatrix(A, rA + half, cA,   A, rA + half, cA + half,  T1, 0, 0, half); 
    hybrid_core(T1, 0, 0, B, rB, cB, M2, 0, 0, half, n0);                         

    subSubMatrix(B, rB, cB + half,   B, rB + half, cB + half,  T2, 0, 0, half); 
    hybrid_core(A, rA, cA, T2, 0, 0, M3, 0, 0, half, n0);                         

    subSubMatrix(B, rB + half, cB,   B, rB, cB,                T2, 0, 0, half); 
    hybrid_core(A, rA + half, cA + half, T2, 0, 0, M4, 0, 0, half, n0);           

    addSubMatrix(A, rA, cA,          A, rA, cA + half,         T1, 0, 0, half); 
    hybrid_core(T1, 0, 0, B, rB + half, cB + half, M5, 0, 0, half, n0);           

    subSubMatrix(A, rA + half, cA,   A, rA, cA,                T1, 0, 0, half); 
    addSubMatrix(B, rB, cB,          B, rB, cB + half,         T2, 0, 0, half); 
    hybrid_core(T1, 0, 0, T2, 0, 0, M6, 0, 0, half, n0);                          

    subSubMatrix(A, rA, cA + half,   A, rA + half, cA + half,  T1, 0, 0, half); 
    addSubMatrix(B, rB + half, cB,   B, rB + half, cB + half,  T2, 0, 0, half); 
    hybrid_core(T1, 0, 0, T2, 0, 0, M7, 0, 0, half, n0);                          

    // Construir C directamente sobre sus cuadrantes
    addSubMatrix(M1, 0, 0, M4, 0, 0, C, rC, cC, half);          
    subSubMatrix(C, rC, cC, M5, 0, 0, C, rC, cC, half);         
    addSubMatrix(C, rC, cC, M7, 0, 0, C, rC, cC, half);         

    addSubMatrix(M3, 0, 0, M5, 0, 0, C, rC, cC + half, half);

    addSubMatrix(M2, 0, 0, M4, 0, 0, C, rC + half, cC, half);

    subSubMatrix(M1, 0, 0, M2, 0, 0, C, rC + half, cC + half, half); 
    addSubMatrix(C, rC + half, cC + half, M3, 0, 0, C, rC + half, cC + half, half); 
    addSubMatrix(C, rC + half, cC + half, M6, 0, 0, C, rC + half, cC + half, half); 
}

// Función principal expuesta
Matrix hybridMultiply(const Matrix& A, const Matrix& B, int n0) {
    int n = A.size();
    Matrix C = createMatrix(n);
    hybrid_core(A, 0, 0, B, 0, 0, C, 0, 0, n, n0);
    return C;
}