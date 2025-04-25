/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P2 - Circular stack implementation
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 04/04/2025
*/

#ifndef BID_STACK_H
#define BID_STACK_H

#include <stdbool.h>
#include "types.h"

#define BID_STACK_SIZE 25  // tamano maximo de la pila de pujas
#define SNULL -1           // posicion nula en la pila

/*
 * createEmptyStack: inicializa una pila vacia.
 * pre: stack es un puntero a tStack.
 * post: se asigna stack->top = SNULL.
 * variables:
 *   - stack: tStack*, puntero a la pila que se va a inicializar.
 */
void createEmptyStack(tStack *stack);

/*
 * isEmptyStack: determina si la pila esta vacia.
 * pre: la pila esta inicializada.
 * post: devuelve true si stack->top == SNULL, false en otro caso.
 * variables:
 *   - stack: tStack, pila que se va a verificar.
 */
bool isEmptyStack(tStack stack);

/*
 * push: inserta un elemento en la cima de la pila.
 * pre: la pila esta inicializada.
 * post: se inserta el elemento en la cima y se actualiza top.
 *       devuelve true si la operacion fue exitosa, false en caso contrario.
 * variables:
 *   - item: tItemS, elemento que se va a insertar.
 *   - stack: tStack*, puntero a la pila en la que se insertara el elemento.
 */
bool push(tItemS item, tStack *stack);

/*
 * pop: elimina el elemento en la cima de la pila.
 * pre: la pila no esta vacia.
 * post: se elimina el elemento y se actualiza top.
 * variables:
 *   - stack: tStack*, puntero a la pila de la cual se eliminara el elemento.
 */
bool pop(tStack *stack);

/*
 * peek: devuelve el elemento de la cima sin eliminarlo.
 * pre: la pila no esta vacia.
 * post: devuelve el tItemS en la cima.
 * variables:
 *   - stack: tStack, pila de la cual se obtendra el elemento en la cima.
 */
tItemS peek(tStack stack);

/*
 * clearStack: vacia la pila de pujas.
 * pre: la pila esta inicializada.
 * post: se establece top = SNULL.
 * variables:
 *   - stack: tStack*, puntero a la pila que se va a vaciar.
 */
void clearStack(tStack *stack);

#endif
