// Torcea Octavian 314CA

#include <stdio.h>
#include <stdlib.h>

int **allocMatrix(int n) {
    int **a, i, j, m;
    a = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        scanf("%d", &m);
        a[i] = (int *)malloc((m + 1) * sizeof(int));
        a[i][0] = m;
        for (j = 1; j <= m; j++) {
            scanf("%x", &a[i][j]);
        }
    }
    return a;
}

void freeMatrix(int **a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
}

double task1(int **map, int n) {
    int i, j, sum = 0, count = 0;
    char *byte;
    double mA = 0;

    // suma tuturor bytes-lor de pe prima linie

    for (i = 1; i <= map[0][0]; i++) {
        byte = (char *)&map[0][i];
        for (j = 0; j < sizeof(map[0][i]); j++) {
            sum += *(byte + j);
            count++;
        }
    }

    // suma ultimilor bytes de pe a doua linie pana la linia n - 1

    for (i = 1; i < n - 1; i++) {
        int aux = map[i][0];
        byte = (char *)&map[i][aux];
        sum += *(byte + sizeof(map[i][0]) - 1);
        count++;
    }

    // suma tuturor bytes-lor de pe ultima linie

    for (i = 1; i <= map[n - 1][0]; i++) {
        byte = (char *)&map[n - 1][i];
        for (j = 0; j < sizeof(map[n - 1][i]); j++) {
            sum += *(byte + j);
            count++;
        }
    }

    // suma primilor bytes de pe a doua linie pana la linia n - 1

    for (i = n - 2; i >= 1; i--) {
        byte = (char *)&map[i][1];
        sum += byte[0];
        count++;
    }

    mA = (double)sum / (double)count;
    return mA;
}

void delChar(int **map, int line, int indexData) {
    char *byte;
    int col = (sizeof(char) * indexData) / 4 + 1;

    // + 1 deoarece in matrice stocarea incepe de la indexul 1

    byte = (char *)(&map[line][col]);
    int index = (sizeof(char) * indexData) % 4 - 1;

    // -1 deoarece indexul primului byte e 0

    *(byte + index) = 0;
}

void delShort(int **map, int line, int indexData) {
    char *byte;
    int col = (sizeof(short) * indexData) / 4 + 1;

    // + 1 deoarece in matrice stocarea incepe de la indexul 1

    byte = (char *)(&map[line][col]);
    int index = (sizeof(short) * indexData) % 4 - 2;

    // -2 deoarece indexul primului byte e 0

    *(byte + index) = 0;
    *(byte + index + 1) = 0;
}

void delInt(int **map, int line, int indexData) {
    char *byte;
    int col = (sizeof(int) * indexData) / 4;
    byte = (char *)(&map[line][col]);
    *(byte) = 0;
    *(byte + 1) = 0;
    *(byte + 2) = 0;
    *(byte + 3) = 0;
}

void swapShort(int **map, int line, int indexData) {
    char *byte;
    int col = (sizeof(short) * indexData) / 4 + 1;
    byte = (char *)(&map[line][col]);
    int index = (sizeof(short) * indexData) % 4;
    int aux = byte[index];
    byte[index] = byte[index + 1];
    byte[index + 1] = aux;
}

void swapInt(int **map, int line, int indexData) {
    char *byte;
    int col = (sizeof(int) * indexData) / 4 + 1;
    byte = (char *)(&map[line][col]);
    int aux = byte[0];
    byte[0] = byte[3];
    byte[3] = aux;
    aux = byte[1];
    byte[1] = byte[2];
    byte[2] = aux;
}

void modifyChar(int **map, int line, int indexData, int new) {
    if (4 * (map[line][0]) < indexData) {
        // alocare de memorie de suplimentara
        map[line] = realloc(map[line], sizeof(int) * ((indexData + 3) / 4 + 1));

        // fBtZ (first byte to zero) are valoarea
        // primului byte ce trebuie sa ia valoarea 0
        char *byte = (char *)&map[line][0];
        int fBtZ = (map[line][0] + 1) * 4;

        // se fac toti octetii suplimentari 0
        for (int i = fBtZ; i < sizeof(int) * ((indexData + 3) / 4 + 1); i++) {
            byte[i] = 0;
        }

        // se modifica si primul el. al matricei ce contoriza nr. de elemente
        map[line][0] = (indexData + 3) / 4;
    }

    // modificare propiu-zisa
    char *byte = (char *)&map[line][(indexData + 3) / 4];
    if (indexData % 4 != 0) {
        byte[(indexData % 4) - 1] = new;
    } else {
        byte[3] = new;
    }
}

