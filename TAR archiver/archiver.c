// Torcea Octavian 314CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// functie care converteste permisiunile in octal
int convertPermissions(char tok[]) {
    int realPerm = 0;

    // codul ascii pentru r e 114
    // codul ascii pentru w e 119
    // codul ascii pentru x e 120

    if (tok[1] == 114) {
        realPerm += 400;
    }
    if (tok[2] == 119) {
        realPerm += 200;
    }
    if (tok[3] == 120) {
        realPerm += 100;
    }
    if (tok[4] == 114) {
        realPerm += 40;
    }
    if (tok[5] == 119) {
        realPerm += 20;
    }
    if (tok[6] == 120) {
        realPerm += 10;
    }
    if (tok[7] == 114) {
        realPerm += 4;
    }
    if (tok[8] == 119) {
        realPerm += 2;
    }
    if (tok[9] == 120) {
        realPerm += 1;
    }
    return realPerm;
}

// functie pentru a face suma tuturor octetilor din header
int checksum(char a[512]) {
    int checksum = 0;
    for (int i = 0; i < 512; i++) {
        checksum += (a[i]);
    }
    return checksum;
}

// functie pentru a converti data in secunde trecute de la 1.1.1970
long convertDate(char ymd[20], char hms[20]) {
    int year, month, day, hour, minute, second;
    char delimYMD[2] = "-";
    char delimHMS[3] = ":.";
    char *tok;

    tok = strtok(ymd, delimYMD);
    sscanf(tok, "%d", &year);
    tok = strtok(NULL, delimYMD);
    sscanf(tok, "%d", &month);
    tok = strtok(NULL, delimYMD);
    sscanf(tok, "%d", &day);

    tok = strtok(hms, delimHMS);
    sscanf(tok, "%d", &hour);
    tok = strtok(NULL, delimHMS);
    sscanf(tok, "%d", &minute);
    tok = strtok(NULL, delimHMS);
    sscanf(tok, "%d", &second);

    struct tm time;
    time_t timeOfDay;
    time.tm_year = year - 1900;
    time.tm_mon = month - 1;
    time.tm_mday = day;
    time.tm_hour = hour;
    time.tm_min = minute;
    time.tm_sec = second;
    time.tm_isdst = -1;
    timeOfDay = mktime(&time);
    return timeOfDay;
}

union record {
    char charptr[512];
    struct header {
        char name[100];
        char mode[8];
        char uid[8];
        char gid[8];
        char size[12];
        char mtime[12];
        char chksum[8];
        char typeflag;
        char linkname[100];
        char magic[8];
        char uname[32];
        char gname[32];
        char devmajor[8];
        char devminor[8];
    } header;
};

