/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P0 (rational_struct)
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3 DATE: 04/02/2025
*/

#ifdef STRUCT_MODE

#include <stdio.h>
#include <stdlib.h>
#include "rational_struct.h"

// funcion auxiliar para calcular el maximo comun divisor (mcd)
static int mcd(int a, int b) {
    if (b == 0)
        return a;
    return mcd(b, a % b);
}

// crea un numero racional a partir de un numerador n y un denominador d
// y simplifica la fraccion
Rational createRational(int n, int d) {
    if (d == 0) {
        fprintf(stderr, "error: denominador no puede ser 0.\n");
        exit(EXIT_FAILURE);
    }
    // normalizar el signo: el denominador siempre sera positivo
    if (d < 0) {
        n = -n;
        d = -d;
    }
    // calcular el mcd para simplificar la fraccion
    int divisor = mcd((n < 0) ? -n : n, (d < 0) ? -d : d);
    Rational r;
    r.num = n / divisor;
    r.den = d / divisor;
    return r;
}

// devuelve el numerador de un numero racional
int numerator(Rational r) {
    return r.num;
}

// devuelve el denominador del numero racional
int denominator(Rational r) {
    return r.den;
}

// suma dos numeros racionales y devuelve el resultado simplificado
Rational sum(Rational r1, Rational r2) {
    int n = r1.num * r2.den + r2.num * r1.den;
    int d = r1.den * r2.den;
    return createRational(n, d);
}

#endif // STRUCT_MODE
