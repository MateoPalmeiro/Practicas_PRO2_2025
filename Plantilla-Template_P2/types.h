#ifndef TYPES_H
#define TYPES_H


#define NAME_LENGTH_LIMIT 10  // longitud máxima de identificadores

typedef char tUserId[NAME_LENGTH_LIMIT];
typedef char tConsoleId[NAME_LENGTH_LIMIT];

typedef enum { nintendo, sega } tConsoleBrand;

typedef float tConsolePrice;
typedef int tBidCounter;

typedef struct sStack tStack;

/*
 * tItemL: estructura que almacena los datos de una consola.
 * Compuesto por:
 *   - seller: tUserId
 *   - consoleId: tConsoleId
 *   - consoleBrand: tConsoleBrand
 *   - consolePrice: tConsolePrice
 *   - bidCounter: tBidCounter
 *   - bidStack: tStack (pila de pujas asociada a la consola)
 */
typedef struct tItemL {
    tUserId seller;
    tConsoleId consoleId;
    tConsoleBrand consoleBrand;
    tConsolePrice consolePrice;
    tBidCounter bidCounter;
    tStack *bidStack;
} tItemL;

#endif

