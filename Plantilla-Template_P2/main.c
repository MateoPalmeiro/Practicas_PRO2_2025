/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P1 - Main Program
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 4.3    DATE: 21/03/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "console_list.h"  // se incluye la interfaz del tad consolelist (lista ordenada de consolas)
#include "bid_stack.h"     // se incluye la interfaz del tad bidstack (pila de pujas)

#define MAX_BUFFER 255

/*
 * processCommand: procesa una peticion de la plataforma de subastas.
 * entradas:
 *   - commandNumber: char*, numero de la peticion.
 *   - command: char, tipo de operacion.
 *   - param1, param2, param3, param4: char*, parametros asociados a la operacion.
 *   - plist: tList*, puntero a la lista de consolas.
 * salida:
 *   se imprime la cabecera y se ejecuta la operacion correspondiente.
 * pre: los parametros deben ser validos segun la operacion.
 * post: se muestran los mensajes de salida de la operacion.
 * variables:
 *   - consoleId: char*, identificador de la consola.
 *   - userId: char*, identificador del usuario (seller o bidder).
 *   - brandStr: char*, marca de la consola.
 *   - priceStr: char*, precio de la consola.
 *   - brand: tConsoleBrand, enumeracion que representa la marca.
 *   - newPrice: float, precio de la puja.
 *   - pos: tPosL, posicion en la lista.
 *   - item: tItemL, elemento (consola) de la lista.
 *   - brandStrOut: char*, cadena que representa la marca para salida.
 */
