import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df_clasico = pd.read_csv('resultados/clasico_reales.csv')
df_strassen = pd.read_csv('resultados/strassen_reales.csv')

n_clasico = df_clasico['n'].values
t_clasico = df_clasico['t_mean'].values

n_strassen = df_strassen['n'].values
t_strassen = df_strassen['t_mean'].values

plt.figure(figsize=(10, 6))

plt.loglog(n_clasico, t_clasico, marker='o', linestyle='-', color='blue', label='Clásico (Empírico)', base=2)
plt.loglog(n_strassen, t_strassen, marker='s', linestyle='-', color='red', label='Strassen (Empírico)', base=2)

# Calcular y graficar curvas teóricas ajustadas
# Para alinear la teoría con la práctica, calculamos una constante 'c' 
# usando el primer punto de datos de cada algoritmo.

# Teórico Clásico: O(n^3) -> t = c * n^3
c_clasico = t_clasico[0] / (n_clasico[0] ** 3)
t_teorico_clasico = c_clasico * (n_clasico ** 3)
plt.loglog(n_clasico, t_teorico_clasico, linestyle='--', color='cyan', label='Clásico O(n^3) Teórico', base=2)

# Teórico Strassen: O(n^log2(7)) -> t = c * n^2.807
log2_7 = np.log2(7)
c_strassen = t_strassen[0] / (n_strassen[0] ** log2_7)
t_teorico_strassen = c_strassen * (n_strassen ** log2_7)
plt.loglog(n_strassen, t_teorico_strassen, linestyle='--', color='orange', label='Strassen O(n^log2(7)) Teórico', base=2)

plt.title('Rendimiento: Clásico vs Strassen (Matrices Reales)', fontsize=14)
plt.xlabel('Tamaño de la matriz (n)', fontsize=12)
plt.ylabel('Tiempo promedio de ejecución (ms)', fontsize=12)
plt.grid(True, which="both", ls="--", alpha=0.5)
plt.legend()

plt.savefig('resultados/grafico_reales.png', dpi=300, bbox_inches='tight')
print("Gráfico generado con éxito en 'resultados/grafico_reales.png'")