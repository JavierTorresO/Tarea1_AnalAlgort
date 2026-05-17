#include "timer.h"

#include <chrono>
#include <cmath>

// Medir tiempo de ejecución
double measureExecutionTime(
    function<void()> func
) {

    auto start = chrono::high_resolution_clock::now();

    func();

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duration = end - start;

    return duration.count();
}


// Calcular promedio
double average(
    const vector<double>& times
) {

    double sum = 0.0;

    for (double t : times) {
        sum += t;
    }

    return sum / times.size();
}


// Calcular desviación estándar
double standardDeviation(
    const vector<double>& times
) {

    double avg = average(times);

    double sum = 0.0;

    for (double t : times) {

        sum += (t - avg) * (t - avg);

    }

    return sqrt(sum / times.size());
}