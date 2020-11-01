// Copyright 2020 Torcea Octavian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./addFunctions.h"
#include "deleteFunctions.h"
#include "moveFunctions.h"
#include "showFunctions.h"
#include "./structures.h"

/*
 * Datele ce trebuie copiate sunt cu 94 bytes in stanga de
 * la sfarsitul fisierului.
 */
#define OFFSET -94

/*
 * Functie care copiaza datele din fisier in nod.
 */
void copyInfo(struct Node *song, FILE *input) {
    char tag[4] = "TAG";
    tag[3] = '\0';
    snprintf(song->antet, strlen(tag), "%s", tag);
    fseek(input, OFFSET, SEEK_END);
    fread(song->title, sizeof(song->title), 1, input);
    fread(song->artist, sizeof(song->artist), 1, input);
    fread(song->album, sizeof(song->album), 1, input);
    fread(song->year, sizeof(song->year), 1, input);
}

void addFirst(struct doubleLinkedList *list, FILE *output, char *path) {
    FILE *songFile = fopen(path, "rb");

    if (songFile == NULL) {
        printf("Nu s-a gasit melodia in folder.\n");
        return;
    }

    struct Node *newSong = (struct Node *)malloc(sizeof(struct Node));
    copyInfo(newSong, songFile);

    if (list->size == 0) {
        list->head = newSong;
        list->tail = newSong;
        list->pointer = newSong;
        newSong->next = NULL;
        newSong->prev = NULL;
        list->size++;
        fclose(songFile);
        return;
    }

    int ok = 0, count = 1;
    struct Node *aux = list->head;

    while (ok != 1 && count <= list->size) {
        if (strcmp(aux->title, newSong->title) == 0) {
            ok = 1;
            if (list->size > 1) {
                if (list->head == aux) {
                    delFirst(list, output);
                    list->head->prev = newSong;
                    newSong->next = list->head;
                    newSong->prev = NULL;
                    list->head = newSong;
                    list->size++;
                    fclose(songFile);
                    return;
                }

                if (list->tail == aux) {
                    delLast(list, output);
                    list->head->prev = newSong;
                    newSong->next = list->head;
                    newSong->prev = NULL;
                    list->head = newSong;
                    list->size++;
                    fclose(songFile);
                    return;
                }

                if (aux == list->pointer) {
                    moveNext(list, output);
                }

                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
                free(aux);
                list->head->prev = newSong;
                newSong->next = list->head;
                newSong->prev = NULL;
                list->head = newSong;
                fclose(songFile);
                return;
            } else {
                free(newSong);
                fclose(songFile);
                return;
            }
        }

        aux = aux->next;
        count++;
    }

    if (ok == 0) {
        list->head->prev = newSong;
        newSong->next = list->head;
        newSong->prev = NULL;
        list->head = newSong;
        list->size++;
    }

    fclose(songFile);
}

void addLast(struct doubleLinkedList *list, FILE *output, char *path) {
    FILE *songFile = fopen(path, "rb");

    if (songFile == NULL) {
        printf("Nu s-a gasit melodia in folder.\n");
        return;
    }

    struct Node *newSong = (struct Node *)malloc(sizeof(struct Node));
    copyInfo(newSong, songFile);

    if (list->size == 0) {
        list->head = newSong;
        list->tail = newSong;
        list->pointer = newSong;
        newSong->next = NULL;
        newSong->prev = NULL;
        list->size++;
        fclose(songFile);
        return;
    }

    int ok = 0, count = 1;
    struct Node *aux = list->head;

    while (ok != 1 && count <= list->size) {
        if (strcmp(aux->title, newSong->title) == 0) {
            ok = 1;
            if (list->size > 1) {
                if (list->head == aux) {
                    delFirst(list, output);
                    list->tail->next = newSong;
                    newSong->next = NULL;
                    newSong->prev = list->tail;
                    list->tail = newSong;
                    list->size++;
                    fclose(songFile);
                    return;
                }

                if (list->tail == aux) {
                    delLast(list, output);
                    list->tail->next = newSong;
                    newSong->next = NULL;
                    newSong->prev = list->tail;
                    list->tail = newSong;
                    list->size++;
                    fclose(songFile);
                    return;
                }

                if (aux == list->pointer) {
                    moveNext(list, output);
                }

                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
                free(aux);
                list->tail->next = newSong;
                newSong->next = NULL;
                newSong->prev = list->tail;
                list->tail = newSong;
                fclose(songFile);
                return;
            } else {
                free(newSong);
                fclose(songFile);
                return;
            }
        }
        aux = aux->next;
        count++;
    }

    if (ok == 0) {
        list->tail->next = newSong;
        newSong->next = NULL;
        newSong->prev = list->tail;
        list->tail = newSong;
        list->size++;
    }

    fclose(songFile);
}

void addAfter(struct doubleLinkedList *list, FILE *output, char *path) {
    if (list->pointer == NULL) {
        return;
    }

    FILE *songFile = fopen(path, "rb");

    if (songFile == NULL) {
        printf("Nu s-a gasit melodia in folder.\n");
        return;
    }

    struct Node *newSong = (struct Node *)malloc(sizeof(struct Node));
    copyInfo(newSong, songFile);

    if (strcmp(list->pointer->title, newSong->title) == 0) {
        free(newSong);
        fclose(songFile);
        return;
    }

    struct Node *aux = list->head;

    while (aux != NULL) {
        if (strcmp(aux->title, newSong->title) == 0) {
            delSong(list, output, path);
            break;
        }

        aux = aux->next;
    }

    if (list->pointer == list->tail) {
        list->tail = newSong;
        newSong->next = NULL;
        newSong->prev = list->pointer;
        list->pointer->next = newSong;
        fclose(songFile);
        list->size++;
        return;
    }

    list->pointer->next->prev = newSong;
    newSong->next = list->pointer->next;
    newSong->prev = list->pointer;
    list->pointer->next = newSong;
    fclose(songFile);
    list->size++;
}
