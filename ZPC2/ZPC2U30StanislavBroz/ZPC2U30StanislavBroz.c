#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int prior;
    char jm[15];
} PFronta;

PFronta *PF = NULL;
int capacity = 0;
int count = 0;

void Pridat(int priority, const char *name) {
    if (PF == NULL) {
        capacity = 5;
        PF = (PFronta *)malloc(capacity * sizeof(PFronta));
    } else if (count == capacity) {
        capacity *= 2;
        PF = (PFronta *)realloc(PF, capacity * sizeof(PFronta));
    }

    if (PF == NULL) exit(1);

    PF[count].prior = priority;
    strncpy(PF[count].jm, name, 14);
    PF[count].jm[14] = '\0';
    count++;
}

int Odebrat(char nameOut[]) {
    if (count == 0) return 0;

    int maxIndex = 0;
    for (int i = 1; i < count; i++) {
        if (PF[i].prior > PF[maxIndex].prior) {
            maxIndex = i;
        }
    }

    strcpy(nameOut, PF[maxIndex].jm);

    for (int i = maxIndex; i < count - 1; i++) {
        PF[i] = PF[i + 1];
    }
    count--;

    return 1;
}

int main() {
#include "U30"

    char retrievedName[15];
    int counter = 0;

    while (Odebrat(retrievedName)) {
        printf(" %s", retrievedName);
        counter++;
        if (counter % 5 == 0) printf("\n");
    }

    if (counter % 5 != 0) printf("\n");
    printf(" %d\n", capacity);

    free(PF);
    return 0;
}