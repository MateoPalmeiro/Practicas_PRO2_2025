/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P0
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2:
GROUP: 1.2 DATE: 04/02/2025
*/

#include <stdio.h>
#include <stdlib.h>

#ifdef STRUCT
#include "rational_struct.h"
#else
#include "rational_pointer.h"
#endif

int main(void) {
    // definir dos numeros racionales con valores de ejemplo
    int n1 = 1, d1 = 2;
    int n2 = 3, d2 = 4;

#ifdef STRUCT
    // version con estructura (paso por valor)
    Rational r1 = createRational(n1, d1);
    Rational r2 = createRational(n2, d2);
    Rational suma = sum(r1, r2);

    // imprimir resultados
    printf("racional 1: %d/%d\n", numerator(r1), denominator(r1));
    printf("racional 2: %d/%d\n", numerator(r2), denominator(r2));
    printf("suma: %d/%d\n", numerator(suma), denominator(suma));
#else
    // version con punteros (memoria dinamica)
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
