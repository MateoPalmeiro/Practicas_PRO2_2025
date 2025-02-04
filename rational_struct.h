/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P0 (rational_struct)
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2:
GROUP: 1.2 DATE: 04/02/2025
*/

#ifndef RATIONAL_STRUCT_H
#define RATIONAL_STRUCT_H

// definicion del tipo rational usando estructura
typedef struct {
    int num;  // numerador
    int den;  // denominador
} Rational;

// crea un numero racional a partir de un numerador n y un denominador d
Rational createRational(int n, int d);

// devuelve el numerador de un numero racional
int numerator(Rational r);

// devuelve el denominador de un numero racional
int denominator(Rational r);

// suma dos numeros racionales y devuelve el resultado
Rational sum(Rational r1, Rational r2);

#endif // RATIONAL_STRUCT_H
