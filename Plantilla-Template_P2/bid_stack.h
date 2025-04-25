/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P2 - Circular stack implementation
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 24/04/2025
*/

#ifndef BID_STACK_H
#define BID_STACK_H

#include <stdbool.h>
#include "types.h"

#define BID_STACK_SIZE 25  // tamano maximo de la pila de pujas
#define SNULL -1           // posicion nula en la pila


/*
 * Objetivo: Inicializa una pila vacía.
 * Entradas:
 * - stack: tStack*, puntero a la pila que se va a inicializar.
 * Salidas:
 * - Ninguna.
 * Precondiciones:
 * - stack debe ser un puntero válido a tStack.
 * Postcondiciones:
 * - stack->top se asigna a SNULL.
 */

void createEmptyStack(tStack *stack);

/*
 * Objetivo: Determina si la pila está vacía.
 * Entradas:
 * - stack: tStack, pila que se va a verificar.
 * Salidas:
 * - true: si stack->top es SNULL.
 * - false: en caso contrario.
 * Precondiciones:
 * - La pila debe estar inicializada.
 * Postcondiciones:
 * - Ninguna.
 */

bool isEmptyStack(tStack stack);

/*
 * Objetivo: Inserta un elemento en la cima de la pila.
 * Entradas:
 * - item: tItemS, elemento que se va a insertar.
 * - stack: tStack*, puntero a la pila en la que se insertará el elemento.
 * Salidas:
 * - true: si la operación fue exitosa.
 * - false: si la pila está llena.
 * Precondiciones:
 * - La pila debe estar inicializada.
 * Postcondiciones:
 * - Ninguna
 */

bool push(tItemS item, tStack *stack);

/*
 * Objetivo: Elimina el elemento en la cima de la pila.
 * Entradas:
 * - stack: tStack*, puntero a la pila de la cual se eliminará el elemento.
 * Salidas:
 * - true: si la operación fue exitosa.
 * - false: si la pila está vacía.
 * Precondiciones:
 * - La pila no debe estar vacía.
 * Postcondiciones:
 * - Ninguna
 */

bool pop(tStack *stack);

/*
 * Objetivo: Devuelve el elemento de la cima sin eliminarlo.
 * Entradas:
 * - stack: tStack, pila de la cual se obtendrá el elemento en la cima.
 * Salidas:
 * - El elemento (tItemS) en la cima.
 * Precondiciones:
 * - La pila no debe estar vacía.
 * Postcondiciones:
 * - Ninguna.
 */

tItemS peek(tStack stack);

/*
 * Objetivo: Vacía la pila de pujas.
 * Entradas:
 * - stack: tStack*, puntero a la pila que se va a vaciar.
 * Salidas:
 * - Ninguna.
 * Precondiciones:
 * - La pila debe estar inicializada.
 * Postcondiciones:
 * - stack->top se establece a SNULL.
 */

void clearStack(tStack *stack);

#endif
