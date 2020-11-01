// Copyright 2020 Octavian Torcea

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXLENGHTLINE 101

struct fakeNode {
    char key[MAXLENGHTLINE];  // practic este cuvantul
    int freq;  // numarul de aparitii
};

struct Hashtable {
    struct fakeNode *nodeVec;  // vector de structuri fakeNode
    int hmax;  // numarul maxim de structuri de tip fakeNode
    unsigned int (*hash_function)(void*);
};

/*
 * Functie de hashing (cea din laborator).
 */
unsigned int hash_function_string(void *a) {
    /*
     * Credits: http://www.cse.yorku.ca/~oz/hash.html
     */
    unsigned char *puchar_a = (unsigned char*) a;
    int64_t hash = 5381;
    int c;

    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

    return hash;
}

/*
 * Functie apelata dupa alocarea unui hashtable pentru a-l initializa.
 */
void initHt(struct Hashtable *ht, int hmax, unsigned int (*hash_func)(void*)) {
    ht->hmax = hmax;
    ht->hash_function = hash_func;
    ht->nodeVec = malloc(hmax * sizeof(struct fakeNode));

    for (int i = 0; i < hmax; i++) {
        ht->nodeVec[i].freq = 0;
        memset(ht->nodeVec[i].key, 0, MAXLENGHTLINE);
    }
}

void put(struct Hashtable *ht, char *key) {
    int index = ht->hash_function(key) % ht->hmax;

    // daca pozitia este goala
    if (ht->nodeVec[index].freq == 0) {
        strncpy(ht->nodeVec[index].key, key, strlen(key));
        ht->nodeVec[index].freq++;
        return;
    }

    // daca pozitia nu e goala dar e acelasi cuvantul
    if (strcmp(ht->nodeVec[index].key, key) == 0) {
        ht->nodeVec[index].freq++;
        return;
    }

    // pana gasesc o pozitie goala
    while (1) {
        index++;

        // daca indexul = nr. maxim de locuri, trebuie sa o ia de la inceput
        if (index == ht->hmax) {
            index = 0;
        }

        if (strcmp(ht->nodeVec[index].key, key) == 0) {
            ht->nodeVec[index].freq++;
            return;
        }

        if (ht->nodeVec[index].freq == 0) {
            strncpy(ht->nodeVec[index].key, key, strlen(key));
            ht->nodeVec[index].freq++;
            return;
        }
    }
}

/*
 * Procedura care elibereaza memoria folosita de toate intrarile din hashtable,
 * dupa care elibereaza si memoria folosita pentru a stoca structura hashtable.
 */
void freeHt(struct Hashtable *ht) {
    free(ht->nodeVec);
    free(ht);
}


int main() {
    char line[MAXLENGHTLINE];
    int count = 0;

    /*
     * Calculez numarul maxim de locuri din hashtbable in functie de numarul de
     * linii din fisier.
     */
    while (fgets(line, sizeof(line), stdin) != NULL) {
        count++;
    }

    fseek(stdin, 0, SEEK_SET);  // inapoi la inceputul fisierlui
    struct Hashtable *wiki = malloc(sizeof(struct Hashtable));
    initHt(wiki, count, hash_function_string);

    while (fgets(line, sizeof(line), stdin) != NULL) {
        line[strlen(line) - 1] = '\0';  // elimin '\n' de la finalul liniei
        put(wiki, line);
    }

    for (int i = 0; i < count; i++) {
        if (wiki->nodeVec[i].freq != 0) {
            printf("%s %d\n", wiki->nodeVec[i].key, wiki->nodeVec[i].freq);
        }
    }

    freeHt(wiki);

    return 0;
}
