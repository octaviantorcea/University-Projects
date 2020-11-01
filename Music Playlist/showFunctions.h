// Copyright 2020 Torcea Octavian

#ifndef SHOWFUNCTIONS_H_
#define SHOWFUNCTIONS_H_

#include "./structures.h"

void printInfo(struct Node *node, FILE *output);

void showFirst(struct doubleLinkedList *list, FILE *output);

void showLast(struct doubleLinkedList *list, FILE *output);

void showCurr(struct doubleLinkedList *list, FILE *output);

void showPlaylist(struct doubleLinkedList *list, FILE *output);

#endif  // SHOWFUNCTIONS_H_
