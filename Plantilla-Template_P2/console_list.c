/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P2 - Ordered list implementation
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 24/04/2025
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
 * Objetivo: Inserta un elemento en la lista ordenada por consoleId,
 *           rechazando duplicados.
 * Entradas:
 *   - item: tItemL, datos de la consola a insertar.
 *   - list: tList*, puntero a la lista ordenada.
 * Salidas:
 *   - true si la inserción fue exitosa.
 *   - false si ya existía esa consola o falla malloc.
 * Precondiciones:
 *   - *list está inicializada (puede valer LNULL).
 * Postcondiciones:
 *   - Si retorna true, el nodo se añade en posición alfabética.
 *   - Si retorna false, la lista no cambia.
 */
bool insertItem(tItemL item, tList *list) {
    // No permitimos duplicados
    for (tPosL p = *list; p != LNULL; p = p->next) {
        if (strcmp(p->item.consoleId, item.consoleId) == 0)
            return false;
    }

    tNode *newNode = malloc(sizeof(tNode));
    if (!newNode) return false;

    newNode->item = item;
    newNode->next = LNULL;

    // Caso lista vacía o insertar al frente
    if (*list == LNULL ||
        strcmp(item.consoleId, (*list)->item.consoleId) < 0) {
        newNode->next = *list;
        *list = newNode;
        return true;
    }

    // Busca el nodo tras el cual insertar
    tPosL prev = *list;
    while (prev->next != LNULL &&
           strcmp(prev->next->item.consoleId, item.consoleId) < 0) {
        prev = prev->next;
    }

    // Inserción en medio o al final
    newNode->next = prev->next;
    prev->next    = newNode;
    return true;
}

/*
 * Objetivo: Elimina el nodo en la posición indicada.
 * Entradas:
 *   - pos:  tPosL, posición del nodo a eliminar.
 *   - list: tList*, puntero a la lista.
 * Salidas:
 *   - Ninguna.
 * Precondiciones:
 *   - pos es una posición válida en *list.
 * Postcondiciones:
 *   - El nodo se libera y la lista se reencadena sin él.
 */
void deleteAtPosition(tPosL pos, tList *list) {
    if (*list == LNULL || pos == LNULL) return;

    // Eliminar la cabeza
    if (pos == *list) {
        *list = pos->next;
        free(pos);
        return;
    }

    // Buscar el anterior y ajustar enlaces
    tPosL prev = previous(pos, *list);
    if (prev != LNULL) {
        prev->next = pos->next;
        free(pos);
    }
}

/*
 * Objetivo: Sustituye el contenido del nodo en pos por item.
 * Entradas:
 *   - item: tItemL, nuevo valor completo a asignar.
 *   - pos:  tPosL, posición del nodo a actualizar.
 *   - list: tList*, puntero a la lista (no usado).
 * Salidas:
 *   - Ninguna.
 * Precondiciones:
 *   - pos es una posición válida en *list.
 * Postcondiciones:
 *   - pos->item queda reemplazado por item.
 */
void updateItem(tItemL item, tPosL pos, tList *list) {
    (void) list;  // parámetro no usado
    if (pos == LNULL) return;
    pos->item = item;
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
* Objetivo: Busca el primer elemento cuyo consoleId coincide con el dado.
* Entradas:
* - consoleId: const char*, identificador que se buscará en la lista.
* - list: tList, lista en la que se buscará el elemento.
* Salidas:
* - La posición del elemento si se encuentra.
* - LNULL: en caso contrario.
* Precondiciones:
* - La lista debe estar inicializada.
* Postcondiciones:
* - Ninguna.
*/
tPosL findItem(const char *consoleId, tList list) {
    tPosL p = list;
    while (p != LNULL) {
        if (strcmp(p->item.consoleId, consoleId) == 0)
            return p;
        p = p->next;
    }
    return LNULL;
}
