# Proyecto de Prácticas PRO2 2025

## Descripción General

Este repositorio contiene las prácticas desarrolladas para la asignatura **Programación II** (Curso 2024/25) de la Facultad de Informática. Cada práctica se organiza en un subdirectorio propio y se compila utilizando **CMake**.  
Actualmente, se encuentra disponible la **Práctica 0 (P0)**, cuyo objetivo es aprender a utilizar ficheros de cabecera (.h) y organizar el código en módulos en C, centrándose en el manejo de números racionales.

## Estructura del Repositorio

- **CMakeLists.txt (raíz):**  
  Archivo de configuración principal que agrega cada práctica como subdirectorio.  
  Actualmente, se agrega el subdirectorio `P0`.

- **Subdirectorios de prácticas:**
  - **P0:**
    - `main.c`
    - `rational_struct.c` y `rational_struct.h`
    - `rational_pointer.c` y `rational_pointer.h`
    - `CMakeLists.txt` específico para la práctica P0.

- **.gitignore:**  
  Se han definido reglas para ignorar archivos y directorios generados durante la compilación y depuración (por ejemplo, carpetas de build, binarios, logs, etc.).

## Práctica 0 (P0) – Manejo de Números Racionales

### Objetivo

La práctica P0 tiene como objetivo aprender a:
- Utilizar ficheros de cabecera (.h).
- Organizar el código en módulos en C.

Se implementa el manejo de números racionales a través de dos versiones:

- **rational_struct:**  
  Implementación basada en estructuras (paso por valor).

- **rational_pointer:**  
  Implementación basada en punteros (uso de memoria dinámica).

El programa principal (`main.c`) crea y suma dos números racionales utilizando las funciones definidas en ambos módulos.

### Requisitos del Enunciado

- **Implementaciones:**  
  Se deben desarrollar dos versiones del código:
  1. Implementación con estructura (`rational_struct`).
  2. Implementación con punteros (`rational_pointer`).

- **Funciones obligatorias:**
  - `Rational createRational(int n, int d)`: Crea un número racional a partir de un numerador `n` y un denominador `d`.
  - `int numerator(Rational r)`: Devuelve el numerador del número racional.
  - `int denominator(Rational r)`: Devuelve el denominador del número racional.
  - `Rational sum(Rational r1, Rational r2)`: Suma dos números racionales.

- **Normas de presentación:**
  - Cada fichero debe incluir un encabezado con la información de los autores, grupo y fecha.
  - Los nombres de los ficheros deben coincidir exactamente con los indicados en el enunciado.
  - Los ficheros a entregar son: `main.c`, `rational_struct.c`, `rational_struct.h`, `rational_pointer.c` y `rational_pointer.h`.

## Normas de Entrega y Evaluación

### Normas Generales de la Asignatura

- El código debe ser compilable en gcc en el servidor de referencia.
- No se deben utilizar variables globales.
- El código debe estar organizado en módulos, funciones y procedimientos, incluyendo comentarios adecuados, indentación correcta y el uso de identificadores significativos.
- Se valorará la eficacia, eficiencia, control de errores, claridad y modularidad.
- Las prácticas incluirán entregas parciales evaluadas de forma automática; no presentarlas o no superarlas conllevará penalizaciones en la nota final.

### Normas Específicas de la Práctica P0

- **Entrega:**
  - **Plazos y forma de entrega:**
    - La entrega se realizará en el enlace designado del Campus Virtual.
    - Es obligatorio realizar la entrega en pareja; sin embargo, un único miembro del equipo debe subir todos los ficheros.
    - La entrega de la práctica P0 es obligatoria. No se admitirán entregas fuera de plazo, y el incumplimiento de esta norma se penalizará (por ejemplo, la práctica se considerará **NO PRESENTADA**).

  - **Ficheros a entregar:**
    - `main.c`
    - `rational_struct.c` y `rational_struct.h`
    - `rational_pointer.c` y `rational_pointer.h`

  - **Encabezados en los ficheros:**
    - Cada archivo debe incluir un encabezado con la siguiente información:
      ```
      TITLE: PROGRAMMING II LABS
      SUBTITLE: Practical P0
      AUTHOR 1: [Nombre completo]           LOGIN 1: [login/email]
      AUTHOR 2: [Nombre completo]           LOGIN 2: [login/email]
      GROUP: [grupo]   DATE: [dd/mm/aaaa]
      ```

- **Aspectos Evaluables:**
  - **Criterios Mínimos:**
    - La práctica debe ser compilable en gcc en el servidor de referencia.
    - El código no debe contener variables globales.
    - La estructura del código debe estar organizada en procedimientos y/o funciones (al menos una función/procedimiento por cada operación del programa principal).
    - Es obligatorio incluir comentarios claros y concisos, buena indentación y uso de identificadores significativos.

  - **Otros Criterios de Evaluación:**
    - **Eficacia:** Se evaluará el cumplimiento correcto de las especificaciones, con la implementación adecuada de todas las funcionalidades.
    - **Eficiencia:** Se valorará que el código evite operaciones o procesos innecesarios y que utilice algoritmos eficientes.
    - **Control de errores:** Se debe realizar un control exhaustivo de los posibles errores de ejecución (por ejemplo, control de errores en la asignación de memoria, manejo de denominadores nulos, etc.).
    - **Claridad y Modularidad:** Se valorará la claridad del código, la correcta organización modular y la reutilización de módulos.
    - **Seguimiento de la práctica:** La práctica incluirá entregas parciales a lo largo del desarrollo, las cuales serán evaluadas de forma automática. No presentar o no superar estas entregas parciales conllevará penalizaciones en la nota final.

## Configuración y Compilación

El proyecto utiliza **CMake** y está configurado para compilar con el estándar **C99**.  
En el subdirectorio `P0`, el archivo `CMakeLists.txt` permite compilar la práctica en dos modos mediante la variable `USE_STRUCT_MODE`:

- **Modo Struct:**
  - Se define la macro `STRUCT_MODE` mediante la línea `set(USE_STRUCT_MODE ON)` en el CMakeLists.txt.
  - Se utiliza el fichero `rational_struct.c`.

- **Modo Punteros:**
  - Si se comenta o elimina la definición de `USE_STRUCT_MODE`, se compila en modo punteros.
  - Se utiliza el fichero `rational_pointer.c`.

## Autores e Información Adicional

- **Mateo Palmeiro Muniz**  
  *Email:* [mateo.palmeiro@udc.es](mailto:mateo.palmeiro@udc.es)  
  **Acerca de Mateo:**

- **Nicolas Otero Costa**  
  *Email:* [nicolas.otero1@udc.es](mailto:nicolas.otero1@udc.es)  
  **Acerca de Nicolas:**
