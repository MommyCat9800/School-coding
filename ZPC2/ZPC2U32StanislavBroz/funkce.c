#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deklaracie.h"

int *pole = NULL;
int kapacita = 0;
int pocet = 0;

int Najit(int elem) {
    for (int i = 0; i < pocet; i++) {
        if (elem == pole[i]) {
            return i;
        }
    }
    return -1;
}
bool Pridat(int elem) {
    if (Najit(elem) >= 0) {
        return false;
    }
    if (pocet == kapacita) {
        int *temp = malloc(sizeof(int) * kapacita);
        memcpy(temp, pole, sizeof(int) * pocet);

        if (kapacita == 0) {
            kapacita = 8;
        } else {
            kapacita *= 2;
        }

        pole = malloc(sizeof(int) * kapacita);
        for (int i = 0; i < pocet; i++) {
            pole[i] = temp[i];
        }
        free(temp);
    }
    pole[pocet] = elem;
    pocet++;

    return true;
}
bool Odebrat(int elem) {
    int pos = Najit(elem);
    if (pos < 0) {
        return false;
    }
    pocet--;
    for (int i = pos; i < pocet; i++) {
        pole[i] = pole[i + 1];
    }
    return true;
}