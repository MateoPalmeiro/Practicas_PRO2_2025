/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P1 - Dynamic List Implementation
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 1.2    DATE: 21/03/2025
*/

#include "dynamic_list.h"  // se incluye la interfaz de la lista dinamica
#include <stdlib.h>        // se incluye para usar malloc y free
#include <string.h>        // se incluye para usar funciones de manejo de cadenas (si es necesario)

/*
 * createEmptyList: inicializa una lista dinamica vacia.
 * pre: list es un puntero a tList.
 * post: se asigna *list = NULL.
 */
void createEmptyList(tList *list) {
    *list = NULL;  // se asigna null a la lista para indicar que esta vacia
}

/*
 * isEmptyList: determina si la lista dinamica esta vacia.
 * pre: la lista esta inicializada.
 * post: devuelve true si *list es NULL, false en otro caso.
 */
bool isEmptyList(tList list) {
    return (list == NULL);
}

/*
 * first: devuelve el primer nodo de la lista.
 * pre: la lista no esta vacia.
 * post: devuelve list.
 */
tPosL first(tList list) {
    return list;  // el primer nodo es el inicio de la lista
}

/*
 * last: devuelve el ultimo nodo de la lista.
 * pre: la lista no esta vacia.
 * post: devuelve el puntero al ultimo nodo.
 */
tPosL last(tList list) {
    tPosL p = list;
    if (p == NULL)
        return NULL;  // si la lista es vacia, se retorna null
    // se recorre la lista hasta el ultimo nodo (donde p->next es null)
    while (p->next != NULL) {
        p = p->next;
    }
    return p;  // se retorna el ultimo nodo
}

/*
 * next: devuelve el nodo siguiente al nodo dado.
 * pre: pos es un nodo valido.
 * post: devuelve pos->next o LNULL si no existe.
 */
tPosL next(tPosL pos, tList list) {
    if (pos == NULL)
        return NULL;  // si pos es null, se retorna null
    return pos->next;  // se retorna el siguiente nodo
}

/*
 * previous: devuelve el nodo anterior al nodo dado.
 * pre: pos es un nodo valido y la lista no esta vacia.
 * post: devuelve el nodo anterior o LNULL si pos es el primero.
 */
tPosL previous(tPosL pos, tList list) {
    if (pos == list)
        return NULL;  // si pos es el primer nodo, no hay anterior
    tPosL prev = list;
    // se recorre la lista hasta encontrar el nodo cuyo siguiente es pos
    while (prev != NULL && prev->next != pos) {
        prev = prev->next;
    }
    return prev;  // se retorna el nodo anterior, o null si no se encontro
}

/*
 * insertItem: inserta un elemento en la lista antes del nodo dado.
 *           si pos es LNULL, inserta al final.
 * pre: la lista esta inicializada y pos es valida o LNULL.
 * post: se asigna memoria para el nuevo nodo y se inserta.
 *       devuelve true si la insercion fue exitosa, false en caso de fallo.
 */
bool insertItem(tItemL item, tPosL pos, tList *list) {
    tNode *newNode = (tNode*) malloc(sizeof(tNode));
    if (!newNode)
        return false;  // si malloc falla, se retorna false
    newNode->item = item;  // se asigna el elemento al nuevo nodo
    newNode->next = NULL;  // se inicializa el puntero next a null

    if (*list == NULL) {
        /* lista vacia: insertar como primer nodo */
        *list = newNode;
        return true;
    }

    if (pos == NULL) {
        /* insertar al final */
        tPosL lastNode = last(*list);
        lastNode->next = newNode;
        return true;
    }

    if (pos == *list) {
        /* insertar al principio */
        newNode->next = *list;
        *list = newNode;
        return true;
    }

    /* insertar antes de pos: buscar el nodo anterior */
    tPosL prev = previous(pos, *list);
    if (prev == NULL)
        return false;  // si no se encuentra el nodo anterior, se retorna false
    newNode->next = pos;
    prev->next = newNode;
    return true;
}

/*
 * deleteAtPosition: elimina el nodo en la posicion dada.
 * pre: pos es un nodo valido.
 * post: se elimina el nodo y se libera la memoria correspondiente.
 */
void deleteAtPosition(tPosL pos, tList *list) {
    if (*list == NULL || pos == NULL)
        return;  // si la lista esta vacia o pos es null, no se hace nada
    if (pos == *list) {
        *list = pos->next;
        free(pos);  // se libera la memoria del primer nodo
        return;
    }
    tPosL prev = previous(pos, *list);
    if (prev != NULL) {
        prev->next = pos->next;
        free(pos);  // se libera la memoria del nodo eliminado
    }
}

/*
 * getItem: devuelve el elemento almacenado en el nodo dado.
 * pre: pos es un nodo valido.
 * post: devuelve el elemento contenido en pos.
 */
tItemL getItem(tPosL pos, tList list) {
    return pos->item;  // se retorna el elemento almacenado en el nodo
}

/*
 * updateItem: actualiza el elemento en el nodo dado.
 * pre: pos es un nodo valido.
 * post: se reemplaza el elemento en pos con el nuevo valor.
 */
void updateItem(tItemL item, tPosL pos, tList *list) {
    if (pos != NULL) {
        pos->item = item;  // se actualiza el elemento en el nodo
    }
}

/*
 * findItem: busca el primer nodo cuyo consoleId coincide con el dado.
 * pre: la lista esta inicializada.
 * post: devuelve el puntero al nodo si se encuentra, o LNULL si no existe.
 */
tPosL findItem(tConsoleId consoleId, tList list) {
    tPosL p = list;
    // se recorre la lista comparando consoleId
    while (p != NULL) {
        if (strcmp(p->item.consoleId, consoleId) == 0)
            return p;  // se retorna el nodo si se encuentra coincidencia
        p = p->next;
    }
    return NULL;  // si no se encuentra, se retorna NULL
}
