/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P2 - Ordered list implementation
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 25/04/2025
*/

#ifndef CONSOLE_LIST_H
#define CONSOLE_LIST_H

#include <stdbool.h>
#include "types.h"

#define LNULL NULL  // se utiliza null para indicar posicion nula

// estructura de nodo de la lista ordenada de consolas
typedef struct sNode {
    tItemL item;
    struct sNode *next;
} tNode;

// la lista se representa como un puntero al primer nodo
typedef tNode* tList;
// la posicion en la lista es un puntero al nodo
typedef tNode* tPosL;

/*
* Objetivo: Inicializa una lista ordenada vacía.
 * Entradas:
 * - list: tList*, puntero a la lista que se va a inicializar.
 * Salidas:
 * - Ninguna.
 * Precondiciones:
 * - list debe ser un puntero válido a tList.
 * Postcondiciones:
 * - Queda una lista vacía
 */
void createEmptyList(tList *list);

/*
 * Objetivo: Determina si la lista está vacía.
 * Entradas:
 * - list: tList, lista que se va a verificar.
 * Salidas:
 * - true: si la lista está vacía.
 * - false: si la lista no está vacía.
 * Precondiciones:
 * - La lista debe estar inicializada.
 * Postcondiciones:
 * - Ninguna.
 */
bool isEmptyList(tList list);

/*
 * Objetivo: Devuelve la primera posición de la lista.
 * Entradas:
 * - list: tList, lista de la cual se obtendrá la primera posición.
 * Salidas:
 * - El primer nodo de la lista.
 * Precondiciones:
 * - La lista debe estar inicializada.
 * Postcondiciones:
 * - Ninguna.
 */
tPosL first(tList list);

/*
 * Objetivo: Devuelve la última posición de la lista.
 * Entradas:
 * - list: tList, lista de la cual se obtendrá la última posición.
 * Salidas:
 * - El último nodo de la lista
 * Precondiciones:
 * - La lista no debe estar vacía.
 * Postcondiciones:
 * - Ninguna.
 */
tPosL last(tList list);

/*
 * Objetivo: Devuelve la posición siguiente a la dada.
 * Entradas:
 * - pos: tPosL, posición actual en la lista.
 * - list: tList, lista en la que se encuentra la posición.
 * Salidas:
 * - pos->next: la posición siguiente.
 * - LNULL: si no existe una posición siguiente.
 * Precondiciones:
 * - pos debe ser una posición válida.
 * Postcondiciones:
 * - Ninguna.
 */
tPosL next(tPosL pos, tList list);

/*
 * Objetivo: Devuelve la posición anterior a la dada.
 * Entradas:
 * - pos: tPosL, posición actual en la lista.
 * - list: tList, lista en la que se encuentra la posición.
 * Salidas:
 * - La posición anterior a pos.
 * - LNULL: si pos es la primera posición de la lista.
 * Precondiciones:
 * - pos debe ser una posición válida.
 * - La lista no debe estar vacía.
 * Postcondiciones:
 * - Ninguna.
 */
tPosL previous(tPosL pos, tList list);

/*
 * Objetivo: Inserta un elemento en la lista de forma ordenada por consoleId.
 * Entradas:
 * - item: tItemL, elemento que se va a insertar.
 * - list: tList*, puntero a la lista en la que se insertará el elemento.
 * Salidas:
 * - true: si la inserción fue exitosa.
 * - false: en caso contrario.
 * Precondiciones:
 * - La lista debe estar inicializada.
 * Postcondiciones:
 * - Las posiciones posteriores cambian de posición
 */
bool insertItem(tItemL item, tList *list);

/*
 * Objetivo: Elimina el nodo en la posición dada.
 * Entradas:
 * - pos: tPosL, posición del nodo que se va a eliminar.
 * - list: tList*, puntero a la lista de la cual se eliminará el nodo.
 * Salidas:
 * - Ninguna.
 * Precondiciones:
 * - pos debe ser una posición válida.
 * Postcondiciones:
 * - Las posiciones posteriores cambian de posición
 */
void deleteAtPosition(tPosL pos, tList *list);

/*
 * Objetivo: Devuelve el elemento almacenado en la posición dada.
 * Entradas:
 * - pos: tPosL, posición del elemento que se va a obtener.
 * - list: tList, lista en la que se encuentra el elemento.
 * Salidas:
 * - El elemento (tItemL) contenido en pos.
 * Precondiciones:
 * - pos debe ser una posición válida.
 * Postcondiciones:
 * - Ninguna.
 */
tItemL getItem(tPosL pos, tList list);

/*
 * Objetivo: Actualiza el elemento en la posición dada.
 * Entradas:
 * - item: tItemL, nuevo valor que se asignará al elemento.
 * - pos: tPosL, posición del elemento que se va a actualizar.
 * - list: tList*, puntero a la lista en la que se encuentra el elemento.
 * Salidas:
 * - Ninguna.
 * Precondiciones:
 * - pos debe ser una posición válida.
 * Postcondiciones:
 * - Ninguna.
 */
void updateItem(tItemL item, tPosL pos, tList *list);

/*
 * Objetivo: Busca el primer elemento cuyo consoleId coincide con el dado.
 * Entradas:
 * - consoleId: tConsoleId, identificador que se buscará en la lista.
 * - list: tList, lista en la que se buscará el elemento.
 * Salidas:
 * - La posición del elemento si se encuentra.
 * - LNULL: en caso contrario.
 * Precondiciones:
 * - La lista debe estar inicializada.
 * Postcondiciones:
 * - Ninguna.
 */
tPosL findItem(tConsoleId consoleId, tList list);

#endif
