#include <iostream>
#include <cassert>

#include "../utils/matrix.h"
#include "../utils/generadores.h"

#include "../algoritmos/clasico/clasico.h"
#include "../algoritmos/strassen/strassen.h"

using namespace std;

//TEST CON "n" MUY PEQUEÑOS, SOLO PARA CONFIRMAR FUNCIONALIDADES 

int main() {
    //para estos tamaños (2,4,8,16) generar matrices aleatorias, multiplicar con ambos algoritmos y comparar resultados
    vector<int> sizes = {2, 4, 8, 16};

    for (int n : sizes) {

        cout << "==========================" << endl;
        cout << "Testing n = " << n << endl;
        cout << "==========================" << endl;

        for (int test = 0; test < 10; test++) {

            Matrix A = randomIntMatrix(n, -10, 10);
            Matrix B = randomIntMatrix(n, -10, 10);

            Matrix classic =
                classicMultiply(A, B);

            Matrix strassen =
                strassenMultiply(A, B);

            assert(
                areEqual(classic, strassen) //resultados iguales->pass
            );
        }

        cout << "PASS" << endl;
        cout << endl;
    }

    return 0;
}