// Copyright 2020 Torcea Octavian

#ifndef DELETEFUNCTIONS_H_
#define DELETEFUNCTIONS_H_

#include "./structures.h"

void delOnlySong(struct doubleLinkedList *list);

void delFirst(struct doubleLinkedList *list, FILE *output);

void delLast(struct doubleLinkedList *list, FILE *output);

void delCurr(struct doubleLinkedList *list, FILE *output);

void delSong(struct doubleLinkedList *list, FILE *output, char *path);

#endif  // DELETEFUNCTIONS_H_
