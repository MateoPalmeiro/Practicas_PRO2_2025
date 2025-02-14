/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P0 (rational_pointer)
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3 DATE: 04/02/2025
*/

#ifndef RATIONAL_POINTER_H
#define RATIONAL_POINTER_H

// definicion del tipo rational usando punteros
typedef struct Rational {
    int num;  // numerador
    int den;  // denominador
} Rational;

// crea un numero racional a partir de un numerador n y un denominador d
// reserva memoria dinamica y devuelve un puntero al numero racional
Rational* createRational(int n, int d);

// devuelve el numerador de un numero racional
int numerator(Rational* r);

// devuelve el denominador de un numero racional
int denominator(Rational* r);

// suma dos numeros racionales y devuelve un puntero al resultado simplificado
Rational* sum(Rational* r1, Rational* r2);

#endif // RATIONAL_POINTER_H