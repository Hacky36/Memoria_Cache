# Memoria_Cache

Comparación de desempeño de bucles anidados y multiplicación de matrices (clásica y por bloques), con análisis de localidad de datos y comportamiento de la memoria caché usando Valgrind/Callgrind y KCachegrind.

Trabajo del Laboratorio 2 — Escuela Profesional de Ciencia de la Computación, UNSA.

## Contenido del repositorio

```
Memoria_Cache/
├── dos_for_anidados.cpp          # Dos bucles for anidados (recorrido por filas vs. columnas)
├── dos_for_anidados              # Binario compilado (Linux/WSL)
├── seis_for_anidados.cpp         # Multiplicación clásica (3 bucles) y por bloques (6 bucles)
├── seis_for_anidados             # Binario compilado (Linux/WSL)
├── dos_for_anidados_carpeta/
│   ├── primerMetodo.py           # Mide y guarda tiempos del recorrido por filas
│   ├── segundoMetodo.py          # Mide y guarda tiempos del recorrido por columnas
│   └── comparacionMetodos.py     # Grafica la comparación de tiempos (matplotlib)
├── seis_for_anidados_carpeta/
│   ├── primerMetodo.py           # Mide y guarda tiempos de la multiplicación clásica
│   ├── segundoMetodo.py          # Mide y guarda tiempos de la multiplicación por bloques
│   └── comparacionMetodos.py     # Grafica la comparación de tiempos (matplotlib)
├── callgrind.out.5048            # Perfil Callgrind: dos bucles for anidados
├── callgrind.out.5055            # Perfil Callgrind: multiplicación clásica vs. bloques (BLOCK_SIZE=50)
├── callgrind.out.5569            # Perfil Callgrind: multiplicación por bloques, BLOCK_SIZE=8
├── callgrind.out.5637            # Perfil Callgrind: multiplicación por bloques, BLOCK_SIZE=32
├── callgrind.out.5650            # Perfil Callgrind: multiplicación por bloques, BLOCK_SIZE=16
├── callgrind.out.5663            # Perfil Callgrind: multiplicación por bloques, BLOCK_SIZE=64
└── .gitignore
```

## Requisitos

Todo el trabajo se ejecutó en **WSL (Ubuntu)** sobre Windows. Se necesita:

- `g++` (compilador C++)
- `valgrind` (con el módulo `callgrind`)
- `kcachegrind` (visualización de los perfiles de Callgrind)
- `python3` y la librería `matplotlib` (para las gráficas de tiempo)

### Instalación en WSL / Ubuntu

```bash
sudo apt update
sudo apt install -y build-essential valgrind kcachegrind python3 python3-pip python3-matplotlib
```

Si `kcachegrind` requiere entorno gráfico, en Windows 11 con WSLg funciona directamente. En versiones anteriores de WSL puede requerir un servidor X (por ejemplo VcXsrv).

## Compilación

Cada programa se compiló sin optimizaciones del compilador (`-O0`), para que las diferencias de tiempo observadas correspondan al patrón de acceso a memoria y no a optimizaciones automáticas:

```bash
# Dos bucles for anidados (filas vs. columnas)
g++ -g -O0 -o dos_for_anidados dos_for_anidados.cpp

# Multiplicación clásica vs. multiplicación por bloques
g++ -g -O0 -o seis_for_anidados seis_for_anidados.cpp
```

> Nota: para el experimento de variación de `BLOCK_SIZE` (8, 16, 32, 50, 64), se edita la constante `BLOCK_SIZE` dentro de `seis_for_anidados.cpp` antes de cada recompilación, y se repite el comando de compilación de arriba.

## Ejecución

### 1. Ejecutar los programas directamente

```bash
./dos_for_anidados
./seis_for_anidados
```

Cada ejecutable corre ambos métodos (por ejemplo `primerMetodo` y `segundoMetodo`) internamente, incrementando el tamaño de entrada `n`, y mide los tiempos con `std::chrono`.

### 2. Generar las gráficas de tiempo (Python/matplotlib)

Cada carpeta contiene los scripts que generan y comparan los tiempos de ejecución:

```bash
cd dos_for_anidados_carpeta
python3 comparacionMetodos.py
cd ..

cd seis_for_anidados_carpeta
python3 comparacionMetodos.py
cd ..
```

Estos scripts ejecutan `primerMetodo.py` y `segundoMetodo.py` con el mismo conjunto de dimensiones y grafican ambas curvas de tiempo para comparar visualmente el desempeño.

### 3. Análisis de caché con Valgrind/Callgrind

```bash
valgrind --tool=callgrind --cache-sim=yes ./dos_for_anidados
valgrind --tool=callgrind --cache-sim=yes ./seis_for_anidados
```

Esto genera un archivo `callgrind.out.<PID>` con los contadores de instrucciones, accesos a memoria y fallos de caché (L1, LL) por función.

### 4. Visualización con KCachegrind

```bash
kcachegrind callgrind.out.<PID> &
```

Por ejemplo, para ver el perfil de los dos bucles anidados generado en este repositorio:

```bash
kcachegrind callgrind.out.5048 &
```

Dentro de KCachegrind se puede seleccionar cada función (`primerMetodo`, `segundoMetodo`, etc.) para ver el desglose de `L1 Data Read Miss`, `LL Data Read Miss`, `Cycle Estimation`, entre otras métricas, tal como se reporta en el informe.

### 5. Experimento de variación de BLOCK_SIZE

Para reproducir el barrido de tamaño de bloque (8, 16, 32, 50, 64) reportado en el informe:

```bash
# Editar BLOCK_SIZE en seis_for_anidados.cpp, luego:
g++ -g -O0 -o seis_for_anidados seis_for_anidados.cpp
valgrind --tool=callgrind --cache-sim=yes ./seis_for_anidados
# Repetir para cada valor de BLOCK_SIZE
```

Cada corrida genera un `callgrind.out.<PID>` distinto (ver los incluidos en este repositorio como referencia de los resultados obtenidos: 5569, 5637, 5650, 5663).

## Resumen de resultados

El informe completo (PDF/LaTeX) con el análisis de complejidad computacional, localidad espacial/temporal y los resultados detallados de Callgrind/KCachegrind se encuentra en el documento del laboratorio entregado junto con este repositorio.

## Autor

Jheeremy Manuel Alvarez Astete — Escuela Profesional de Ciencia de la Computación, UNSA.
