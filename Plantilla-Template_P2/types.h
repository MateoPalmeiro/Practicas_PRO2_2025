#ifndef TYPES_H
#define TYPES_H

#define NAME_LENGTH_LIMIT 10  // longitud maxima de identificadores

typedef char tUserId[NAME_LENGTH_LIMIT];
typedef char tConsoleId[NAME_LENGTH_LIMIT];

typedef enum { nintendo, sega } tConsoleBrand;

typedef float tConsolePrice;
typedef int tBidCounter;

// declaracion adelantada de la pila de pujas
typedef struct sStack tStack;

/*
 * titeml: estructura que almacena los datos de una consola.
 * contiene seller, consoleid, consolebrand, consoleprice, bidcounter
 * y la pila de pujas bidstack.
 */
typedef struct tItemL {
    tUserId seller;
    tConsoleId consoleId;
    tConsoleBrand consoleBrand;
    tConsolePrice consolePrice;
    tBidCounter bidCounter;
    tStack bidStack;  // pila de pujas asociada a la consola
} tItemL;

#endif
