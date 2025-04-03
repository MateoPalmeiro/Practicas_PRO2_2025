/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P2 - Ordered list implementation
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 04/04/2025
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
 * variables:
 *   - list: tList*, puntero a la lista que se va a inicializar.
 */
void createEmptyList(tList *list);

/*
 * isEmptyList: determina si la lista esta vacia.
 * pre: la lista esta inicializada.
 * post: devuelve true si list es null, false en otro caso.
 * variables:
 *   - list: tList, lista que se va a verificar.
 */
bool isEmptyList(tList list);

/*
 * first: devuelve la primera posicion de la lista.
 * pre: la lista esta inicializada.
 * post: devuelve el primer nodo.
 * variables:
 *   - list: tList, lista de la cual se obtendra la primera posicion.
 */
tPosL first(tList list);

/*
 * last: devuelve la ultima posicion de la lista.
 * pre: la lista no esta vacia.
 * post: devuelve el puntero al ultimo nodo.
 * variables:
 *   - list: tList, lista de la cual se obtendra la ultima posicion.
 */
tPosL last(tList list);

/*
 * next: devuelve la posicion siguiente a la dada.
 * pre: pos es una posicion valida.
 * post: devuelve pos->next o LNULL si no existe.
 * variables:
 *   - pos: tPosL, posicion actual en la lista.
 *   - list: tList, lista en la que se encuentra la posicion.
 */
tPosL next(tPosL pos, tList list);

/*
 * previous: devuelve la posicion anterior a la dada.
 * pre: pos es una posicion valida y la lista no esta vacia.
 * post: devuelve la posicion anterior o LNULL si pos es el primero.
 * variables:
 *   - pos: tPosL, posicion actual en la lista.
 *   - list: tList, lista en la que se encuentra la posicion.
 */
tPosL previous(tPosL pos, tList list);

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
bool insertItem(tItemL item, tList *list);

/*
 * deleteAtPosition: elimina el nodo en la posicion dada.
 * pre: pos es una posicion valida.
 * post: se elimina el nodo y se libera la memoria.
 * variables:
 *   - pos: tPosL, posicion del nodo que se va a eliminar.
 *   - list: tList*, puntero a la lista de la cual se eliminara el nodo.
 *   - prev: tPosL, posicion anterior en la lista.
 */
void deleteAtPosition(tPosL pos, tList *list);

/*
 * getItem: devuelve el elemento almacenado en la posicion dada.
 * pre: pos es una posicion valida.
 * post: devuelve el tItemL contenido en pos.
 * variables:
 *   - pos: tPosL, posicion del elemento que se va a obtener.
 *   - list: tList, lista en la que se encuentra el elemento.
 */
tItemL getItem(tPosL pos, tList list);

/*
 * updateItem: actualiza el elemento en la posicion dada.
 * pre: pos es una posicion valida.
 * post: se reemplaza el item en pos por el nuevo item.
 * variables:
 *   - item: tItemL, nuevo valor que se asignara al elemento.
 *   - pos: tPosL, posicion del elemento que se va a actualizar.
 *   - list: tList*, puntero a la lista en la que se encuentra el elemento.
 */
void updateItem(tItemL item, tPosL pos, tList *list);

/*
 * findItem: busca el primer elemento cuyo consoleid coincide con el dado.
 * pre: la lista esta inicializada.
 * post: devuelve la posicion si se encuentra, o LNULL en caso contrario.
 * variables:
 *   - consoleId: tConsoleId, identificador que se buscara en la lista.
 *   - list: tList, lista en la que se buscara el elemento.
 *   - p: tPosL, posicion temporal para recorrer la lista.
 */
tPosL findItem(tConsoleId consoleId, tList list);

#endif