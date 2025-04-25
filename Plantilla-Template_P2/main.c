/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P2 - Main Program
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 24/04/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "console_list.h"  // se incluye la interfaz del tad consolelist (lista ordenada de consolas)
#include "bid_stack.h"     // se incluye la interfaz del tad bidstack (pila de pujas)

#define MAX_BUFFER 255

/*
 * New: alta de una nueva consola.
 * entradas:
 *   - num: numero de la peticion.
 *   - consoleId: identificador de la consola.
 *   - seller: identificador del vendedor.
 *   - brandStr: marca de la consola.
 *   - priceStr: precio de la consola (cadena).
 *   - plist: puntero a la lista de consolas.
 * salidas:
 *   - imprime la cabecera y el resultado de la operacion.
 * precondiciones:
 *   - plist apunta a una lista inicializada.
 * postcondiciones:
 *   - si es exitosa, la consola se inserta en la lista con su pila vacia.
 */
void New(int num,
         char *consoleId,
         char *seller,
         char *brandStr,
         char *priceStr,
         tList *plist)
{
    // cabecera
    printf("********************\n");
    printf("%02d N: console %s seller %s brand %s price %s\n",
           num, consoleId, seller, brandStr, priceStr);

    // validacion basica de parametros
    if (!consoleId || !seller || !brandStr || !priceStr) {
        printf("+ Error: New not possible\n");
        return;
    }

    // no puede existir ya la consola
    if (findItem(consoleId, *plist) != LNULL) {
        printf("+ Error: New not possible\n");
        return;
    }

    // construccion del item
    tItemL item;
    strcpy(item.consoleId, consoleId);
    strcpy(item.seller,    seller);

    if (strcmp(brandStr, "nintendo") == 0) {
        item.consoleBrand = nintendo;
    } else if (strcmp(brandStr, "sega") == 0) {
        item.consoleBrand = sega;
    } else {
        printf("+ Error: New not possible\n");
        return;
    }

    item.consolePrice = atof(priceStr);
    item.bidCounter   = 0;

    // inicializar la pila estatica dentro de item
    createEmptyStack(&item.bidStack);

    // intentar insertar en la lista
    if (insertItem(item, plist))
        printf("* New: console %s seller %s brand %s price %.2f\n",
               item.consoleId, item.seller, brandStr, item.consolePrice);
    else
        printf("+ Error: New not possible\n");
}

/*
 * Delete: baja de una consola.
 * entradas:
 *   - num: numero de la peticion.
 *   - consoleId: identificador de la consola.
 *   - plist: puntero a la lista de consolas.
 * salidas:
 *   - imprime la cabecera y el resultado de la operacion.
 * precondiciones:
 *   - plist apunta a una lista inicializada.
 * postcondiciones:
 *   - si es exitosa, la consola y su pila se eliminan.
 */
void Delete(int num,
            char *consoleId,
            tList *plist)
{
    // cabecera
    printf("********************\n");
    printf("%02d D: console %s\n", num, consoleId);

    if (!consoleId) {
        printf("+ Error: Delete not possible\n");
        return;
    }

    tPosL pos = findItem(consoleId, *plist);
    if (pos == LNULL) {
        printf("+ Error: Delete not possible\n");
    } else {
        // obtenemos el item y guardamos el número de pujas actual
        tItemL item = getItem(pos, *plist);
        int oldBids = item.bidCounter;

        // vaciar pila y resetear contador
        clearStack(&item.bidStack);
        item.bidCounter = 0;
        updateItem(item, pos, plist);

        // borramos el nodo
        deleteAtPosition(pos, plist);

        // imprimimos usando el valor original oldBids
        char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
        printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n",
               item.consoleId, item.seller, brandStrOut,
               item.consolePrice, oldBids);
    }
}


/*
 * Bid: puja por una consola.
 * entradas:
 *   - num: numero de la peticion.
 *   - consoleId: identificador de la consola.
 *   - bidder: identificador del pujador.
 *   - priceStr: precio de la puja (cadena).
 *   - plist: puntero a la lista de consolas.
 * salidas:
 *   - imprime la cabecera y el resultado de la operacion.
 * precondiciones:
 *   - plist apunta a una lista inicializada.
 * postcondiciones:
 *   - si es exitosa, se apila la puja y se incrementa bidCounter.
 */