void create(char nume_arhiva[], char nume_director[]) {
    union record record;

    // se scrie in header doar NULL
    memset(record.charptr, '\0', 512);

    char null[512], lineF[512], lineUM[512], date1[20], date2[20], numeR[512];
    memset(null, '\0', 512);
    char delim[4] = " \n", delimU[2] = ":";
    int size, Duid, Dgid, sum, toAdd, ok = 1, exists = 0;

    FILE *files = fopen("files.txt", "r");
    FILE *usermap = fopen("usermap.txt", "r");

    // se parcurge acum files.txt linie cu linie
    while (fgets(lineF, 512, files)) {
        // se memoreaza file persmissions in mode
        char *tok =  strtok(lineF, delim);
        sprintf(record.header.mode, "%d", convertPermissions(tok));

        // se sare peste campul no_links
        tok = strtok(NULL, delim);

        // se memoreaza numele utilizatorului
        tok = strtok(NULL, delim);
        strcpy(record.header.uname, tok);

        // se memoreaza numele grupului
        tok = strtok(NULL, delim);
        strcpy(record.header.gname, tok);

        // se memoreaza dimensiunea fisierului
        tok = strtok(NULL, delim);
        sscanf(tok, "%d", &size);
        sprintf(record.header.size, "%o", size);

        // se memoreaza campul last_change_time
        tok = strtok(NULL, delim);
        strcpy(date1, tok);
        tok = strtok(NULL, delim);
        strcpy(date2, tok);
        tok = strtok(NULL, delim);

        // se memoreazaz numele fisierului
        tok = strtok(NULL, delim);
        strcpy(record.header.name, tok);
        strcpy(numeR, nume_director);
        strcat(numeR, tok);
        strcpy(record.header.linkname, record.header.name);

        // se scrie in magic "GNUtar "
        strcpy(record.header.magic, "GNUtar ");

        FILE *toArchive;
        // se verifica daca se poate deschide fisierul
        if ((toArchive = fopen(numeR, "rb")) == NULL) {
            printf("> Failed!\n");
            ok = 0;
            break;
        } else {
            while (!exists) {
                fgets(lineUM, 512, usermap);
                tok = strtok(lineUM, delimU);

                // se cauta uid si gid corespunzator userului
                if (strcmp(record.header.uname, tok) == 0) {
                    exists = 1;
                    tok = strtok(NULL, delimU);
                    tok = strtok(NULL, delimU);
                    sscanf(tok, "%d", &Duid);
                    sprintf(record.header.uid, "%o", Duid);
                    tok = strtok(NULL, delimU);
                    sscanf(tok, "%d", &Dgid);
                    sprintf(record.header.gid, "%o", Dgid);
                }
            }

            // se memoreaza data in secunde
            sprintf(record.header.mtime, "%lo", convertDate(date1, date2));

            // se introduce in chksum doar BLANK
            strcpy(record.header.chksum, "        ");

            // apoi se calculeaza suma octetilor
            sum = checksum(record.charptr);

            // se pune doar NULL in chksum
            memset(record.header.chksum, '\0', 8);

            // se memoreaza suma
            sprintf(record.header.chksum, "%o", sum);

            // se va crea "arhiva" si se introduce headerul fisierului
            FILE *archive = fopen(nume_arhiva, "ab");
            fwrite(&record, sizeof(record), 1, archive);

            // se introduc datele din fisier in arhiva
            const int Nsize = size;
            char toWrite[Nsize];
            fread(toWrite, size, 1, toArchive);
            fwrite(&toWrite, size, 1, archive);

            // se introduc NULL-uri incat sa se ajunga la un multiplu de 512
            toAdd = 512 - size % 512;
            fwrite(&null, toAdd, 1, archive);
            fclose(archive);
            fclose(toArchive);
        }

        // se reinitializeaza headerul
        memset(record.charptr, '\0', 512);
    }

    // daca arhiva s-a creat se introduc la final 512 NULL-uri
    if (ok == 1) {
        FILE *archive = fopen(nume_arhiva, "ab");
        fwrite(&null, 512, 1, archive);
        fclose(archive);
        printf("> Done!\n");
    }
    fclose(files);
    fclose(usermap);
}

void list(char nume_arhiva[]) {
    FILE *archive;

    // se verifica daca exista arhiva
    if ((archive = fopen(nume_arhiva, "rb")) == NULL) {
        printf("> File not found!\n");
    } else {
        char nume[100], sizeO[12];
        int size;

        // se citeste numele primului fisier
        fread(nume, 100, 1, archive);

        // atat timp cat nu s-a ajuns la partea de final a arhivei de 512 NULL
        while (strcmp(nume, "\0") != 0) {
            printf("> %s\n", nume);
            fseek(archive, 24, SEEK_CUR);
            fread(sizeO, 12, 1, archive);
            sscanf(sizeO, "%o", &size);

            // se sare peste partea din arhiva cu datele fisierului
            fseek(archive, 512 - 136 + size + 512 - size % 512, SEEK_CUR);

            // se citeste un alt nume de fisier
            fread(nume, 100, 1, archive);
        }
        fclose(archive);
    }
}

