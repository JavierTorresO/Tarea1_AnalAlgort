#ifndef TIMER_H
#define TIMER_H

#include <vector>
#include <functional>

using namespace std;

// Medir tiempo de ejecución (milisegundos)
double measureExecutionTime(
    function<void()> func
);

// Promedio de tiempos
double average(
    const vector<double>& times
);

// Desviación estándar
double standardDeviation(
    const vector<double>& times
);

#endif