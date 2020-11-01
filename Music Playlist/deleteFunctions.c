// Copyright 2020 Torcea Octavian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "addFunctions.h"
#include "./deleteFunctions.h"
#include "moveFunctions.h"
#include "showFunctions.h"
#include "./structures.h"

/*
 * Functie care sterge melodia din playlist atunci cand playlistul are doar o
 * singura melodie.
 */
void delOnlySong(struct doubleLinkedList *list) {
    free(list->head);
    list->head = NULL;
    list->tail = NULL;
    list->pointer = NULL;
    list->size--;
}

/*
 * In toate functiile delete se va elibera memoria nodului ce se va sterge,
 * astfel incat apelantul functiei sa nu fie nevoit sa elibereze el memoria.
 * De asemenea, se ia in considerare la fiecare stergere pozitia cursorului,
 * acesta mutandu-se conform cerintei.
 */

void delFirst(struct doubleLinkedList *list, FILE *output) {
    if (list->head == NULL) {
        fprintf(output, "Error: delete from empty playlist\n");
        return;
    }

    if (list->size == 1) {
        delOnlySong(list);
        return;
    }

    if (list->head == list->pointer) {
        moveNext(list, output);
    }

    list->head->next->prev = NULL;
    struct Node *aux = list->head->next;
    free(list->head);
    list->head = aux;
    list->size--;
}

void delLast(struct doubleLinkedList *list, FILE *output) {
    if (list->tail == NULL) {
        fprintf(output, "Error: delete from empty playlist\n");
        return;
    }

    if (list->size == 1) {
        delOnlySong(list);
        return;
    }

    if (list->tail == list->pointer) {
        movePrev(list, output);
    }

    list->tail->prev->next = NULL;
    struct Node *aux = list->tail->prev;
    free(list->tail);
    list->tail = aux;
    list->size--;
}

void delCurr(struct doubleLinkedList *list, FILE *output) {
    if (list->pointer == NULL) {
        fprintf(output, "Error: no track playing\n");
        return;
    }

    if (list->size == 1) {
        delOnlySong(list);
        return;
    }

    if (list->pointer == list->head) {
        delFirst(list, output);
        return;
    }

    if (list->pointer == list->tail) {
        delLast(list, output);
        return;
    }

    list->pointer->prev->next = list->pointer->next;
    list->pointer->next->prev = list->pointer->prev;
    struct Node *aux = list->pointer;
    moveNext(list, output);
    free(aux);
    list->size--;
}

void delSong(struct doubleLinkedList *list, FILE *output, char *path) {
    if (list->head == NULL) {
        fprintf(output, "Error: no song found to delete\n");
        return;
    }

    FILE *songFile = fopen(path, "rb");

    if (songFile == NULL) {
        printf("Nu s-a gasit melodia in folder.\n");
        fclose(songFile);
        return;
    }

    struct Node *songToFind = (struct Node *)malloc(sizeof(struct Node));
    struct Node *aux = list->head;
    copyInfo(songToFind, songFile);
    int ok = 0, count = 1;

    while (ok != 1 && count <= list->size) {
        if (strcmp(aux->title, songToFind->title) == 0) {
            if (aux == list->head && ok == 0) {
                delFirst(list, output);
                ok = 1;
            } else if (aux == list->tail && ok == 0) {
                delLast(list, output);
                ok = 1;
            } else {
                aux->prev->next = aux->next;
                aux->next->prev = aux->prev;
                free(aux);
                list->size--;
                ok = 1;
            }
        } else {
            aux = aux->next;
            count++;
        }
    }

    if (ok == 0) {
        fprintf(output, "Error: no song found to delete\n");
        fclose(songFile);
        free(songToFind);
        return;
    }

    fclose(songFile);
    free(songToFind);
}
