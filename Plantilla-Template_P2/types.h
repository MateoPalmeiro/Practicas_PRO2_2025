#ifndef TYPES_H
#define TYPES_H

/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P2 - Types
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 24/04/2025
*/

#define NAME_LENGTH_LIMIT 10  // longitud maxima de identificadores
#define BID_STACK_SIZE    25  // tamano maximo de la pila de pujas

typedef char tUserId[NAME_LENGTH_LIMIT];
typedef char tConsoleId[NAME_LENGTH_LIMIT];

typedef enum { nintendo, sega } tConsoleBrand;

typedef float tConsolePrice;
typedef int   tBidCounter;

/*
 * tItemS: estructura que almacena los datos de una puja.
 * Compuesto por:
 *   - bidder: tUserId
 *   - consolePrice: tConsolePrice
 */
typedef struct {
    tUserId       bidder;       // id del pujador
    tConsolePrice consolePrice; // importe de la puja
} tItemS;

/*
 * tStack: pila estatica de pujas.
 * Compuesto por:
 *   - items: array de tItemS de tamano BID_STACK_SIZE
 *   - top: indice del elemento en la cima (-1 si vacia)
 */
typedef struct sStack {
    tItemS items[BID_STACK_SIZE];
    int    top;  // indice de la cima
} tStack;

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
typedef struct {
    tUserId        seller;       // id del vendedor
    tConsoleId     consoleId;    // id de la consola
    tConsoleBrand  consoleBrand; // marca de la consola
    tConsolePrice  consolePrice; // precio original
    tBidCounter    bidCounter;   // numero de pujas recibidas
    tStack         bidStack;     // pila de pujas asociada
} tItemL;

#endif  // TYPES_H