void Bid(int num,
         char *consoleId,
         char *bidder,
         char *priceStr,
         tList *plist)
{
    // cabecera
    printf("********************\n");
    printf("%02d B: console %s bidder %s price %s\n",
           num, consoleId, bidder, priceStr);

    // validacion basica de parametros
    if (!consoleId || !bidder || !priceStr) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    // conversion de precio
    float newPrice = atof(priceStr);
    tPosL pos = findItem(consoleId, *plist);
    if (pos == LNULL) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    // obtencion del item
    tItemL item = getItem(pos, *plist);
    if (strcmp(item.seller, bidder) == 0) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    // validacion de precio
    float currentPrice = item.consolePrice;
    if (!isEmptyStack(item.bidStack)) {
        tItemS topBid = peek(item.bidStack);
        currentPrice = topBid.consolePrice;
    }

    if (newPrice <= currentPrice) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    // construccion de la puja
    tItemS bid;
    strcpy(bid.bidder, bidder);
    bid.consolePrice = newPrice;

    // apilar la puja
    if (!push(bid, &item.bidStack)) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    // actualizacion del item
    item.bidCounter++;
    updateItem(item, pos, plist);

    // salida
    char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
    printf("* Bid: console %s bidder %s brand %s price %.2f bids %d\n",
           item.consoleId, bidder, brandStrOut,
           newPrice, item.bidCounter);
}

/*
 * Award: asigna el ganador de la puja.
 * entradas:
 *   - num: numero de la peticion.
 *   - consoleId: identificador de la consola.
 *   - plist: puntero a la lista de consolas.
 * salidas:
 *   - imprime la cabecera y el resultado de la operacion.
 * precondiciones:
 *   - plist apunta a una lista inicializada.
 * postcondiciones:
 *   - si es exitosa, se elimina la consola.
 */
void Award(int num,
           char *consoleId,
           tList *plist)
{
    // cabecera
    printf("********************\n");
    printf("%02d A: console %s\n", num, consoleId);

    // validacion basica de parametros
    if (!consoleId) {
        printf("+ Error: Award not possible\n");
        return;
    }

    // busqueda del item
    tPosL pos = findItem(consoleId, *plist);
    if (pos == LNULL) {
        printf("+ Error: Award not possible\n");
        return;
    }

    // obtencion del item
    tItemL item = getItem(pos, *plist);
    if (isEmptyStack(item.bidStack)) {
        printf("+ Error: Award not possible\n");
        return;
    }

    // obtencion de la puja ganadora
    tItemS winningBid = peek(item.bidStack);
    char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
    printf("* Award: console %s bidder %s brand %s price %.2f\n",
           item.consoleId, winningBid.bidder, brandStrOut,
           winningBid.consolePrice);

    // eliminacion del item
    deleteAtPosition(pos, plist);
}

/*
 * InvalidateBids: invalida pujas excesivas.
 * entradas:
 *   - num: numero de la peticion.
 *   - plist: puntero a la lista de consolas.
 * salidas:
 *   - imprime la cabecera y los resultados.
 * precondiciones:
 *   - plist apunta a una lista inicializada.
 * postcondiciones:
 *   - si es exitosa, se vacian las pilas que superen 2*media.
 */
void InvalidateBids(int num,
                    tList *plist)
{
    // cabecera
    printf("********************\n");
    printf("%02d I\n", num);

    // validacion basica de parametros
    if (isEmptyList(*plist)) {
        printf("+ Error: InvalidateBids not possible\n");
        return;
    }

    // calculo de la media de pujas
    int totalBids = 0, count = 0;
    tPosL pos = first(*plist);
    while (pos != LNULL) {
        tItemL item = getItem(pos, *plist);
        totalBids += item.bidCounter;
        count++;
        pos = next(pos, *plist);
    }

    float averageBids = (count > 0) ? (float)totalBids / count : 0;
    int invalidated = 0;

    // invalidacion de pujas excesivas
    pos = first(*plist);
    while (pos != LNULL) {
        tItemL item = getItem(pos, *plist);
        if (item.bidCounter > 2 * averageBids) {
            clearStack(&item.bidStack);
            int oldBids = item.bidCounter;
            item.bidCounter = 0;
            updateItem(item, pos, plist);
            char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
            printf("* InvalidateBids: console %s seller %s brand %s price %.2f bids %d average bids %.2f\n",
                   item.consoleId, item.seller, brandStrOut,
                   item.consolePrice, oldBids, averageBids);
            invalidated++;
        }
        pos = next(pos, *plist);
    }

    // salida
    if (invalidated == 0)
        printf("+ Error: InvalidateBids not possible\n");
}

