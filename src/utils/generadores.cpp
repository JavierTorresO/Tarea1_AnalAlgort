#include "utils/generadores.h"

#include <random>

// Generador global de números aleatorios
random_device rd;
mt19937 gen(rd());


// Matriz de enteros aleatorios
Matrix randomIntMatrix(
    int n,
    int minValue,
    int maxValue
) {

    Matrix A = createMatrix(n);
    uniform_int_distribution<> dist(minValue, maxValue);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = dist(gen);
        }
    }
    return A;
}


// Matriz de doubles aleatorios
Matrix randomDoubleMatrix(
    int n,
    double minValue,
    double maxValue
) {

    Matrix A = createMatrix(n);
    uniform_real_distribution<> dist(minValue, maxValue);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = dist(gen);
        }
    }
    return A;
}


// Matriz identidad (1 en la diagonal y todo lo otro cero)
Matrix identityMatrix(int n) {

    Matrix I = createMatrix(n);

    for (int i = 0; i < n; i++) {
        I[i][i] = 1.0;
    }
    return I;
}


// Matriz constante
Matrix constantMatrix(
    int n,
    double value
) {

    Matrix A = createMatrix(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = value;
        }
    }
    return A;
}


// Matriz dispersa
Matrix sparseMatrix(
    int n,
    double zeroProbability
) {

    Matrix A = createMatrix(n);

    uniform_real_distribution<> prob(0.0, 1.0);
    uniform_real_distribution<> valueDist(-100.0, 100.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double r = prob(gen);
            if (r < zeroProbability) {
                A[i][j] = 0.0;
            } else {
                A[i][j] = valueDist(gen);
            }
        }
    }
    return A;
}