void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *plist) {
    if (command == 'N') {  // operacion new: formato "N consoleId seller brand price"
        char *consoleId = param1;
        char *seller = param2;
        char *brandStr = param3;
        char *priceStr = param4;
        printf("********************\n");
        printf("%s n: console %s seller %s brand %s price %s\n", commandNumber, consoleId, seller, brandStr, priceStr);
        if (!consoleId || !seller || !brandStr || !priceStr) {
            printf("+ error: new not possible\n");
            return;
        }
        if (findItem(consoleId, *plist) != LNULL) {
            printf("+ error: new not possible\n");
            return;
        }
        tItemL item;
        strcpy(item.consoleId, consoleId);
        strcpy(item.seller, seller);
        tConsoleBrand brand;
        if (strcmp(brandStr, "nintendo") == 0) {
            brand = nintendo;
            strcpy(brandStr, "nintendo");
        } else if (strcmp(brandStr, "sega") == 0) {
            brand = sega;
            strcpy(brandStr, "sega");
        } else {
            printf("+ error: new not possible (invalid brand)\n");
            return;
        }
        item.consoleBrand = brand;
        item.consolePrice = atof(priceStr);
        item.bidCounter = 0;
        createEmptyStack(&item.bidStack);  // inicializar la pila de pujas asociada a la consola
        if (insertItem(item, LNULL, plist))
            printf("* new: console %s seller %s brand %s price %.2f\n", item.consoleId, item.seller, brandStr, item.consolePrice);
        else
            printf("+ error: new not possible\n");
    }
    else if (command == 'D') {  // operacion delete: formato "D consoleId"
        char *consoleId = param1;
        printf("********************\n");
        printf("%s d: console %s\n", commandNumber, consoleId);
        if (!consoleId) {
            printf("+ error: delete not possible\n");
            return;
        }
        tPosL pos = findItem(consoleId, *plist);
        if (pos == LNULL) {
            printf("+ error: delete not possible\n");
        } else {
            tItemL item = getItem(pos, *plist);
            if (!isEmptyStack(item.bidStack)) {
                printf("+ error: delete not possible\n");
                return;
            }
            deleteAtPosition(pos, plist);
            char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
            printf("* delete: console %s seller %s brand %s price %.2f bids %d\n",
                   item.consoleId, item.seller, brandStrOut, item.consolePrice, item.bidCounter);
        }
    }
    else if (command == 'B') {  // operacion bid: formato "B consoleId bidder price"
        char *consoleId = param1;
        char *bidder = param2;
        char *priceStr = param3;
        printf("********************\n");
        printf("%s b: console %s bidder %s price %s\n", commandNumber, consoleId, bidder, priceStr);
        if (!consoleId || !bidder || !priceStr) {
            printf("+ error: bid not possible\n");
            return;
        }
        float newPrice = atof(priceStr);
        tPosL pos = findItem(consoleId, *plist);
        if (pos == LNULL) {
            printf("+ error: bid not possible\n");
            return;
        }
        tItemL item = getItem(pos, *plist);
        if (strcmp(item.seller, bidder) == 0) {
            printf("+ error: bid not possible\n");
            return;
        }
        float currentPrice = item.consolePrice;
        if (!isEmptyStack(item.bidStack)) {
            tItemS topBid = peek(item.bidStack);
            currentPrice = topBid.consolePrice;
        }
        if (newPrice <= currentPrice) {
            printf("+ error: bid not possible\n");
            return;
        }
        tItemS bid;
        strcpy(bid.bidder, bidder);
        bid.consolePrice = newPrice;
        if (!push(bid, &item.bidStack)) {
            printf("+ error: bid not possible\n");
            return;
        }
        item.bidCounter++;
        updateItem(item, pos, plist);
        char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
        printf("* bid: console %s bidder %s brand %s price %.2f bids %d\n",
               item.consoleId, bidder, brandStrOut, newPrice, item.bidCounter);
    }
    else if (command == 'A') {  // operacion award: formato "A consoleId"
        char *consoleId = param1;
        printf("********************\n");
        printf("%s a: console %s\n", commandNumber, consoleId);
        if (!consoleId) {
            printf("+ error: award not possible\n");
            return;
        }
        tPosL pos = findItem(consoleId, *plist);
        if (pos == LNULL) {
            printf("+ error: award not possible\n");
            return;
        }
        tItemL item = getItem(pos, *plist);
        if (isEmptyStack(item.bidStack)) {
            printf("+ error: award not possible\n");
            return;
        }
        tItemS winningBid = peek(item.bidStack);
        char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
        printf("* award: console %s bidder %s brand %s price %.2f\n",
               item.consoleId, winningBid.bidder, brandStrOut, winningBid.consolePrice);
        deleteAtPosition(pos, plist);
    }
    else if (command == 'I') {  // operacion invalidatebids: formato "I"
        printf("********************\n");
        printf("%s i\n", commandNumber);
        if (isEmptyList(*plist)) {
            printf("+ error: invalidatebids not possible\n");
            return;
        }
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
        pos = first(*plist);
        while (pos != LNULL) {
            tItemL item = getItem(pos, *plist);
            if (item.bidCounter > 2 * averageBids) {
                clearStack(&item.bidStack);
                int oldBids = item.bidCounter;
                item.bidCounter = 0;
                updateItem(item, pos, plist);
                char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
                printf("* invalidatebids: console %s seller %s brand %s price %.2f bids %d average bids %.2f\n",
                       item.consoleId, item.seller, brandStrOut, item.consolePrice, oldBids, averageBids);
                invalidated++;
            }
            pos = next(pos, *plist);
        }
        if (invalidated == 0)
            printf("+ error: invalidatebids not possible\n");
    }
    else if (command == 'R') {  // operacion remove: formato "R"
        printf("********************\n");
        printf("%s r\n", commandNumber);
        if (isEmptyList(*plist)) {
            printf("+ error: remove not possible\n");
            return;
        }
        int removed = 0;
        tPosL pos = *plist;
        tPosL prev = LNULL;
        while (pos != LNULL) {
            tItemL item = getItem(pos, *plist);
            if (item.bidCounter == 0) {
                char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
                printf("removing console %s seller %s brand %s price %.2f bids %d\n",
                       item.consoleId, item.seller, brandStrOut, item.consolePrice, item.bidCounter);
                removed++;
                if (pos == *plist) {
                    *plist = pos->next;
                    free(pos);
                    pos = *plist;
                    prev = LNULL;
                    continue;
                } else {
                    prev->next = pos->next;
                    free(pos);
                    pos = prev->next;
                    continue;
                }
            }
            prev = pos;
            pos = next(pos, *plist);
        }
        if (removed == 0)
            printf("+ error: remove not possible\n");
    }
    else if (command == 'S') {  // operacion stats: formato "S"
        printf("********************\n");
        printf("%s s\n", commandNumber);
        if (isEmptyList(*plist)) {
            printf("+ error: stats not possible\n");
            return;
        }
        tPosL pos = first(*plist);
        while (pos != LNULL) {
            tItemL item = getItem(pos, *plist);
            char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
            if (!isEmptyStack(item.bidStack))
                printf("console %s seller %s brand %s price %.2f bids %d top bidder %s\n",
                       item.consoleId, item.seller, brandStrOut, item.consolePrice, item.bidCounter, peek(item.bidStack).bidder);
            else
                printf("console %s seller %s brand %s price %.2f bids %d no bids\n",
                       item.consoleId, item.seller, brandStrOut, item.consolePrice, item.bidCounter);
            pos = next(pos, *plist);
        }
        printf("\n");
        int countNintendo = 0, countSega = 0;
        float sumNintendo = 0, sumSega = 0;
        pos = first(*plist);
        while (pos != LNULL) {
            tItemL item = getItem(pos, *plist);
            if (item.consoleBrand == nintendo) {
                countNintendo++;
                sumNintendo += item.consolePrice;
            } else if (item.consoleBrand == sega) {
                countSega++;
                sumSega += item.consolePrice;
            }
            pos = next(pos, *plist);
        }
        float avgNintendo = (countNintendo > 0) ? sumNintendo / countNintendo : 0;
        float avgSega = (countSega > 0) ? sumSega / countSega : 0;
        printf("brand     consoles    price  average\n");
        printf("nintendo  %8d %8.2f %8.2f\n", countNintendo, sumNintendo, avgNintendo);
        printf("sega      %8d %8.2f %8.2f\n", countSega, sumSega, avgSega);
        pos = first(*plist);
        tPosL topPos = LNULL;
        float maxIncrease = 0;
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
        if (topPos != LNULL) {
            tItemL topItem = getItem(topPos, *plist);
            tItemS topBid = peek(topItem.bidStack);
            char *brandStrOut = (topItem.consoleBrand == nintendo) ? "nintendo" : "sega";
            printf("\n top bid: console %s seller %s brand %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
                   topItem.consoleId, topItem.seller, brandStrOut, topItem.consolePrice,
                   topBid.bidder, topBid.consolePrice, maxIncrease);
        } else {
            printf("top bid not possible\n");
        }
    }
    else {
        printf("********************\n");
        printf("%s ?\n", commandNumber);
    }
}

/*
 * readTasks: lee las peticiones de un fichero y procesa cada una.
 * entrada:
 *   - filename: char*, nombre del fichero con las peticiones.
 *   - plist: tList*, puntero a la lista de consolas.
 * salida:
 *   se procesan las peticiones leidas.
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
 * main: funcion principal.
 * argumentos:
 *   - nargs, args: parametros de la linea de comandos.
 * salida:
 *   inicializa la lista y procesa el fichero de peticiones.
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
