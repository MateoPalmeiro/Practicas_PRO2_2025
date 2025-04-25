/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P2 - Circular stack implementation
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 24/04/2025
*/

#include <stdlib.h>
#include "bid_stack.h"

/*
 * createEmptyStack: inicializa una pila vacia.
 * pre: stack es un puntero a tStack.
 * post: se asigna stack->top = SNULL.
 * variables:
 *   - stack: tStack*, puntero a la pila que se va a inicializar.
 */
void createEmptyStack(tStack *stack) {
    stack->top = SNULL;
}

/*
 * isEmptyStack: determina si la pila esta vacia.
 * pre: la pila esta inicializada.
 * post: devuelve true si stack->top == SNULL, false en otro caso.
 * variables:
 *   - stack: tStack, pila que se va a verificar.
 */
bool isEmptyStack(tStack stack) {
    return (stack.top == SNULL);
}

/*
 * push: inserta un elemento en la cima de la pila.
 * pre: la pila esta inicializada.
 * post: se inserta el elemento y se incrementa top.
 *       devuelve true si la operacion fue exitosa, false si la pila esta llena.
 * variables:
 *   - item: tItemS, elemento que se va a insertar.
 *   - stack: tStack*, puntero a la pila en la que se insertara el elemento.
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
 * variables:
 *   - stack: tStack*, puntero a la pila de la cual se eliminara el elemento.
 */
bool pop(tStack *stack) {
    if (stack->top == SNULL)
        return false;
    stack->top--;
    return true;
}

/*
 * peek: devuelve el elemento de la cima sin eliminarlo.
 * pre: la pila no esta vacia.
 * post: devuelve el tItemS en la cima.
 * variables:
 *   - stack: tStack, pila de la cual se obtendra el elemento en la cima.
 */
tItemS peek(tStack stack) {
    return stack.items[stack.top];
}

/*
 * clearStack: vacia la pila de pujas.
 * pre: la pila esta inicializada.
 * post: se establece stack->top = SNULL.
 * variables:
 *   - stack: tStack*, puntero a la pila que se va a vaciar.
 */
void clearStack(tStack *stack) {
    stack->top = SNULL;
}
