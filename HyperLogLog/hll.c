// Copyright 2020 Octavian Torcea

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define m 2048  // 1 << 11

/*
 * Functie de hashing (gasita pe net).
 */
int hashFunction(int n) {
    /*
     * Credits: https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
     */
    n = ((n >> 16) ^ n) * 0x45d9f3b;
    n = ((n >> 16) ^ n) * 0x45d9f3b;
    n = (n >> 16) ^ n;
    return n;
}

int seqLength(int a) {
    if (a == 0) {
        return 1;
    }

    /*
     * Practic trebui sa gasesc lungimea secventei "000...01" de la inceputul
     * numarului, nu numarul de 0.
     */
    int count = 1;

    while (1) {
        if (a % 2 == 0) {
            // daca numarul de divizibil cu 2 inseamna ca are primul bit 0
            count++;
            a = a / 2;
        } else {
            return count;  // am gasit primul bit 1
        }
    }
}

int main(int argc, char *argv[]) {
    int *M = calloc(m, sizeof(int));
    FILE *input = fopen(argv[argc - 1], "r");
    int number = 0;

    while (fscanf(input, "%d", &number) != EOF) {
        int aux = hashFunction(number);

        /*
         * aux % m ---> primii 11 biti
         * aux / m ---> numarul fara primii 11 biti
         */
        if (M[aux % m] < seqLength(aux / m)) {
            M[aux % m] = seqLength(aux / m);
        }
    }

    int E = 0;
    double alfaM = 0.7213 / (1 + 1.079 / m);
    double Z = 0;

    for (int i = 0; i < m; i++) {
        double aux = 1 << M[i];
        Z += (1 / aux);
    }

    Z = 1 / Z;
    E = alfaM * m * m * Z;
    printf("%d\n", E);
    fclose(input);
    free(M);
}
