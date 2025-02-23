/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P1 - Dynamic List Interface
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 21/03/2025
*/

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"
#include <stdbool.h>

#define LNULL NULL  /* se utiliza NULL para indicar posicion nula */

/* estructura de nodo para la lista dinamica */
typedef struct sNode {
    tItemL item;
    struct sNode *next;
} tNode;

/* la lista dinamica se representa como un puntero al primer nodo */
typedef tNode* tList;
/* la posicion en la lista es un puntero al nodo */
typedef tNode* tPosL;

/*
 * createEmptyList: inicializa una lista dinamica vacia.
 * pre: list es un puntero a tList.
 * post: se asigna *list = NULL.
 */
void createEmptyList(tList *list);

/*
 * isEmptyList: determina si la lista dinamica esta vacia.
 * pre: la lista esta inicializada.
 * post: devuelve true si *list es NULL, false en otro caso.
 */
bool isEmptyList(tList list);

/*
 * first: devuelve el primer nodo de la lista.
 * pre: la lista no esta vacia.
 * post: devuelve list.
 */
tPosL first(tList list);

/*
 * last: devuelve el ultimo nodo de la lista.
 * pre: la lista no esta vacia.
 * post: devuelve el puntero al ultimo nodo.
 */
tPosL last(tList list);

/*
 * next: devuelve el nodo siguiente al nodo dado.
 * pre: pos es un nodo valido.
 * post: devuelve pos->next o LNULL si no existe.
 */
tPosL next(tPosL pos, tList list);

/*
 * previous: devuelve el nodo anterior al nodo dado.
 * pre: pos es un nodo valido y la lista no esta vacia.
 * post: devuelve el nodo anterior o LNULL si pos es el primero.
 */
tPosL previous(tPosL pos, tList list);

/*
 * insertItem: inserta un elemento en la lista antes del nodo dado.
 *           si pos es LNULL, inserta al final.
 * pre: la lista esta inicializada y pos es valida o LNULL.
 * post: se asigna memoria para el nuevo nodo y se inserta.
 *       devuelve true si la insercion fue correcta, false en caso de fallo.
 */
bool insertItem(tItemL item, tPosL pos, tList *list);

/*
 * deleteAtPosition: elimina el nodo en la posicion dada.
 * pre: pos es un nodo valido.
 * post: se elimina el nodo y se libera la memoria correspondiente.
 */
void deleteAtPosition(tPosL pos, tList *list);

/*
 * getItem: devuelve el elemento almacenado en el nodo dado.
 * pre: pos es un nodo valido.
 * post: devuelve el elemento contenido en pos.
 */
tItemL getItem(tPosL pos, tList list);

/*
 * updateItem: actualiza el elemento en el nodo dado.
 * pre: pos es un nodo valido.
 * post: se reemplaza el elemento en pos con el nuevo valor.
 */
void updateItem(tItemL item, tPosL pos, tList *list);

/*
 * findItem: busca el primer nodo cuyo consoleId coincide con el dado.
 * pre: la lista esta inicializada.
 * post: devuelve el puntero al nodo si se encuentra, o LNULL si no existe.
 */
tPosL findItem(tConsoleId consoleId, tList list);

#endif
