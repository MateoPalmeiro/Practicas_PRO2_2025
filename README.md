# Proyecto de Prácticas PRO2 2025

## Descripción General

Este repositorio contiene las prácticas desarrolladas para la asignatura **Programación II** (Curso 2024/25) de la Facultad de Informática. Cada práctica se organiza en un subdirectorio propio y se compila utilizando **CMake**.  
Actualmente se encuentran disponibles las Prácticas 0 y 1, cuyo objetivo es aprender a modularizar el código en C mediante el uso de ficheros de cabecera y el desarrollo de Tipos Abstractos de Datos (TADs).
- La **Práctica 0 (P0)** se centra en el manejo de números racionales, implementado en dos versiones (estructuras y punteros).
- La **Práctica 1 (P1)** consiste en desarrollar una plataforma de subastas de consolas retro. Se debe diseñar un TAD Lista NO ORDENADA que gestione las consolas (altas, bajas y modificaciones de precio) y se implementa en dos versiones: estática y dinámica.

## Estructura del Repositorio

La estructura del repositorio se organiza de la siguiente manera:
- **.idea/**  
  Configuraciones del IDE (no se suben al repositorio).
- **P0/**  
  Código fuente de la Práctica 0 (incluye main.c, rational_struct.c/h, rational_pointer.c/h, CMakeLists.txt de P0).
- **P1/**  
  Código fuente de la Práctica 1 (incluye main.c, test.c, types.h, static_list.c/h, dynamic_list.c/h, CMakeLists.txt de P1 y config.cmake).
- **bin/**  
  Ficheros de entrada (txt) y los ejecutables generados, especialmente para la Práctica 1.
- **cmake-build-debug/**  
  Carpeta generada por CLion para la compilación.
- **script_minimos/**  
  Carpeta que contiene los ficheros de entrada para el programa principal de la Práctica 1 (por ejemplo, new.txt, bid.txt, delete.txt y sus salidas de referencia).
- **script_test/**  
  Carpeta que contiene los ficheros de entrada y salida esperada para probar los TADs de la Práctica 1.
- **.gitignore**  
  Archivo que excluye archivos y carpetas generados (por ejemplo, .idea, cmake-build-debug, etc.).
- **CMakeLists.txt (raíz)**  
  Archivo maestro que agrega los subdirectorios de las prácticas.
- **README.md**  
  Este documento.
- **script.sh**  
  Script para compilar y ejecutar las pruebas de la Práctica 1.

## Práctica 0 (P0) – Manejo de Números Racionales

### Objetivo

Aprender a:
- Utilizar ficheros de cabecera (.h) y modularizar el código en C.
- Implementar y organizar el código en módulos (estructuras y punteros).
- Desarrollar operaciones con números racionales (crear, sumar, etc.).

### Requisitos del Enunciado

- Implementar dos versiones:
  1. Con estructura (rational_struct).
  2. Con punteros (rational_pointer).
- Ficheros a entregar: `main.c`, `rational_struct.c` y `.h`, `rational_pointer.c` y `.h`.
- Incluir encabezados con la información de los autores, grupo y fecha.

## Práctica 1 (P1) – Plataforma de Subastas de Consolas Retro

### Objetivo

El problema consiste en implementar funcionalidades para una plataforma de subastas de consolas retro. Se debe diseñar una estructura de datos que almacene la información asociada a cada consola y, a partir de ello, implementar un TAD Lista NO ORDENADA (en dos versiones: estática y dinámica) para gestionar las consolas.  
El programa principal debe procesar las siguientes operaciones, leídas desde un fichero de entrada:
- **N (New):** Alta de una nueva consola. Formato:  
  `N consoleId userId brand price`
- **D (Delete):** Baja de una consola. Formato:  
  `D consoleId`
- **B (Bid):** Puja sobre una consola. Formato:  
  `B consoleId userId price`
- **S (Stats):** Listado de consolas y estadisticas. Formato:  
  `S`

Cada operacion debe mostrar una cabecera de 20 asteriscos y el mensaje de salida en un formato exacto, tal como se especifica en los pdfs.

### Fases de la Practica

#### Fase 1 – Implementacion del TAD
- **Libreria Types:**  
  Se definen los tipos necesarios:
  - `NAME_LENGTH_LIMIT`, `tUserId`, `tConsoleId`, `tConsoleBrand`, `tConsolePrice`, `tBidCounter` y `tItemL`.
- **TAD Lista:**  
  Implementar dos versiones de la lista NO ORDENADA:
  - **Estatica:** Con array de tamaño máximo 25 y `tPosL` como entero (LNULL = -1).
  - **Dinamica:** Lista enlazada simple, con `tPosL` como puntero y LNULL = NULL.
- Se prueba el TAD con el fichero `test.c` incluido.

#### Fase 2 – Programa Principal
- El programa (`main.c`) debe leer un fichero de entrada con las peticiones numeradas y procesarlas:
  - Imprimir cabeceras de operacion (20 asteriscos, luego el mensaje).
  - Para la operacion New, debe dar error si ya existe la consola o si la marca no es "nintendo" o "sega".
  - Para Delete, Bid y Stats, mostrar la salida exacta según el enunciado (incluyendo formato de tabla en Stats).

### Requisitos de Entrega y Evaluacion
- El proyecto debe compilar sin errores en gcc en el servidor de referencia.
- No se deben usar variables globales (salvo para la lista si se justifica).
- El código debe estar debidamente comentado y estructurado.
- Las salidas del programa deben coincidir exactamente con las de referencia.
- Se realizaran entregas parciales y una entrega final; en cada entrega se evaluara el correcto funcionamiento del TAD y el programa principal.

## Configuracion y Compilacion

El proyecto utiliza **CMake** y compila con el estandar **C99**.  
Cada practica tiene su propio CMakeLists.txt y config.cmake para seleccionar la implementacion (estatica o dinamica) y el fichero de entrada para main.

- **P0:** Se compila con la variable `USE_STRUCT_MODE` para seleccionar la implementacion.
- **P1:** En el archivo config.cmake se debe elegir entre STATIC y DYNAMIC, y el fichero de entrada (por ejemplo, new.txt, bid.txt, delete.txt).

El script `script.sh` y las carpetas `script_minimos` y `script_test` permiten probar la practica de forma automatizada, comparando la salida del programa con los ficheros de referencia.

## Ejecucion del Script

Para ejecutar la practica P1 en la maquina de referencia o localmente:
1. Asegurate de que en la carpeta raíz del proyecto se encuentre la carpeta P1, junto con bin, script_minimos, script_test, script.sh, CMakeLists.txt y config.cmake.
2. Desde una terminal en la carpeta raíz, otorga permisos de ejecucion al script:
   ```bash
   chmod u+x script.sh
3. Ejecuta el script con la opcion deseada:
  - Para ejecutar el programa principal:
    ```bash
    ./script.sh -p main
    ```
  - Para ejecutar el programa de test:
    ```bash
    ./script.sh -p test
    ```

## Autores e Informacion Adicional

- **Mateo Palmeiro Muniz**  
  *Email:* [mateo.palmeiro@udc.es](mailto:mateo.palmeiro@udc.es)  
  **Acerca de Mateo:**  

- **Nicolas Otero Costa**  
  *Email:* [nicolas.otero1@udc.es](mailto:nicolas.otero1@udc.es)  
  **Acerca de Nicolas:**