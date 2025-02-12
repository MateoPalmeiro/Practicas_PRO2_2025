/*
TITLE: PROGRAMMING II LABS
SUBTITLE: Practical P1 - Main Program
AUTHOR 1: Mateo Palmeiro Muniz           LOGIN 1: mateo.palmeiro@udc.es
AUTHOR 2: Nicolas Otero Costa            LOGIN 2: nicolas.otero1@udc.es
GROUP: 1.2    DATE: 21/03/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

/*
 * main: funcion principal que procesa las peticiones de la plataforma de subastas.
 * se leen las operaciones de un fichero de entrada y se ejecutan las acciones correspondientes.
 * operaciones:
 *   - N (new): alta de una consola.
 *       formato: N consoleId userId brand price
 *   - D (delete): baja de una consola.
 *       formato: D consoleId
 *   - B (bid): puja sobre una consola.
 *       formato: B consoleId userId price
 *   - S (stats): listado de consolas y estadisticas.
 *       formato: S
 *
 * pre: el fichero de entrada existe y esta en el formato correcto.
 * post: se ejecutan las operaciones y se muestra la salida correspondiente.
 */
int main(int nargs, char **args) {
    char *file_name = "new.txt";
    if (nargs > 1) {
        file_name = args[1];
    }
#ifdef INPUT_FILE
    else {
        file_name = INPUT_FILE;
    }
#endif

    FILE *fp = fopen(file_name, "r");
    if (!fp) {
        fprintf(stderr, "cannot open file %s.\n", file_name);
        return 1;
    }

    // inicializar la lista (tanto para implementacion estatica como dinamica)
    tList list;
    createEmptyList(&list);

    char buffer[MAX_BUFFER];
    // se procesan las lineas del fichero
    while (fgets(buffer, MAX_BUFFER, fp)) {
        // eliminar salto de linea
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == 0)
            continue;

        // se extraen los tokens: numero de comando, tipo y parametros
        char *commandNumber = strtok(buffer, " ");
        char *commandStr = strtok(NULL, " ");
        if (!commandStr) continue;
        char command = commandStr[0];

        if (command == 'N') {
            // operacion new: formato "N consoleId userId brand price"
            char *consoleId = strtok(NULL, " ");
            char *userId = strtok(NULL, " ");
            char *brandStr = strtok(NULL, " ");
            char *priceStr = strtok(NULL, " ");
            printf("********************\n");
            printf("%s N: console %s seller %s brand %s price %s\n", commandNumber, consoleId, userId, brandStr, priceStr);
            if (!consoleId || !userId || !brandStr || !priceStr) {
                printf("+ Error: New not possible\n");
                continue;
            }
            float price = atof(priceStr);
            // verificar si ya existe una consola con ese id
            tPosL pos = findItem(consoleId, list);
            if (pos != LNULL) {
                printf("+ Error: New not possible\n");
            } else {
                tItemL item;
                strcpy(item.consoleId, consoleId);
                strcpy(item.seller, userId);
                if (strcmp(brandStr, "nintendo") == 0)
                    item.consoleBrand = nintendo;
                else if (strcmp(brandStr, "sega") == 0)
                    item.consoleBrand = sega;
                else
                    item.consoleBrand = nintendo; // valor por defecto si no coincide
                item.consolePrice = price;
                item.bidCounter = 0;
                if (insertItem(item, LNULL, &list))
                    printf("* New: console %s seller %s brand %s price %.2f\n", consoleId, userId, brandStr, price);
                else
                    printf("+ Error: New not possible\n");
            }
        }
        else if (command == 'D') {
            // operacion delete: formato "D consoleId"
            char *consoleId = strtok(NULL, " ");
            printf("********************\n");
            printf("%s D: console %s\n", commandNumber, consoleId);
            if (!consoleId) {
                printf("+ Error: Delete not possible\n");
                continue;
            }
            tPosL pos = findItem(consoleId, list);
            if (pos == LNULL) {
                printf("+ Error: Delete not possible\n");
            } else {
                tItemL item = getItem(pos, list);
                deleteAtPosition(pos, &list);
                char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
                printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n",
                       item.consoleId, item.seller, brandStrOut, item.consolePrice, item.bidCounter);
            }
        }
        else if (command == 'B') {
            // operacion bid: formato "B consoleId userId price"
            char *consoleId = strtok(NULL, " ");
            char *userId = strtok(NULL, " ");
            char *priceStr = strtok(NULL, " ");
            printf("********************\n");
            printf("%s B: console %s bidder %s price %s\n", commandNumber, consoleId, userId, priceStr);
            if (!consoleId || !userId || !priceStr) {
                printf("+ Error: Bid not possible\n");
                continue;
            }
            float price = atof(priceStr);
            tPosL pos = findItem(consoleId, list);
            if (pos == LNULL) {
                printf("+ Error: Bid not possible\n");
            } else {
                tItemL item = getItem(pos, list);
                // verificar que el pujador no sea el vendedor y que el precio sea mayor al actual
                if (strcmp(item.seller, userId) == 0 || price <= item.consolePrice) {
                    printf("+ Error: Bid not possible\n");
                } else {
                    item.consolePrice = price;
                    item.bidCounter++;
                    updateItem(item, pos, &list);
                    char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
                    printf("* Bid: console %s seller %s brand %s price %.2f bids %d\n",
                           item.consoleId, item.seller, brandStrOut, item.consolePrice, item.bidCounter);
                }
            }
        }
        else if (command == 'S') {
            // operacion stats: formato "S"
            printf("********************\n");
            printf("%s S\n", commandNumber);
            if (isEmptyList(list)) {
                printf("+ Error: Stats not possible\n");
            } else {
                // imprimir listado de consolas
                tPosL pos = first(list);
                while (pos != LNULL) {
                    tItemL item = getItem(pos, list);
                    char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
                    printf("Console %s seller %s brand %s price %.2f bids %d\n",
                           item.consoleId, item.seller, brandStrOut, item.consolePrice, item.bidCounter);
                    pos = next(pos, list);
                }
                // calcular estadisticas por marca
                int countNintendo = 0, countSega = 0;
                float sumNintendo = 0, sumSega = 0;
                pos = first(list);
                while (pos != LNULL) {
                    tItemL item = getItem(pos, list);
                    if (item.consoleBrand == nintendo) {
                        countNintendo++;
                        sumNintendo += item.consolePrice;
                    } else if (item.consoleBrand == sega) {
                        countSega++;
                        sumSega += item.consolePrice;
                    }
                    pos = next(pos, list);
                }
                float avgNintendo = (countNintendo > 0) ? sumNintendo / countNintendo : 0;
                float avgSega = (countSega > 0) ? sumSega / countSega : 0;
                printf("Brand     Consoles     Price     Average\n");
                printf("nintendo  %8d  %8.2f  %8.2f\n", countNintendo, sumNintendo, avgNintendo);
                printf("sega      %8d  %8.2f  %8.2f\n", countSega, sumSega, avgSega);
            }
        }
        else {
            // operacion desconocida
            printf("********************\n");
            printf("%s ?\n", commandNumber);
        }
    } // fin del while
    fclose(fp);
    return 0;
}
