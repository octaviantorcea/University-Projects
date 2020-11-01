// Copyright 2020 Torcea Octavian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "addFunctions.h"
#include "deleteFunctions.h"
#include "moveFunctions.h"
#include "showFunctions.h"
#include "./structures.h"

#define MAXLENGHT 90

/*
 * Functie ce initializeaza lista dublu inlantuita, dupa ce listei i s-a alocat
 * memorie in functia main.
 */
struct doubleLinkedList* initList(struct doubleLinkedList *list) {
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->pointer = NULL;
    return list;
}

/*
 * Elibereaza memoria tuturor nodurilor din lista, iar la final elibereaza
 * memoria folosita de lista.
 */
void freeList(struct doubleLinkedList **pointerList) {
    if ((*pointerList) == NULL) {
        printf("Nu exsita lista\n");
        return;
    }

    struct Node *curr = NULL;

    while ((*pointerList)->head != NULL) {
        curr = (*pointerList)->head;
        (*pointerList)->head = (*pointerList)->head->next;
        free(curr);
        (*pointerList)->size--;
    }

    free(*pointerList);
}

/*
 * Functia ia cate o linie din fisierul de input, o imparte in COMANDA si
 * NUMELE MELODIEI (daca e cazul), apoi apeleaza functiile primite din
 * fisierul de input.
 */
void cmdInterpr(FILE *input, FILE *output, struct doubleLinkedList *playlist) {
    char line[MAXLENGHT] = "\0", aux[MAXLENGHT] = "\0";
    char songName[MAXLENGHT] = "\0", path[MAXLENGHT] = "songs/";
    fgets(line, MAXLENGHT, input);
    snprintf(aux, strlen(line), "%s", line);
    static char *garbage;
    char *command = __strtok_r(aux, " \n", &garbage);
    snprintf(songName, MAXLENGHT, "%s", (line + strlen(command) + 1));
    songName[strlen(songName) - 1] = '\0';  // ca sa elimin caracterul '\n'
    snprintf(path + strlen(path), MAXLENGHT, "%s", songName);

    if (strcmp(command, "ADD_FIRST") == 0) {
        if (strcmp(path, "songs/") == 0) {
            printf("Nu s-a specificat melodia.\n");
        } else {
            addFirst(playlist, output, path);
        }
    } else if (strcmp(command, "ADD_LAST") == 0) {
        if (strcmp(path, "songs/") == 0) {
            printf("Nu s-a specificat melodia.\n");
        } else {
            addLast(playlist, output, path);
        }
    } else if (strcmp(command, "ADD_AFTER") == 0) {
        if (strcmp(path, "songs/") == 0) {
            printf("Nu s-a specificat melodia.\n");
        } else {
            addAfter(playlist, output, path);
        }
    } else if (strcmp(command, "DEL_FIRST") == 0) {
        delFirst(playlist, output);
    } else if (strcmp(command, "DEL_LAST") == 0) {
        delLast(playlist, output);
    } else if (strcmp(command, "DEL_CURR") == 0) {
        delCurr(playlist, output);
    } else if (strcmp(command, "DEL_SONG") == 0) {
        if (strcmp(path, "songs/") == 0) {
            printf("Nu s-a specificat melodia.\n");
        } else {
            delSong(playlist, output, path);
        }
    } else if (strcmp(command, "MOVE_NEXT") == 0) {
        moveNext(playlist, output);
    } else if (strcmp(command, "MOVE_PREV") == 0) {
        movePrev(playlist, output);
    } else if (strcmp(command, "SHOW_FIRST") == 0) {
        showFirst(playlist, output);
    } else if (strcmp(command, "SHOW_LAST") == 0) {
        showLast(playlist, output);
    } else if (strcmp(command, "SHOW_CURR") == 0) {
        showCurr(playlist, output);
    } else if (strcmp(command, "SHOW_PLAYLIST") == 0) {
        showPlaylist(playlist, output);
    } else {
        printf("Comanda gresita!\n");
    }
}

int main(int argc, char *argv[]) {
    FILE *input, *output;
    input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Nu s-a putut deschide fisierul de input.\n");
        fclose(input);
        return -1;
    }

    output = fopen(argv[2], "w");

    if (output == NULL) {
        printf("Nu s-a putut deschide fisierul de output.\n");
        fclose(input);
        fclose(output);
        return -1;
    }

    struct doubleLinkedList *playlist = NULL;
    playlist = malloc(sizeof(struct doubleLinkedList));
    initList(playlist);
    int queue = 0;
    fscanf(input, "%d", &queue);
    fseek(input, 1, SEEK_CUR);  // ca sa trec in fisier de caracterul '\n'

    for (int i = 0; i < queue; i++) {
        cmdInterpr(input, output, playlist);
    }

    freeList(&playlist);
    fclose(input);
    fclose(output);
    return 0;
}
