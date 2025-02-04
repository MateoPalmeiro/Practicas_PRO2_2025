# Proyecto P0 - Manejo de Números Racionales

## Descripción

Este proyecto corresponde a la práctica P0 de la asignatura de Programación II (Curso 2024/25). El objetivo principal es aprender a utilizar ficheros de cabecera (.h) y organizar el código en módulos en C. El proyecto se centra en el manejo de números racionales y ofrece dos implementaciones:

- **rational_struct:** Basada en el uso de estructuras.
- **rational_pointer:** Basada en el uso de punteros (memoria dinámica).

El programa principal (`main.c`) crea y suma dos números racionales utilizando las funciones definidas en ambos módulos.

## Requisitos del Enunciado

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
