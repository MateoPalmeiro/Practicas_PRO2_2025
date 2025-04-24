/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P2 - Ordered list implementation
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 04/04/2025
*/

#include <stdlib.h>
#include <string.h>
#include "console_list.h"

/*
 * createEmptyList: inicializa una lista ordenada vacia.
 * pre: list es un puntero a tList.
 * post: se asigna *list = null.
 * variables:
 *   - list: tList*, puntero a la lista que se va a inicializar.
 */
void createEmptyList(tList *list) {
    *list = LNULL;
}

/*
 * isEmptyList: determina si la lista esta vacia.
 * pre: la lista esta inicializada.
 * post: devuelve true si list es null, false en otro caso.
 * variables:
 *   - list: tList, lista que se va a verificar.
 */
bool isEmptyList(tList list) {
    return (list == LNULL);
}

/*
 * first: devuelve la primera posicion de la lista.
 * pre: la lista esta inicializada.
 * post: devuelve el primer nodo.
 * variables:
 *   - list: tList, lista de la cual se obtendra la primera posicion.
 */
tPosL first(tList list) {
    return list;
}

/*
 * last: devuelve la ultima posicion de la lista.
 * pre: la lista no esta vacia.
 * post: devuelve el puntero al ultimo nodo.
 * variables:
 *   - list: tList, lista de la cual se obtendra la ultima posicion.
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
 * next: devuelve la posicion siguiente a la dada.
 * pre: pos es una posicion valida.
 * post: devuelve pos->next o LNULL si no existe.
 * variables:
 *   - pos: tPosL, posicion actual en la lista.
 *   - list: tList, lista en la que se encuentra la posicion.
 */
tPosL next(tPosL pos, tList list) {
    if (pos == LNULL)
        return LNULL;
    return pos->next;
}

/*
 * previous: devuelve la posicion anterior a la dada.
 * pre: pos es una posicion valida y la lista no esta vacia.
 * post: devuelve la posicion anterior o LNULL si pos es el primero.
 * variables:
 *   - pos: tPosL, posicion actual en la lista.
 *   - list: tList, lista en la que se encuentra la posicion.
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
 * insertItem: inserta un elemento en la lista de forma ordenada por consoleid.
 * pre: la lista esta inicializada.
 * post: se inserta el elemento en la posicion correcta segun el orden alfabetico.
 *       devuelve true si la insercion fue exitosa, false en caso contrario.
 * variables:
 *   - item: tItemL, elemento que se va a insertar.
 *   - list: tList*, puntero a la lista en la que se insertara el elemento.
 *   - newNode: tNode*, nuevo nodo que se insertara en la lista.
 *   - prev: tPosL, posicion anterior en la lista.
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
 * deleteAtPosition: elimina el nodo en la posicion dada.
 * pre: pos es una posicion valida.
 * post: se elimina el nodo y se libera la memoria.
 * variables:
 *   - pos: tPosL, posicion del nodo que se va a eliminar.
 *   - list: tList*, puntero a la lista de la cual se eliminara el nodo.
 *   - prev: tPosL, posicion anterior en la lista.
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
 * getItem: devuelve el elemento almacenado en la posicion dada.
 * pre: pos es una posicion valida.
 * post: devuelve el tItemL contenido en pos.
 * variables:
 *   - pos: tPosL, posicion del elemento que se va a obtener.
 *   - list: tList, lista en la que se encuentra el elemento.
 */
tItemL getItem(tPosL pos, tList list) {
    return pos->item;
}

/*
 * updateItem: actualiza el elemento en la posicion dada.
 * pre: pos es una posicion valida.
 * post: se reemplaza el item en pos por el nuevo item.
 * variables:
 *   - item: tItemL, nuevo valor que se asignara al elemento.
 *   - pos: tPosL, posicion del elemento que se va a actualizar.
 *   - list: tList*, puntero a la lista en la que se encuentra el elemento.
 */
void updateItem(tItemL item, tPosL pos, tList *list) {
    if (pos != LNULL)
        pos->item = item;
}

/*
 * findItem: busca el primer elemento cuyo consoleid coincide con el dado.
 * pre: la lista esta inicializada.
 * post: devuelve la posicion si se encuentra, o LNULL en caso contrario.
 * variables:
 *   - consoleId: tConsoleId, identificador que se buscara en la lista.
 *   - list: tList, lista en la que se buscara el elemento.
 *   - p: tPosL, posicion temporal para recorrer la lista.
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
