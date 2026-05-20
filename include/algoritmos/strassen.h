#ifndef STRASSEN_H
#define STRASSEN_H

#include "../../utils/matrix.h"

// Multiplicación de matrices con Strassen
Matrix strassenMultiply(
    const Matrix& A,
    const Matrix& B
);

#endif