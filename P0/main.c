/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P0
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3 DATE: 10/02/2025
*/

// comentario: para seleccionar el modo, comentar o descomentar la siguiente linea
//#define STRUCT_MODE

#include <stdio.h>
#include <stdlib.h>

// incluir el fichero de cabecera segun el modo seleccionado
#ifdef STRUCT_MODE
#include "rational_struct.h"
#else
#include "rational_pointer.h"
#endif

int main(void) {
    // definir dos numeros racionales con valores de ejemplo
    int n1 = 1134903170, d1 = 1836311903;
    int n2 = 433494437, d2 = 701408733;

#ifdef STRUCT_MODE
    // modo con estructuras (paso por valor)
    Rational r1 = createRational(n1, d1);
    Rational r2 = createRational(n2, d2);
    Rational suma = sum(r1, r2);

    // imprimir resultados
    printf("racional 1: %d/%d\n", numerator(r1), denominator(r1));
    printf("racional 2: %d/%d\n", numerator(r2), denominator(r2));
    printf("suma: %d/%d\n", numerator(suma), denominator(suma));
#else
    // modo con punteros (memoria dinamica)
    Rational *r1 = createRational(n1, d1);
    Rational *r2 = createRational(n2, d2);
    Rational *suma = sum(r1, r2);

    // imprimir resultados
    printf("racional 1: %d/%d\n", numerator(r1), denominator(r1));
    printf("racional 2: %d/%d\n", numerator(r2), denominator(r2));
    printf("suma: %d/%d\n", numerator(suma), denominator(suma));

    // liberar la memoria asignada
    free(r1);
    free(r2);
    free(suma);
#endif

    return 0;
}
