/** Experimento 2: Búsqueda del mejor umbral n0 para el Híbrido */

#include <cstdint>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "utils.cpp"

#include "../include/utils/matrix.h"
#include "../include/utils/generadores.h"
#include "../include/algoritmos/hibrido.h"

int main(int argc, char *argv[])
{
    std::int64_t runs, lower, upper, step;
    validate_input(argc, argv, runs, lower, upper, step);

    // Reemplazamos 'n' por 'n0' para que el loop controle el umbral
    std::int64_t n0, i, executed_runs;
    std::int64_t total_runs_multiplicative = runs * (floor(log(upper / double(lower)) / log(step)) + 1);
    std::vector<double> times(runs);
    std::vector<double> q;
    double mean_time, time_stdev, dev;
    auto begin_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_time;

    std::ofstream time_data;
    time_data.open(argv[1]);
    time_data << "n0,t_mean,t_stdev,t_Q0,t_Q1,t_Q2,t_Q3,t_Q4" << std::endl;

    std::cerr << "\033[0;36mRunning tests...\033[0m" << std::endl << std::endl;
    executed_runs = 0;

    // fijamos un n grande para que el umbral n0 tenga impacto real en el rendimiento (n=512)
    const int FIXED_N = 512;
    std::cerr << "Generando matrices fijas de " << FIXED_N << "x" << FIXED_N << "..." << std::endl;
    Matrix A = randomDoubleMatrix(FIXED_N, 0.0, 1.0);
    Matrix B = randomDoubleMatrix(FIXED_N, 0.0, 1.0);

    // Iteramos variando el n0 (con salto multiplicativo)
    for (n0 = lower; n0 <= upper; n0 *= step) {
        mean_time = 0;
        time_stdev = 0;

        for (i = 0; i < runs; i++) {
            display_progress(++executed_runs, total_runs_multiplicative);

            begin_time = std::chrono::high_resolution_clock::now();
            
            // Evaluamos el Híbrido pasándole la matriz fija y el umbral dinámico n0
            Matrix C = hybridMultiply(A, B, n0);

            end_time = std::chrono::high_resolution_clock::now();

            elapsed_time = end_time - begin_time;
            times[i] = elapsed_time.count();

            mean_time += times[i];
        }

        mean_time /= runs;

        for (i = 0; i < runs; i++) {
            dev = times[i] - mean_time;
            time_stdev += dev * dev;
        }

        time_stdev /= runs - 1;
        time_stdev = std::sqrt(time_stdev);

        quartiles(times, q);

        time_data << n0 << "," << mean_time << "," << time_stdev << ",";
        time_data << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << "," << q[4] << std::endl;
    }

    std::cerr << std::endl << std::endl;
    std::cerr << "\033[1;32mDone!\033[0m" << std::endl;

    time_data.close();

    return 0;
}