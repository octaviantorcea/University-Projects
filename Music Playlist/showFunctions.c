// Copyright 2020 Torcea Octavian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "addFunctions.h"
#include "deleteFunctions.h"
#include "moveFunctions.h"
#include "./showFunctions.h"
#include "./structures.h"

/*
 * Functie ce afiseaza toate datele melodiei.
 */
void printInfo(struct Node *node, FILE *output) {
    fprintf(output, "Title: %.30s\n", node->title);
    fprintf(output, "Artist: %.30s\n", node->artist);
    fprintf(output, "Album: %.30s\n", node->album);
    fprintf(output, "Year: %.4s\n", node->year);
}

void showFirst(struct doubleLinkedList *list, FILE *output) {
    if (list->head == NULL) {
        fprintf(output, "Error: show empty playlist\n");
        return;
    }

    printInfo(list->head, output);
}

void showLast(struct doubleLinkedList *list, FILE *output) {
    if (list->tail == NULL) {
        fprintf(output, "Error: show empty playlist\n");
        return;
    }

    printInfo(list->tail, output);
}

void showCurr(struct doubleLinkedList *list, FILE *output) {
    if (list->pointer == NULL) {
        fprintf(output, "Error: show empty playlist\n");
        return;
    }

    printInfo(list->pointer, output);
}

void showPlaylist(struct doubleLinkedList *list, FILE *output) {
    fprintf(output, "[");
    struct Node *curr = list->head;

    if (list->head == NULL) {
        fprintf(output, "]\n");
        return;
    } else {
        fprintf(output, "%.30s;", curr->title);
        curr = curr->next;
    }

    while (curr->next != NULL) {
        fprintf(output, " %.30s;", curr->title);
        curr = curr->next;
    }

    fprintf(output, " %.30s", curr->title);
    fprintf(output, "]\n");
}
