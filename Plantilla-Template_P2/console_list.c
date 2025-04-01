/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P1 - Main Program
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 21/03/2025
*/

#include <stdlib.h>
#include <string.h>
#include "console_list.h"

/*
 * createEmptyList: inicializa una lista ordenada vacia.
 * pre: list es un puntero a tList.
 * post: se asigna *list = null.
 */
void createEmptyList(tList *list) {
    *list = NULL;
}

/*
 * isEmptyList: determina si la lista esta vacia.
 * pre: la lista esta inicializada.
 * post: devuelve true si list es null, false en otro caso.
 */
bool isEmptyList(tList list) {
    return (list == NULL);
}

/*
 * first: devuelve la primera posicion de la lista.
 * pre: la lista esta inicializada.
 * post: devuelve el primer nodo.
 */
tPosL first(tList list) {
    return list;
}

/*
 * last: devuelve la ultima posicion de la lista.
 * pre: la lista no esta vacia.
 * post: devuelve el puntero al ultimo nodo.
 */
tPosL last(tList list) {
    tPosL p = list;
    if (p == NULL)
        return NULL;
    while (p->next != NULL)
        p = p->next;
    return p;
}

/*
 * next: devuelve la posicion siguiente a la dada.
 * pre: pos es una posicion valida.
 * post: devuelve pos->next o LNULL si no existe.
 */
tPosL next(tPosL pos, tList list) {
    if (pos == NULL)
        return NULL;
    return pos->next;
}

/*
 * previous: devuelve la posicion anterior a la dada.
 * pre: pos es una posicion valida y la lista no esta vacia.
 * post: devuelve la posicion anterior o LNULL si pos es el primero.
 */
tPosL previous(tPosL pos, tList list) {
    if (pos == list)
        return NULL;
    tPosL prev = list;
    while (prev != NULL && prev->next != pos)
        prev = prev->next;
    return prev;
}

/*
 * insertItem: inserta un elemento en la lista de forma ordenada por consoleid.
 * pre: la lista esta inicializada.
 * post: se inserta el elemento en la posicion correcta segun el orden alfabetico.
 *       devuelve true si la insercion fue exitosa, false en caso contrario.
 */
bool insertItem(tItemL item, tList *list) {
    tNode *newNode = (tNode *) malloc(sizeof(tNode));
    if (!newNode)
        return false;
    newNode->item = item;
    newNode->next = NULL;

    // si la lista esta vacia, insertar como primer nodo
    if (*list == NULL) {
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
    while (prev->next != NULL && strcmp(prev->next->item.consoleId, item.consoleId) < 0) {
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
 */
void deleteAtPosition(tPosL pos, tList *list) {
    if (*list == NULL || pos == NULL)
        return;
    if (pos == *list) {
        *list = pos->next;
        free(pos);
        return;
    }
    tPosL prev = previous(pos, *list);
    if (prev != NULL) {
        prev->next = pos->next;
        free(pos);
    }
}

/*
 * getItem: devuelve el elemento almacenado en la posicion dada.
 * pre: pos es una posicion valida.
 * post: devuelve el tItemL contenido en pos.
 */
tItemL getItem(tPosL pos, tList list) {
    return pos->item;
}

/*
 * updateItem: actualiza el elemento en la posicion dada.
 * pre: pos es una posicion valida.
 * post: se reemplaza el item en pos por el nuevo item.
 */
void updateItem(tItemL item, tPosL pos, tList *list) {
    if (pos != NULL)
        pos->item = item;
}

/*
 * findItem: busca el primer elemento cuyo consoleid coincide con el dado.
 * pre: la lista esta inicializada.
 * post: devuelve la posicion si se encuentra, o LNULL en caso contrario.
 */
tPosL findItem(tConsoleId consoleId, tList list) {
    tPosL p = list;
    while (p != NULL) {
        if (strcmp(p->item.consoleId, consoleId) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}