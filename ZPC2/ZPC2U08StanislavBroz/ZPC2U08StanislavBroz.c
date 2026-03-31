#include <stdio.h>
#include <string.h>

typedef enum { MUZ=1,ZENA } Pohlavi;
typedef struct { char j[12]; Pohlavi p; } Jmeno;
Jmeno J[134];

int insert(Jmeno name, int maxIndex) {
    for (int i = 0; i < maxIndex; i++) {
        if (!strcmp(J[i].j,name.j)) return 0;
    }

    J[maxIndex] = name;
    for (int i = maxIndex; i > 0; i--) {
        if (strcmp(J[i].j,J[i-1].j) < 0) {
            Jmeno temp = J[i-1];
            J[i-1] = J[i];
            J[i] = temp;
        }
    }
    return 1;
}

void readNames(FILE* Names) {
    char nameLen;
    Jmeno currName;
    int i = 0;


    while (fread(&nameLen, sizeof(char), 1, Names) == 1) {
        if (feof(Names)) {
            return;
        }
        if (nameLen > 50) {
            currName.p = ZENA;
            nameLen -= 50;
        } else {
            currName.p = MUZ;
        }
        fread(currName.j,sizeof(char),nameLen,Names);
        currName.j[(int)nameLen] = '\0';
        if (insert(currName,i)) i++;
    }
}

void printNames(Pohlavi p) {
    int printed = 0;
    for (int i = 0; i < 134; i++) {
        if (J[i].p == p) {
            printf("%s ",J[i].j);
            printed++;
            if (printed == 10) {
                printf("\n");
                printed = 0;
            }
        }
    }
    if (printed != 10) printf("\n");
    printf("\n");
}

int main(void) {
    FILE* Names = fopen("Jmena","rb");
    readNames(Names);

    printNames(ZENA);
    printNames(MUZ);
    fclose(Names);

    return 0;
}