// Copyright 2020 Octavian Torcea

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMAX 2000000
#define MAXLINELENGTH 9

int main() {
    int *vfreq = calloc((NMAX + 1), sizeof(int));
    char line[MAXLINELENGTH];
    int new = 0;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        new = atoi(line);
        vfreq[new]++;
    }

    for (int i = 0; i <= NMAX; i++) {
        if (vfreq[i] != 0) {
            printf("%d %d\n", i, vfreq[i]);
        }
    }

    free(vfreq);
    return 0;
}
