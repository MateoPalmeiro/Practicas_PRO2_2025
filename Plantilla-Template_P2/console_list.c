/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P2 - Ordered list implementation
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 25/04/2025
*/

#include <stdlib.h>
#include <string.h>
#include "console_list.h"

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

void createEmptyList(tList *list) {
    *list = LNULL;
}


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

bool isEmptyList(tList list) {
    return (list == LNULL);
}


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

tPosL first(tList list) {
    return list;
}

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

tPosL last(tList list) {
    tPosL p = list;
    if (p == LNULL)
        return LNULL;
    while (p->next != LNULL)
        p = p->next;
    return p;
}


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

tPosL next(tPosL pos, tList list) {
    if (pos == LNULL)
        return LNULL;
    return pos->next;
}


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

tPosL previous(tPosL pos, tList list) {
    if (pos == list)
        return LNULL;
    tPosL prev = list;
    while (prev != LNULL && prev->next != pos)
        prev = prev->next;
    return prev;
}


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

bool insertItem(tItemL item, tList *list) {
    tNode *newNode = (tNode *) malloc(sizeof(tNode));
    if (!newNode)
        return false;
    newNode->item = item;
    newNode->next = LNULL;

    // si la lista esta vacia, insertar como primer nodo
    if (*list == LNULL) {
        *list = newNode;
        return true;
    }

    // si el nuevo item debe ir al inicio (orden alfabetico por consoleid)
    if (strcmp(item.consoleId, (*list)->item.consoleId) < 0) {
        newNode->next = *list;
        *list = newNode;
        return true;
    }

    // buscar la posicion de insercion
    tPosL prev = *list;
    while (prev->next != LNULL && strcmp(prev->next->item.consoleId, item.consoleId) < 0) {
        prev = prev->next;
    }

    newNode->next = prev->next;
    prev->next = newNode;

    return true;
}


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

void deleteAtPosition(tPosL pos, tList *list) {
    if (*list == LNULL || pos == LNULL)
        return;
    if (pos == *list) {
        *list = pos->next;
        free(pos);
        return;
    }
    tPosL prev = previous(pos, *list);
    if (prev != LNULL) {
        prev->next = pos->next;
        free(pos);
    }
}


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

tItemL getItem(tPosL pos, tList list) {
    return pos->item;
}


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

void updateItem(tItemL item, tPosL pos, tList *list) {
    if (pos != LNULL)
        pos->item = item;
}


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

tPosL findItem(tConsoleId consoleId, tList list) {
    tPosL p = list;
    while (p != LNULL) {
        if (strcmp(p->item.consoleId, consoleId) == 0)
            return p;
        p = p->next;
    }
    return LNULL;
}
