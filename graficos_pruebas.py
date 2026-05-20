import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Configuración de los datasets y algoritmos a leer
tipos_matrices = ['reales', 'enteras', 'dispersas', 'estructuradas']
titulos = ['Matrices Reales [0,1]', 'Matrices Enteras [-100, 100]', 'Matrices Dispersas (90% ceros)', 'Matrices Estructuradas (Identidad)']
algoritmos = ['clasico', 'strassen', 'hibrido']
colores = {'clasico': 'blue', 'strassen': 'red', 'hibrido': 'green'}
marcadores = {'clasico': 'o', 'strassen': 's', 'hibrido': '^'}
nombres = {'clasico': 'Clásico O(n^3)', 'strassen': 'Strassen O(n^log2(7))', 'hibrido': 'Híbrido (n0=64)'}

# Crear una figura con 4 subgráficos (2x2)
fig, axs = plt.subplots(2, 2, figsize=(15, 12))
axs = axs.flatten()

for i, tipo in enumerate(tipos_matrices):
    ax = axs[i]
    
    for algo in algoritmos:
        archivo = f'resultados/{algo}_{tipo}.csv'
        
        # Verificar si el archivo existe antes de graficar (evita errores si falta alguno)
        if os.path.exists(archivo):
            df = pd.read_csv(archivo)
            n = df['n'].values
            t_mean = df['t_mean'].values
            
            ax.loglog(n, t_mean, marker=marcadores[algo], linestyle='-', 
                      color=colores[algo], label=nombres[algo], base=2, linewidth=2, markersize=8)
    
    # Configuración estética de cada subgráfico
    ax.set_title(titulos[i], fontsize=14, fontweight='bold')
    ax.set_xlabel('Tamaño de la matriz (n)', fontsize=12)
    ax.set_ylabel('Tiempo promedio (ms)', fontsize=12)
    ax.grid(True, which="both", ls="--", alpha=0.6)
    ax.legend(fontsize=10)

# Ajustar el espaciado global
plt.suptitle('Análisis de Rendimiento Asintótico: Multiplicación de Matrices', fontsize=18, y=1.02)
plt.tight_layout()

# Guardar el resultado final
plt.savefig('resultados/grafico_comparativo_final.png', dpi=300, bbox_inches='tight')
print("¡Gráficos generados exitosamente en 'resultados/grafico_comparativo_final.png'!")