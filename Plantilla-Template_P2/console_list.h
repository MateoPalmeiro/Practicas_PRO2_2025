/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P1 - Main Program
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 21/03/2025
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
 * createEmptyList: inicializa una lista ordenada vacia.
 * pre: list es un puntero a tList.
 * post: se asigna *list = null.
 */
void createEmptyList(tList *list);

/*
 * isEmptyList: determina si la lista esta vacia.
 * pre: la lista esta inicializada.
 * post: devuelve true si list es null, false en otro caso.
 */
bool isEmptyList(tList list);

/*
 * first: devuelve la primera posicion de la lista.
 * pre: la lista esta inicializada.
 * post: devuelve el primer nodo de la lista.
 */
tPosL first(tList list);

/*
 * last: devuelve la ultima posicion de la lista.
 * pre: la lista no esta vacia.
 * post: devuelve el puntero al ultimo nodo.
 */
tPosL last(tList list);

/*
 * next: devuelve la posicion siguiente a la dada.
 * pre: pos es una posicion valida.
 * post: devuelve pos->next o LNULL si no existe.
 */
tPosL next(tPosL pos, tList list);

/*
 * previous: devuelve la posicion anterior a la dada.
 * pre: pos es una posicion valida y la lista no esta vacia.
 * post: devuelve la posicion anterior o LNULL si pos es el primero.
 */
tPosL previous(tPosL pos, tList list);

/*
 * insertItem: inserta un elemento en la lista de forma ordenada por consoleid.
 * pre: la lista esta inicializada.
 * post: se inserta el elemento en la posicion correspondiente segun el orden alfabetico.
 *       devuelve true si la insercion fue correcta, false en caso contrario.
 * nota: el parametro pos se ignora.
 */
bool insertItem(tItemL item, tList *list);

/*
 * deleteAtPosition: elimina el nodo en la posicion dada.
 * pre: pos es una posicion valida.
 * post: se elimina el nodo y se libera la memoria.
 */
void deleteAtPosition(tPosL pos, tList *list);

/*
 * getItem: devuelve el elemento almacenado en la posicion dada.
 * pre: pos es una posicion valida.
 * post: devuelve el tItemL contenido en pos.
 */
tItemL getItem(tPosL pos, tList list);

/*
 * updateItem: actualiza el elemento en la posicion dada.
 * pre: pos es una posicion valida.
 * post: se reemplaza el elemento en pos con item.
 */
void updateItem(tItemL item, tPosL pos, tList *list);

/*
 * findItem: busca el primer elemento cuyo consoleid coincide con el dado.
 * pre: la lista esta inicializada.
 * post: devuelve la posicion si se encuentra, o LNULL en caso contrario.
 */
tPosL findItem(tConsoleId consoleId, tList list);

#endif