/*
 * Remove: elimina consolas sin pujas.
 * entradas:
 *   - num: numero de la peticion.
 *   - plist: puntero a la lista de consolas.
 * salidas:
 *   - imprime la cabecera y los resultados.
 * precondiciones:
 *   - plist apunta a una lista inicializada.
 * postcondiciones:
 *   - si es exitosa, se eliminan todos los nodos con bidCounter==0.
 */
void Remove(int num,
            tList *plist)
{
    // cabecera
    printf("********************\n");
    printf("%02d R\n", num);

    // validacion basica de parametros
    if (isEmptyList(*plist)) {
        printf("+ Error: Remove not possible\n");
        return;
    }

    // se eliminan las consolas cuyo bidCounter sea igual a cero
    int removed = 0;
    tPosL pos = first(*plist);
    while (pos != LNULL) {
        tPosL nextPos = next(pos, *plist);
        tItemL item = getItem(pos, *plist);
        if (item.bidCounter == 0) {
            char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
            printf("Removing console %s seller %s brand %s price %.2f bids %d\n",
                   item.consoleId, item.seller, brandStrOut,
                   item.consolePrice, item.bidCounter);
            deleteAtPosition(pos, plist);
            removed++;
        }
        pos = nextPos;
    }

    // salida
    if (removed == 0)
        printf("+ Error: Remove not possible\n");
}

/*
 * Stats: muestra estadisticas y listado de consolas.
 * entradas:
 *   - num: numero de la peticion.
 *   - plist: puntero a la lista de consolas.
 * salidas:
 *   - imprime cabecera, listado, estadisticas y top bid.
 * precondiciones:
 *   - plist apunta a una lista inicializada.
 * postcondiciones:
 *   - no modifica la lista.
 */
void Stats(int num,
           tList *plist)
{
    // cabecera
    printf("********************\n");
    printf("%02d S\n", num);

    // validacion basica de parametros
    if (isEmptyList(*plist)) {
        printf("+ Error: Stats not possible\n");
        return;
    }

    // listado de consolas
    tPosL pos = first(*plist);
    while (pos != LNULL) {
        tItemL item = getItem(pos, *plist);
        char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
        if (!isEmptyStack(item.bidStack)) {
            printf("Console %s seller %s brand %s price %.2f bids %d top bidder %s\n",
                   item.consoleId, item.seller, brandStrOut,
                   item.consolePrice, item.bidCounter, peek(item.bidStack).bidder);
        } else {
            printf("Console %s seller %s brand %s price %.2f. No bids\n",
                   item.consoleId, item.seller, brandStrOut,
                   item.consolePrice);
        }
        pos = next(pos, *plist);
    }

    // estadisticas por marca
    int countN = 0, countS = 0;
    float sumN = 0, sumS = 0;
    pos = first(*plist);
    while (pos != LNULL) {
        tItemL item = getItem(pos, *plist);
        if (item.consoleBrand == nintendo) {
            countN++;
            sumN += item.consolePrice;
        } else {
            countS++;
            sumS += item.consolePrice;
        }
        pos = next(pos, *plist);
    }
    float avgN = (countN > 0) ? sumN / countN : 0;
    float avgS = (countS > 0) ? sumS / countS : 0;

    printf("\nBrand     Consoles    Price  Average\n");
    printf("Nintendo  %8d %8.2f %8.2f\n", countN, sumN, avgN);
    printf("Sega      %8d %8.2f %8.2f\n", countS, sumS, avgS);

    // se obtiene el item y la puja correspondiente a la puja más significativa
    float maxIncrease = 0;
    tPosL topPos = LNULL;
    pos = first(*plist);
    while (pos != LNULL) {
        tItemL item = getItem(pos, *plist);
        if (!isEmptyStack(item.bidStack)) {
            tItemS topBid = peek(item.bidStack);
            float increase = ((topBid.consolePrice - item.consolePrice) / item.consolePrice) * 100;
            if (increase > maxIncrease) {
                maxIncrease = increase;
                topPos = pos;
            }
        }
        pos = next(pos, *plist);
    }

    // salida
    if (topPos != LNULL) {
        tItemL topItem = getItem(topPos, *plist);
        tItemS topBid = peek(topItem.bidStack);
        char *brandStrOut = (topItem.consoleBrand == nintendo) ? "nintendo" : "sega";
        printf("Top bid: console %s seller %s brand %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
               topItem.consoleId, topItem.seller, brandStrOut,
               topItem.consolePrice, topBid.bidder, topBid.consolePrice,
               maxIncrease);
    } else {
        printf("Top bid not possible\n");
    }
}


