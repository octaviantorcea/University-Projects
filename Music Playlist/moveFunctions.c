// Copyright 2020 Torcea Octavian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "addFunctions.h"
#include "deleteFunctions.h"
#include "./moveFunctions.h"
#include "showFunctions.h"
#include "./structures.h"

void moveNext(struct doubleLinkedList *list, FILE *output) {
    if (list->pointer == NULL) {
        fprintf(output, "Error: no track playing\n");
        return;
    }

    if (list->pointer->next != NULL) {
        list->pointer = list->pointer->next;
    } else {
        return;
    }
}

void movePrev(struct doubleLinkedList *list, FILE *output) {
    if (list->pointer == NULL) {
        fprintf(output, "Error: no track playing\n");
        return;
    }

    if (list->pointer->prev != NULL) {
        list->pointer = list->pointer->prev;
    } else {
        return;
    }
}
