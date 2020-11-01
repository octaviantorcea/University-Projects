// Copyright 2020 Torcea Octavian

#ifndef ADDFUNCTIONS_H_
#define ADDFUNCTIONS_H_

#include "./structures.h"

void copyInfo(struct Node *song, FILE *input);

void addFirst(struct doubleLinkedList *list, FILE *output, char *path);

void addLast(struct doubleLinkedList *list, FILE *output, char *path);

void addAfter(struct doubleLinkedList *list, FILE *output, char *path);

#endif  // ADDFUNCTIONS_H_
