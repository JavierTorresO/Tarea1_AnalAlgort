# Tarea 1: Análisis de Algoritmos - Multiplicación de Matrices

Este repositorio contiene la implementación y el análisis de rendimiento empírico de tres algoritmos de multiplicación de matrices cuadradas ($n \times n$):

1. **Algoritmo Clásico** ($O(n^3)$)
2. **Algoritmo de Strassen** ($O(n^{\log_2 7})$)
3. **Algoritmo Híbrido** (Combina Strassen con el Clásico utilizando un umbral $n_0$ optimizado para la memoria caché).

## Requisitos Previos

Para compilar y ejecutar este proyecto, el sistema debe contar con:

- **Compilador C++:** Soporte para el estándar C++17 (ej. `g++`).
- **GNU Make:** Para la automatización de la compilación.
- **Python 3:** Para la generación de gráficos de análisis (requiere las librerías `pandas`, `matplotlib` y `numpy`).
- **Entorno:** Sistema operativo basado en Unix (Linux / WSL en Windows) debido al uso de herramientas de medición de tiempo.

## Instrucciones de Compilación

El proyecto utiliza un `Makefile` para gestionar la compilación de forma limpia y eficiente. Para compilar todos los archivos fuente y generar los ejecutables de experimentación, sitúate en la raíz del proyecto y ejecuta:

`make`

Este comando creará automáticamente una carpeta llamada `build/` donde se alojarán los ejecutables (`exp_reales`, `exp_enteras`, `exp_dispersas`, `exp_estructuradas`, `exp_hibrido`).

_Nota: Para limpiar los binarios y recompilar desde cero, puedes usar el comando `make clean`._

## Instrucciones de Ejecución

Los ejecutables utilizan una suite de medición de rendimiento (basada en la herramienta `uhr`) que registra el tiempo promedio, desviación estándar y cuartiles de la ejecución en formato CSV.

El formato general para ejecutar cualquier prueba es:

`./build/<nombre_ejecutable> <archivo_salida.csv> <repeticiones> <n_inicial> <n_final> <factor_multiplicativo>`

### Ejemplo de Ejecución

Para recolectar los datos de rendimiento sobre matrices de números reales (tamaños desde $n=64$ hasta $n=512$, multiplicando $n$ por 2 en cada paso, con 32 repeticiones estadísticas), el comando es:

`./build/exp_reales resultados/reales.csv 32 64 512 2`

Se requiere modificar internamente qué algoritmo se llama en cada archivo `exp_*.cpp` (descomentando la línea correspondiente a `classicMultiply`, `strassenMultiply` o `hybridMultiply`) y recompilar con `make` para extraer los datos de cada método individualmente.

## Generación de Gráficos (Escala Log-Log)

Una vez que se hayan recolectado todos los datos en formato CSV dentro de la carpeta `resultados/`, se puede generar el análisis visual comparativo exigido en el enunciado.

Asegúrate de estar posicionado en la raíz del proyecto y ejecuta el script de Python:

`python3 graficos_finales.py`

Este script leerá automáticamente los archivos CSV y generará una imagen llamada `grafico_comparativo_final.png` en la carpeta `resultados/`, mostrando las curvas de rendimiento empírico ajustadas con las curvas de complejidad teórica asintótica.

## Estructura del Proyecto

- `include/`: Cabeceras (`.h`) de los algoritmos y herramientas de utilidad.
- `src/`: Implementación de los algoritmos (`.cpp`) y generadores de matrices.
- `experiments/`: Archivos base con la suite de medición integrando los algoritmos.
- `build/`: Directorio autogenerado que contiene los ejecutables compilados.
- `resultados/`: Directorio destinado a almacenar los archivos CSV generados por las pruebas y los gráficos finales.
- `graficos_finales.py`: Script de Python para la visualización de los datos.
- `Makefile`: Reglas automatizadas de compilación estricta (flag `-O0`).