void modifyShort(int **map, int line, int indexData, int new) {
    if (2 * (map[line][0]) < indexData) {
        // alocare de memorie de suplimentara
        map[line] = realloc(map[line], sizeof(int) * ((indexData + 1) / 2 + 1));

        char *byte = (char *)&map[line][0];
        int fBtZ = (map[line][0] + 1) * 4;
        for (int i = fBtZ; i < sizeof(int) * ((indexData + 1) / 2 + 1); i++) {
            byte[i] = 0;
        }
        map[line][0] = ((indexData + 1) / 2);
    }

    // modificarea propriu-zisa
    char *byte = (char *)&map[line][((indexData + 1) / 2)];
    char *readByte = (char *)&new;
    if (indexData % 2 == 1) {
        byte[0] = *(readByte + 0);
        byte[1] = *(readByte + 1);
    } else {
        byte[2] = *(readByte + 0);
        byte[3] = *(readByte + 1);
    }
}

void modifyInt(int **map, int line, int indexData, int new) {
    if (map[line][0] < indexData) {
        // alocare de memorie de suplimentara
        map[line] = realloc(map[line], sizeof(int) * (indexData + 1));
        char *byte = (char *)&map[line][0];
        int fBtZ = (map[line][0] + 1) * 4;
        for (int i = fBtZ; i < sizeof(int) * (indexData + 1); i++) {
            byte[i] = 0;
        }
        map[line][0] = indexData;
    }

    // modificarea propiu-zisa
    char *byte = (char *)&map[line][indexData];
    char *readByte = (char *)&new;
    byte[0] = readByte[0];
    byte[1] = readByte[1];
    byte[2] = readByte[2];
    byte[3] = readByte[3];
}

void task2(int **map, int n) {
    int k, i, line, indexData, new;
    char operation[2], dataDimension[2];
    scanf("%d", &k);
    for (i = 0; i < k; i++) {
        scanf("%s%s%d%d", &operation[0], &dataDimension[0], &line, &indexData);
        if (operation[0] == 'M') {
            scanf("%x", &new);
            if (dataDimension[0] == 'C') {
                modifyChar(map, line, indexData, new);
            }
            if (dataDimension[0] == 'S') {
                modifyShort(map, line, indexData, new);
            }
            if (dataDimension[0] == 'I') {
                modifyInt(map, line, indexData, new);
            }
        }
        if (operation[0] == 'D') {
            if (dataDimension[0] == 'C') {
                delChar(map, line, indexData);
            }
            if (dataDimension[0] == 'S') {
                delShort(map, line, indexData);
            }
            if (dataDimension[0] == 'I') {
                delInt(map, line, indexData);
            }
        }
        if (operation[0] == 'S') {
            if (dataDimension[0] == 'S') {
                swapShort(map, line, indexData);
            }
            if (dataDimension[0] == 'I') {
                swapInt(map, line, indexData);
            }
        }
    }
}

void col(int n, int i, int j, int **copy, int **map, int *aux) {
    char *byte = (char *)&copy[i][0];
    if (byte[j] == 0) {
        byte[j] = 1;
        *aux = *aux + 1;
        if (j > 0) {
            col(n, i, j - 1, copy, map, aux);
        }
        if (j < map[i][0] * 4 - 1) {
            col(n, i, j + 1, copy, map, aux);
        }
        if (i > 0 && j < map[i - 1][0] * 4) {
            col(n, i - 1, j, copy, map, aux);
        }
        if (i < n - 1 && j < map[i + 1][0] * 4) {
            col(n, i + 1, j, copy, map, aux);
        }
    }
}

void task3(int n, int **map) {
    int line = 0, collumn = 0, size = 0, aux = 0;
    char *byteA, *byteC;

    // alocare memorie pentru matricea copie
    int **copy = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        copy[i] = (int *)malloc(map[i][0] * sizeof(int));
    }

    // octetii au val. 1 daca in matricea originala au o val. diferita de 0
    // sau 0 daca si in matricea originala aveau tot val. 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < map[i][0]; j++) {
            byteA = (char *)&(map[i][j + 1]);
            byteC = (char *)&(copy[i][j]);
            for (int k = 0; k < 4; k++) {
                if (byteA[k] != 0) {
                    byteC[k] = 1;
                } else {
                    byteC[k] = byteA[k];
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < map[i][0] * 4; j++) {
            col(n, i, j, copy, map, &aux);
            if (aux > size) {
                size = aux;
                line = i;
                collumn = j;
            }
            aux = 0;
        }
    }

    freeMatrix(copy, n);
    printf("%d %d %d\n", line, collumn, size);
}

int main() {
    int n, **galaxy;
    scanf("%d", &n);
    galaxy = allocMatrix(n);
    double mA = task1(galaxy, n);
    task2(galaxy, n);
    printf("task 1\n%0.8lf\ntask 2\n", mA);

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= galaxy[i][0]; j++) {
            printf("%.8X ", galaxy[i][j]);
        }
        printf("\n");
    }

    printf("task 3\n");
    task3(n, galaxy);
    freeMatrix(galaxy, n);
    return 0;
}
