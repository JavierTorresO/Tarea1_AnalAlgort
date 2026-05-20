/** Experimento 1: Matrices Reales Aleatorias [0,1] */

#include <cstdint>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

// Incluimos el archivo utils del profesor (guardado en experiments/)
#include "utils.cpp"

// Incluimos nuestras cabeceras del proyecto
#include "../include/utils/matrix.h"
#include "../include/utils/generadores.h"
#include "../include/algoritmos/strassen.h"
#include "../include/algoritmos/clasico.h"

int main(int argc, char *argv[])
{
    // Validate and sanitize input
    std::int64_t runs, lower, upper, step;
    validate_input(argc, argv, runs, lower, upper, step);

    // Set up clock variables
    std::int64_t n, i, executed_runs;
    std::int64_t total_runs_multiplicative = runs * (floor(log(upper / double(lower)) / log(step)) + 1);
    std::vector<double> times(runs);
    std::vector<double> q;
    double mean_time, time_stdev, dev;
    auto begin_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    
    // Dejaremos la medición en milisegundos para que los números sean más legibles
    std::chrono::duration<double, std::milli> elapsed_time;

    // File to write time data
    std::ofstream time_data;
    time_data.open(argv[1]);
    time_data << "n,t_mean,t_stdev,t_Q0,t_Q1,t_Q2,t_Q3,t_Q4" << std::endl;

    // Begin testing
    std::cerr << "\033[0;36mRunning tests...\033[0m" << std::endl << std::endl;
    executed_runs = 0;
    
    for (n = lower; n <= upper; n *= step) {
        mean_time = 0;
        time_stdev = 0;

        // =========================================================
        // CONFIGURACIÓN DEL EXPERIMENTO (Fuera de la medición de tiempo)
        // =========================================================
        // Generamos matrices con reales entre -100 y 100 de tamaño n x n
        Matrix A = randomIntMatrix(n, -100, 100);
        Matrix B = randomIntMatrix(n, -100, 100);

        // Run to compute elapsed time
        for (i = 0; i < runs; i++) {
            display_progress(++executed_runs, total_runs_multiplicative);

            begin_time = std::chrono::high_resolution_clock::now();
            
            // =========================================================
            // FUNCIÓN A MEDIR
            // Comentar algortimo no usado

            //Matrix C = strassenMultiply(A, B); 
            Matrix C = classicMultiply(A, B);
            // =========================================================

            end_time = std::chrono::high_resolution_clock::now();

            elapsed_time = end_time - begin_time;
            times[i] = elapsed_time.count();

            mean_time += times[i];
        }

        // Compute statistics
        mean_time /= runs;

        for (i = 0; i < runs; i++) {
            dev = times[i] - mean_time;
            time_stdev += dev * dev;
        }

        time_stdev /= runs - 1; // Subtract 1 to get unbiased estimator
        time_stdev = std::sqrt(time_stdev);

        quartiles(times, q);

        time_data << n << "," << mean_time << "," << time_stdev << ",";
        time_data << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << "," << q[4] << std::endl;
    }

    std::cerr << std::endl << std::endl;
    std::cerr << "\033[1;32mDone!\033[0m" << std::endl;

    time_data.close();

    return 0;
}