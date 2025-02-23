/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P1 - Types Library
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 21/03/2025
*/

#ifndef PRO2_2024_P1_TYPES_H
#define PRO2_2024_P1_TYPES_H

#define NAME_LENGTH_LIMIT 10    // define la longitud maxima de los identificadores (userId y consoleId)

// se define el tipo tUserId como un array de char de longitud NAME_LENGTH_LIMIT
typedef char tUserId[NAME_LENGTH_LIMIT];

// se define el tipo tConsoleId como un array de char de longitud NAME_LENGTH_LIMIT
typedef char tConsoleId[NAME_LENGTH_LIMIT];

// se define el tipo enumerado tConsoleBrand para representar la marca de la consola
// los posibles valores son: nintendo y sega
typedef enum { nintendo, sega } tConsoleBrand;

// se define el tipo tConsolePrice como float, para representar el precio de la consola
typedef float tConsolePrice;

// se define el tipo tBidCounter como int, para contar el numero de pujas recibidas
typedef int tBidCounter;

// se define la estructura tItemL que representa los datos de un elemento (una consola)
// esta estructura almacena el vendedor, el identificador de la consola, la marca, el precio y el contador de pujas
typedef struct tItemL {
    tUserId seller;             // identificador del vendedor (cadena de caracteres)
    tConsoleId consoleId;       // identificador de la consola (cadena de caracteres)
    tConsoleBrand consoleBrand; // marca de la consola (nintendo o sega)
    tConsolePrice consolePrice; // precio de la consola (valor float)
    tBidCounter bidCounter;     // contador de pujas (valor entero)
} tItemL;

#endif  // PRO2_2024_P1_TYPES_H
