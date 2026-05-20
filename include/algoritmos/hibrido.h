#ifndef HIBRIDO_H
#define HIBRIDO_H

#include "utils/matrix.h"

// Multiplicación híbrida: Strassen + clásico bajo umbral n0
Matrix hybridMultiply(
    const Matrix& A,
    const Matrix& B,
    int n0
);

#endif

//para tamaños pequeños, clásico suele ser más rápido
//para tamaños grandes, Strassen gana
// ->Entonces el híbrido normalmente obtiene "mejor rendimiento real"