void extract(char nume_fisier[], char nume_arhiva[]) {
    int ok1 = 0, ok2 = 0;
    FILE *archive;

    // se verifica daca exista arhiva
    if ((archive = fopen(nume_arhiva, "rb")) == NULL) {
        ok2 = 1;
        printf("> File not found!\n");
    } else {
        char nume[100], sizeO[12];
        int size;
        fread(nume, 100, 1, archive);

        // se verifica daca exista fisierul in arhiva
        while ((strcmp(nume, "\0") != 0) && ok1 == 0) {
            if (strcmp(nume, nume_fisier) == 0) {
                ok1 = 1;
                char numeFisier[110] = "extracted_";
                strcat(numeFisier, nume);

                // se va crea noul fisier
                FILE *extracted = fopen(numeFisier, "wb");

                // se copiaza din arhiva doar datele, sarindu-se peste header
                fseek(archive, 24, SEEK_CUR);
                fread(sizeO, 12, 1, archive);
                sscanf(sizeO, "%o", &size);
                fseek(archive, 512 - 136, SEEK_CUR);
                const int Nsize = size;
                char toWrite[Nsize];
                fread(toWrite, size, 1, archive);
                fwrite(&toWrite, size, 1, extracted);
                fclose(extracted);
            } else {
                fseek(archive, 24, SEEK_CUR);
                fread(sizeO, 12, 1, archive);
                sscanf(sizeO, "%o", &size);
                fseek(archive, 512 - 136 + size + 512 - size % 512, SEEK_CUR);
                fread(nume, 100, 1, archive);
            }
        }
        fclose(archive);
    }
    if (ok1) {
        printf("> File extracted!\n");
    } else if (!ok2) {
        printf("> File not found!\n");
    }
}

int main() {
    char command[512];
    char *token;
    char delim[2] = " ";
    char nume_arhiva[512];
    char nume_director[512];
    char nume_fisier[512];

    // pana cand se primeste comanda "exit"
    while (1) {
        fgets(command, 512, stdin);
        command[strlen(command) - 1] = '\0';
        if (!strcmp(command, "exit")) {
            break;
        }
        token = strtok(command, delim);

        // comanda "create" trebuie sa aiba fix 2 argumente
        // altfel se va afisa "> Wrong command!"
        if (strcmp(token, "create") == 0) {
            token = strtok(NULL, delim);
            if (token == NULL) {
                printf("> Wrong command!\n");
            } else {
                strcpy(nume_arhiva, token);
                token = strtok(NULL, delim);
                if (token == NULL) {
                    printf("> Wrong command!\n");
                } else {
                    strcpy(nume_director, token);
                    token = strtok(NULL, delim);
                    if (token != NULL) {
                        printf("> Wrong command!\n");
                    } else {
                        create(nume_arhiva, nume_director);
                    }
                }
            }

        // comanda "list" trebuie sa aiba fix un argument
        // altfel se va afisa "> Wrong command!"
        } else if (strcmp(token, "list") == 0) {
            token = strtok(NULL, delim);
            if (token == NULL) {
                printf("> Wrong command!\n");
            } else {
                strcpy(nume_arhiva, token);
                token = strtok(NULL, delim);
                if (token != NULL) {
                    printf("> Wrong command!\n");
                } else {
                    list(nume_arhiva);
                }
            }

        // comanda "extract" trebuie sa aiba fix 2 argumente
        // altfel se va afisa "> Wrong command!"
        } else if (strcmp(token, "extract") == 0) {
            token = strtok(NULL, delim);
            if (token == NULL) {
                printf("> Wrong command!\n");
            } else {
                strcpy(nume_fisier, token);
                token = strtok(NULL, delim);
                if (token == NULL) {
                    printf("> Wrong command!\n");
                } else {
                    strcpy(nume_arhiva, token);
                    token = strtok(NULL, delim);
                    if (token != NULL) {
                        printf("> Wrong command!\n");
                    } else {
                        extract(nume_fisier, nume_arhiva);
                    }
                }
            }
        } else {
            printf(">Wrong command!\n");
        }
    }
    return 0;
}