/*
 * processCommand: procesa una petición de la plataforma de subastas.
 * entradas:
 *   - commandNumber: char*, número de la petición.
 *   - command: char, tipo de operación ('N', 'D', 'B', 'A', 'I', 'R', 'S').
 *   - param1, param2, param3, param4: char*, parámetros genéricos según la operación:
 *       • 'N': param1=consoleId, param2=seller,     param3=brand,   param4=price
 *       • 'D': param1=consoleId
 *       • 'B': param1=consoleId, param2=bidder,     param3=price
 *       • 'A': param1=consoleId
 *       • 'I', 'R', 'S': sin parámetros adicionales
 *   - plist: tList*, puntero a la lista de consolas.
 * salida:
 *   - imprime la cabecera de la petición y el resultado de la operación correspondiente.
 * precondiciones:
 *   - el puntero plist debe apuntar a una lista inicializada.
 *   - los parámetros (param1…param4) han de estar presentes según el formato de cada operación.
 * postcondiciones:
 *   - se ejecuta la función asociada y se muestra su resultado.
 */
void processCommand(char *commandNumber, char command,
                    char *param1, char *param2,
                    char *param3, char *param4,
                    tList *plist) {
    int num = atoi(commandNumber);

    switch (command) {
        case 'N':  // operacion new: formato "N consoleid seller brand price"
            New(num, param1, param2, param3, param4, plist);
            break;

        case 'D':  // operacion delete: formato "D consoleid"
            Delete(num, param1, plist);
            break;

        case 'B':  // operacion bid: formato "B consoleid bidder price"
            Bid(num, param1, param2, param3, plist);
            break;

        case 'A':  // operacion award: formato "A consoleid"
            Award(num, param1, plist);
            break;

        case 'I':  // operacion invalidatebids: formato "I"
            InvalidateBids(num, plist);
            break;

        case 'R':  // operacion remove: formato "R"
            Remove(num, plist);
            break;

        case 'S':  // operacion stats: formato "S"
            Stats(num, plist);
            break;

        default:   // operacion desconocida
            printf("********************\n");
            printf("%02d ?\n", num);
            break;
    }
}

/*
 * readTasks: lee las peticiones de un fichero y procesa cada una.
 * pre: el archivo debe existir y ser accesible.
 * post: se procesan las peticiones leídas.
 * variables:
 *   - filename: char*, nombre del fichero con las peticiones.
 *   - plist: tList*, puntero a la lista de consolas.
 *   - f: FILE*, puntero al archivo.
 *   - commandNumber, command, param1, param2, param3, param4: char*, parámetros de las peticiones.
 *   - delimiters: const char[], delimitadores para separar los parámetros.
 *   - buffer: char[], buffer para leer las líneas del archivo.
 */
    void readTasks(char *filename, tList *plist) {
        FILE *f = NULL;
        char *commandNumber, *command, *param1, *param2, *param3, *param4;
        const char delimiters[] = " \n\r";
        char buffer[MAX_BUFFER];

        f = fopen(filename, "r");
        if (f != NULL) {
            while (fgets(buffer, MAX_BUFFER, f)) {
                commandNumber = strtok(buffer, delimiters);
                command = strtok(NULL, delimiters);
                param1 = strtok(NULL, delimiters);
                param2 = strtok(NULL, delimiters);
                param3 = strtok(NULL, delimiters);
                param4 = strtok(NULL, delimiters);
                if (command != NULL)
                    processCommand(commandNumber, command[0], param1, param2, param3, param4, plist);
            }
            fclose(f);
        } else {
            printf("cannot open file %s.\n", filename);
        }
    }

/*
 * main: función principal.
 * pre: se deben proporcionar los parámetros de la línea de comandos.
 * post: inicializa la lista y procesa el fichero de peticiones.
 * variables:
 *   - nargs: int, número de argumentos de la línea de comandos.
 *   - args: char**, array de argumentos de la línea de comandos.
 *   - file_name: char*, nombre del fichero de peticiones.
 *   - list: tList, lista de consolas.
 */
    int main(int nargs, char **args) {
        char *file_name = "bid.txt";
        if (nargs > 1) {
            file_name = args[1];
        }
#ifdef INPUT_FILE
        else {
            file_name = INPUT_FILE;
        }
#endif
        tList list;
        createEmptyList(&list);
        readTasks(file_name, &list);
        return 0;
    }
