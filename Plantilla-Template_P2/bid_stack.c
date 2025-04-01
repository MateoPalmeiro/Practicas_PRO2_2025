/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P1 - Main Program
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 21/03/2025
*/

#include <stdlib.h>
#include "bid_stack.h"

/*
 * createEmptyStack: inicializa una pila vacia.
 * pre: stack es un puntero a tStack.
 * post: se asigna stack->top = -1.
 */
void createEmptyStack(tStack *stack) {
    stack->top = -1;
}

/*
 * isEmptyStack: determina si la pila esta vacia.
 * pre: la pila esta inicializada.
 * post: devuelve true si stack->top == -1, false en otro caso.
 */
bool isEmptyStack(tStack stack) {
    return (stack.top == -1);
}

/*
 * push: inserta un elemento en la cima de la pila.
 * pre: la pila esta inicializada.
 * post: se inserta el elemento y se incrementa top.
 *       devuelve true si la operacion fue exitosa, false si la pila esta llena.
 */
bool push(tItemS item, tStack *stack) {
    if (stack->top >= BID_STACK_SIZE - 1)
        return false;
    stack->top++;
    stack->items[stack->top] = item;
    return true;
}

/*
 * pop: elimina el elemento en la cima de la pila.
 * pre: la pila no esta vacia.
 * post: se elimina el elemento y se decrementa top.
 */
bool pop(tStack *stack) {
    if (stack->top == -1)
        return false;
    stack->top--;
    return true;
}

/*
 * peek: devuelve el elemento de la cima sin eliminarlo.
 * pre: la pila no esta vacia.
 * post: devuelve el tItemS en la cima.
 */
tItemS peek(tStack stack) {
    return stack.items[stack.top];
}

/*
 * clearStack: vacia la pila de pujas.
 * pre: la pila esta inicializada.
 * post: se establece stack->top = -1.
 */
void clearStack(tStack *stack) {
    stack->top = -1;
}