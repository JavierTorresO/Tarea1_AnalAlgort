#include <iostream>

#include "../utils/matrix.h"
#include "../utils/generadores.h"

#include "../algoritmos/clasico/clasico.h"

using namespace std;

int main() {

    // TEST 1: Multiplicación por identidad

    cout << "TEST 1: Multiplicacion identidad" << endl;
    cout << "==============================" << endl;

    Matrix A = {
        {1, 2},
        {3, 4}
    };

    Matrix I = identityMatrix(2);

    Matrix result1 = classicMultiply(A, I);

    if (areEqual(A, result1)) {
        cout << "PASS" << endl;
    } else {
        cout << "FAIL" << endl;

        cout << "Resultado:" << endl;
        printMatrix(result1);
    }

    cout << endl;


    // TEST 2: Multiplicación por matriz cero

    cout << "TEST 2: Multiplicacion matriz cero" << endl;
    cout << "==============================" << endl;

    Matrix Z = createMatrix(2);

    Matrix result2 = classicMultiply(A, Z);

    Matrix expectedZero = {
        {0, 0},
        {0, 0}
    };

    if (areEqual(result2, expectedZero)) {
        cout << "PASS" << endl;
    } else {
        cout << "FAIL" << endl;

        cout << "Resultado:" << endl;
        printMatrix(result2);
    }

    cout << endl;


    // TEST 3: Caso manual conocido

    cout << "TEST 3: Caso manual conocido" << endl;
    cout << "==============================" << endl;

    Matrix B = {
        {5, 6},
        {7, 8}
    };

    Matrix expected = {
        {19, 22},
        {43, 50}
    };

    Matrix result3 = classicMultiply(A, B);

    if (areEqual(result3, expected)) {
        cout << "PASS" << endl;
    } else {
        cout << "FAIL" << endl;

        cout << "Resultado:" << endl;
        printMatrix(result3);
    }

    cout << endl;


    // TEST 4: Split y Join

    cout << "TEST 4: Split y Join" << endl;
    cout << "==============================" << endl;

    Matrix M = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    Matrix M11, M12, M21, M22;

    splitMatrix(M, M11, M12, M21, M22);

    Matrix reconstructed =
        joinMatrices(M11, M12, M21, M22);

    if (areEqual(M, reconstructed)) {
        cout << "PASS" << endl;
    } else {
        cout << "FAIL" << endl;

        cout << "Matriz original:" << endl;
        printMatrix(M);

        cout << "Reconstruida:" << endl;
        printMatrix(reconstructed);
    }

    cout << endl;


    // TEST 5: Suma y resta

    cout << "TEST 5: Suma y resta" << endl;
    cout << "==============================" << endl;

    Matrix C = addMatrix(A, B);

    Matrix D = subtractMatrix(C, B);

    if (areEqual(D, A)) {
        cout << "PASS" << endl;
    } else {
        cout << "FAIL" << endl;
    }

    cout << endl;


    // TEST 6: Matrices aleatorias 4x4

    cout << "TEST 6: Matrices aleatorias 4x4" << endl;
    cout << "==============================" << endl;

    Matrix R1 = randomIntMatrix(4, -10, 10);
    Matrix R2 = randomIntMatrix(4, -10, 10);

    Matrix R3 = classicMultiply(R1, R2);

    cout << "Matriz A:" << endl;
    printMatrix(R1);

    cout << endl;

    cout << "Matriz B:" << endl;
    printMatrix(R2);

    cout << endl;

    cout << "A * B:" << endl;
    printMatrix(R3);

    cout << endl;

    cout << "PASS (ejecucion completada)" << endl;

    return 0;
}