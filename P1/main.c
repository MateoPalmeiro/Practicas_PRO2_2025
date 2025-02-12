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

// variable global para la lista
tList list;

/*
 * processCommand: procesa una peticion de la plataforma de subastas.
 * entradas:
 *   commandNumber: numero de la peticion (string).
 *   command: tipo de operacion (char).
 *   param1, param2, param3, param4: parametros asociados a la operacion.
 * salida:
 *   imprime la operacion procesada y realiza la operacion.
 * pre: los parametros deben ser validos segun la operacion.
 * post: se muestra en pantalla la cabecera y el resultado de la operacion.
 */
void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4) {
    if (command == 'N') {
        // operacion new: formato "N consoleId userId brand price"
        char *consoleId = param1;
        char *userId = param2;
        char *brandStr = param3;
        char *priceStr = param4;
        printf("********************\n");
        printf("%s N: console %s seller %s brand %s price %s\n", commandNumber, consoleId, userId, brandStr, priceStr);
        if (!consoleId || !userId || !brandStr || !priceStr) {
            printf("+ Error: New not possible\n");
            return;
        }
        tConsoleBrand brand;
        if (strcmp(brandStr, "nintendo") == 0) {
            brand = nintendo;
            strcpy(brandStr, "nintendo");
        } else if (strcmp(brandStr, "sega") == 0) {
            brand = sega;
            strcpy(brandStr, "sega");
        } else {
            printf("+ Error: New not possible (invalid brand)\n");
            return;
        }
        float price = atof(priceStr);
        tPosL pos = findItem(consoleId, list);
        if (pos != LNULL) {
            printf("+ Error: New not possible\n");
        } else {
            tItemL item;
            strcpy(item.consoleId, consoleId);
            strcpy(item.seller, userId);
            item.consoleBrand = brand;
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
        char *consoleId = param1;
        printf("********************\n");
        printf("%s D: console %s\n", commandNumber, consoleId);
        if (!consoleId) {
            printf("+ Error: Delete not possible\n");
            return;
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
        char *consoleId = param1;
        char *userId = param2;
        char *priceStr = param3;
        printf("********************\n");
        printf("%s B: console %s bidder %s price %s\n", commandNumber, consoleId, userId, priceStr);
        if (!consoleId || !userId || !priceStr) {
            printf("+ Error: Bid not possible\n");
            return;
        }
        float price = atof(priceStr);
        tPosL pos = findItem(consoleId, list);
        if (pos == LNULL) {
            printf("+ Error: Bid not possible\n");
        } else {
            tItemL item = getItem(pos, list);
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
            tPosL pos = first(list);
            while (pos != LNULL) {
                tItemL item = getItem(pos, list);
                char *brandStrOut = (item.consoleBrand == nintendo) ? "nintendo" : "sega";
                printf("Console %s seller %s brand %s price %.2f bids %d\n",
                       item.consoleId, item.seller, brandStrOut, item.consolePrice, item.bidCounter);
                pos = next(pos, list);
            }
            printf("\n");
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
            printf("Brand     Consoles    Price  Average\n");
            printf("Nintendo %9d %8.2f %8.2f\n", countNintendo, sumNintendo, avgNintendo);
            printf("Sega     %9d %8.2f %8.2f\n", countSega, sumSega, avgSega);
        }
    }
    else {
        printf("********************\n");
        printf("%s ?\n", commandNumber);
    }
}

void readTasks(char *filename) {
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

            processCommand(commandNumber, command[0], param1, param2, param3, param4);
        }
        fclose(f);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {
    char *file_name = "new.txt";
    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }
    createEmptyList(&list);
    readTasks(file_name);
    return 0;
}

