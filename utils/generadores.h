#ifndef GENERADORES_H
#define GENERADORES_H

#include "matrix.h"

// Matriz con enteros aleatorios
Matrix randomIntMatrix(
    int n,
    int minValue,
    int maxValue
);

// Matriz con doubles aleatorios
Matrix randomDoubleMatrix(
    int n,
    double minValue,
    double maxValue
);

// Matriz identidad
Matrix identityMatrix(int n);

// Matriz constante
Matrix constantMatrix(
    int n,
    double value
);

// Matriz dispersa
Matrix sparseMatrix(
    int n,
    double zeroProbability
);

#endif