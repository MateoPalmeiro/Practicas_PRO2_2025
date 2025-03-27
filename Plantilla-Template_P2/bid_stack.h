#ifndef BID_STACK_H
#define BID_STACK_H

#include <stdbool.h>
#include "types.h"

#define BID_STACK_SIZE 25  // tamano maximo de la pila de pujas
#define SNULL -1           // posicion nula en la pila

/*
 * titems: estructura que almacena los datos de una puja.
 * contiene bidder y consoleprice.
 */
typedef struct {
    tUserId bidder;
    tConsolePrice consolePrice;
} tItemS;

/*
 * sstack: estructura que representa una pila de pujas.
 * items: array de tItemS.
 * top: indice del elemento en la cima de la pila (-1 si esta vacia).
 */
struct sStack {
    tItemS items[BID_STACK_SIZE];
    int top;
};

/*
 * createEmptyStack: inicializa una pila vacia.
 * pre: stack es un puntero a tStack.
 * post: se asigna stack->top = -1.
 */
void createEmptyStack(tStack *stack);

/*
 * isEmptyStack: determina si la pila esta vacia.
 * pre: la pila esta inicializada.
 * post: devuelve true si stack->top == -1, false en otro caso.
 */
bool isEmptyStack(tStack stack);

/*
 * push: inserta un elemento en la cima de la pila.
 * pre: la pila esta inicializada.
 * post: se inserta el elemento en la cima y se actualiza top.
 *       devuelve true si la operacion fue exitosa, false en caso contrario.
 */
bool push(tItemS item, tStack *stack);

/*
 * pop: elimina el elemento en la cima de la pila.
 * pre: la pila no esta vacia.
 * post: se elimina el elemento y se actualiza top.
 */
bool pop(tStack *stack);

/*
 * peek: devuelve el elemento de la cima sin eliminarlo.
 * pre: la pila no esta vacia.
 * post: devuelve el tItemS en la cima.
 */
tItemS peek(tStack stack);

/*
 * clearStack: vacia la pila de pujas.
 * pre: la pila esta inicializada.
 * post: se establece top = -1.
 */
void clearStack(tStack *stack);

#endif
