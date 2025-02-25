/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P1 - Static List Interface
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 21/03/2025
*/

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"
#include <stdbool.h>

#define STATIC_LIST_SIZE 25  /* tamano maximo de la lista estatica */
#define LNULL -1             /* constante para indicar posicion nula */

/* estructura que representa una lista estatica de consolas */
typedef struct {
    tItemL items[STATIC_LIST_SIZE];
    int count;
} tList;

/* tipo que representa la posicion (indice) en la lista */
typedef int tPosL;

/*
 * createEmptyList: inicializa una lista vacia.
 * pre: list es un puntero a una variable tList.
 * post: se establece list->count = 0.
 * variables:
 *   - list: tList*, puntero a la lista que se va a inicializar.
 */
void createEmptyList(tList *list);

/*
 * isEmptyList: devuelve true si la lista esta vacia.
 * pre: la lista esta inicializada.
 * post: devuelve true si count == 0, false en otro caso.
 * variables:
 *   - list: tList, lista que se va a verificar.
 */
bool isEmptyList(tList list);

/*
 * first: devuelve la posicion del primer elemento.
 * pre: la lista no esta vacia.
 * post: devuelve 0.
 * variables:
 *   - list: tList, lista de la cual se obtendra la primera posicion.
 */
tPosL first(tList list);

/*
 * last: devuelve la posicion del ultimo elemento.
 * pre: la lista no esta vacia.
 * post: devuelve count - 1.
 * variables:
 *   - list: tList, lista de la cual se obtendra la ultima posicion.
 */
tPosL last(tList list);

/*
 * next: devuelve la posicion siguiente a la dada.
 * pre: pos es una posicion valida.
 * post: devuelve pos + 1, o LNULL si pos es el ultimo.
 * variables:
 *   - pos: tPosL, posicion actual en la lista.
 *   - list: tList, lista en la que se encuentra la posicion.
 */
tPosL next(tPosL pos, tList list);

/*
 * previous: devuelve la posicion anterior a la dada.
 * pre: pos es una posicion valida.
 * post: devuelve pos - 1, o LNULL si pos es el primero.
 * variables:
 *   - pos: tPosL, posicion actual en la lista.
 *   - list: tList, lista en la que se encuentra la posicion.
 */
tPosL previous(tPosL pos, tList list);

/*
 * insertItem: inserta un elemento en la lista antes de la posicion indicada.
 *           si pos es LNULL, inserta al final.
 * pre: la lista esta inicializada y pos es valida o LNULL.
 * post: se incrementa count y se desplazan elementos segun corresponda.
 *       devuelve true si la insercion fue exitosa, false si la lista esta llena.
 * variables:
 *   - item: tItemL, elemento que se va a insertar.
 *   - pos: tPosL, posicion en la que se insertara el elemento.
 *   - list: tList*, puntero a la lista en la que se insertara el elemento.
 *   - i: int, variable temporal para recorrer la lista.
 */
bool insertItem(tItemL item, tPosL pos, tList *list);

/*
 * deleteAtPosition: elimina el elemento en la posicion indicada.
 * pre: pos es una posicion valida en la lista.
 * post: se decrementa count y se desplazan los elementos posteriores.
 * variables:
 *   - pos: tPosL, posicion del elemento que se va a eliminar.
 *   - list: tList*, puntero a la lista de la cual se eliminara el elemento.
 *   - i: int, variable temporal para recorrer la lista.
 */
void deleteAtPosition(tPosL pos, tList *list);

/*
 * getItem: devuelve el elemento que ocupa la posicion indicada.
 * pre: pos es una posicion valida en la lista.
 * post: devuelve una copia del elemento.
 * variables:
 *   - pos: tPosL, posicion del elemento que se va a obtener.
 *   - list: tList, lista en la que se encuentra el elemento.
 */
tItemL getItem(tPosL pos, tList list);

/*
 * updateItem: actualiza el elemento en la posicion indicada.
 * pre: pos es una posicion valida en la lista.
 * post: se reemplaza el elemento en pos por el nuevo valor.
 * variables:
 *   - item: tItemL, nuevo valor que se asignara al elemento.
 *   - pos: tPosL, posicion del elemento que se va a actualizar.
 *   - list: tList*, puntero a la lista en la que se encuentra el elemento.
 */
void updateItem(tItemL item, tPosL pos, tList *list);

/*
 * findItem: busca el primer elemento cuyo consoleId coincide con el dado.
 * pre: la lista esta inicializada.
 * post: devuelve la posicion si se encuentra, o LNULL si no existe.
 * variables:
 *   - consoleId: tConsoleId, identificador que se buscara en la lista.
 *   - list: tList, lista en la que se buscara el elemento.
 *   - i: int, variable temporal para recorrer la lista.
 */
tPosL findItem(tConsoleId consoleId, tList list);

#endif