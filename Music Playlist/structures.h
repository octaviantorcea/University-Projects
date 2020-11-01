// Copyright 2020 Torcea Octavian

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

struct Node {
    char antet[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    struct Node *prev, *next;
};

struct doubleLinkedList {
    int size;
    struct Node *head, *tail, *pointer;
};

#endif  // STRUCTURES_H_
