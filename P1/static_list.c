/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P1 - Static List Implementation
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 21/03/2025
*/

#include "static_list.h"  // incluye la interfaz de la lista estatica
#include <string.h>       // se incluye para utilizar funciones de manejo de cadenas (por ej, strcmp)

/*
 * createEmptyList: inicializa una lista estatica vacia.
 * pre: list es un puntero a una variable tList.
 * post: se establece list->count = 0.
 * variables:
 *   - list: tList*, puntero a la lista que se va a inicializar.
 */
void createEmptyList(tList *list) {
    // inicializa el contador de elementos en cero para indicar que la lista esta vacia
    list->count = 0;
}

/*
 * isEmptyList: determina si la lista esta vacia.
 * pre: la lista esta inicializada.
 * post: devuelve true si count es 0, false en otro caso.
 * variables:
 *   - list: tList, lista que se va a verificar.
 */
bool isEmptyList(tList list) {
    // se devuelve true si el contador es igual a cero, lo que significa que la lista no contiene elementos
    return (list.count == 0);
}

/*
 * first: devuelve la posicion del primer elemento de la lista.
 * pre: la lista no esta vacia.
 * post: devuelve 0.
 * variables:
 *   - list: tList, lista de la cual se obtendra la primera posicion.
 */
tPosL first(tList list) {
    // como la lista es un array, la primera posicion es el indice 0
    return 0;
}

/*
 * last: devuelve la posicion del ultimo elemento de la lista.
 * pre: la lista no esta vacia.
 * post: devuelve count - 1.
 * variables:
 *   - list: tList, lista de la cual se obtendra la ultima posicion.
 */
tPosL last(tList list) {
    // se devuelve la posicion del ultimo elemento, que es el contador menos uno
    return list.count - 1;
}

/*
 * next: devuelve la posicion siguiente a la dada.
 * pre: pos es una posicion valida.
 * post: devuelve pos + 1, o LNULL si pos es el ultimo.
 * variables:
 *   - pos: tPosL, posicion actual en la lista.
 *   - list: tList, lista en la que se encuentra la posicion.
 */
tPosL next(tPosL pos, tList list) {
    // si la posicion actual es menor que el indice del ultimo elemento, se devuelve el siguiente indice
    if (pos < list.count - 1)
        return pos + 1;
    else
        // si ya es el ultimo elemento, se devuelve LNULL para indicar que no hay siguiente
        return LNULL;
}

/*
 * previous: devuelve la posicion anterior a la dada.
 * pre: pos es una posicion valida.
 * post: devuelve pos - 1, o LNULL si pos es el primero.
 * variables:
 *   - pos: tPosL, posicion actual en la lista.
 *   - list: tList, lista en la que se encuentra la posicion.
 */
tPosL previous(tPosL pos, tList list) {
    // si la posicion es mayor que 0, se devuelve el indice anterior
    if (pos > 0)
        return pos - 1;
    else
        // si es el primer elemento, no existe posicion anterior, se devuelve LNULL
        return LNULL;
}

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
bool insertItem(tItemL item, tPosL pos, tList *list) {
    // si la lista ya alcanzo el tamano maximo, no se puede insertar
    if (list->count >= STATIC_LIST_SIZE)
        return false;

    // si pos es LNULL o es mayor o igual al numero de elementos, se inserta al final
    if (pos == LNULL || pos >= list->count) {
        // se asigna el nuevo elemento en la posicion count
        list->items[list->count] = item;
    } else {
        // se desplazan los elementos desde la posicion 'pos' hacia la derecha para hacer espacio
        for (int i = list->count; i > pos; i--) {
            list->items[i] = list->items[i - 1];
        }
        // se inserta el nuevo elemento en la posicion indicada
        list->items[pos] = item;
    }
    // se incrementa el contador de elementos
    list->count++;
    return true;
}

/*
 * deleteAtPosition: elimina el elemento en la posicion indicada.
 * pre: pos es una posicion valida en la lista.
 * post: se decrementa count y se desplazan los elementos posteriores.
 * variables:
 *   - pos: tPosL, posicion del elemento que se va a eliminar.
 *   - list: tList*, puntero a la lista de la cual se eliminara el elemento.
 *   - i: int, variable temporal para recorrer la lista.
 */
void deleteAtPosition(tPosL pos, tList *list) {
    // se verifica que la posicion sea valida; si no, se devuelve sin hacer nada
    if (pos < 0 || pos >= list->count)
        return;
    // se desplazan los elementos a partir de la posicion eliminada hacia la izquierda
    for (int i = pos; i < list->count - 1; i++) {
        list->items[i] = list->items[i + 1];
    }
    // se decrementa el contador de elementos
    list->count--;
}

/*
 * getItem: devuelve el elemento que ocupa la posicion indicada.
 * pre: pos es una posicion valida en la lista.
 * post: devuelve una copia del elemento.
 * variables:
 *   - pos: tPosL, posicion del elemento que se va a obtener.
 *   - list: tList, lista en la que se encuentra el elemento.
 */
tItemL getItem(tPosL pos, tList list) {
    // se devuelve el elemento en el indice especificado
    return list.items[pos];
}

/*
 * updateItem: actualiza el elemento en la posicion indicada.
 * pre: pos es una posicion valida en la lista.
 * post: se reemplaza el elemento en pos por el nuevo valor.
 * variables:
 *   - item: tItemL, nuevo valor que se asignara al elemento.
 *   - pos: tPosL, posicion del elemento que se va a actualizar.
 *   - list: tList*, puntero a la lista en la que se encuentra el elemento.
 */
void updateItem(tItemL item, tPosL pos, tList *list) {
    // se verifica que la posicion sea valida y se actualiza el elemento
    if (pos >= 0 && pos < list->count)
        list->items[pos] = item;
}

/*
 * findItem: busca el primer elemento cuyo consoleId coincide con el dado.
 * pre: la lista esta inicializada.
 * post: devuelve la posicion si se encuentra, o LNULL si no existe.
 * variables:
 *   - consoleId: tConsoleId, identificador que se buscara en la lista.
 *   - list: tList, lista en la que se buscara el elemento.
 *   - i: int, variable temporal para recorrer la lista.
 */
tPosL findItem(tConsoleId consoleId, tList list) {
    // se recorre la lista desde el inicio hasta encontrar el elemento que coincida
    for (int i = 0; i < list.count; i++) {
        if (strcmp(list.items[i].consoleId, consoleId) == 0)
            return i; // se devuelve la posicion del elemento encontrado
    }
    // si no se encontro, se devuelve LNULL
    return LNULL;
}