#include <stdio.h>
#include "deklaracie.h"


void Vypsat() {
    for (int i = 0; i < pocet - 1; i++) {
        for (int j = 0; j < pocet - i - 1; j++) {
            if (pole[j] > pole[j + 1]) {
                int temp = pole[j];
                pole[j] = pole[j + 1];
                pole[j + 1] = temp;
            }
        }
    }
    printf("Prvky v poli:\n");
    for (int i = 0; i < pocet; i++) {
        printf("%d\t", pole[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n\nAktualna velkost pola (kapacita): %d\n", kapacita);
    printf("Pocet ulozenych prvkov: %d\n", pocet);
}

int main() {
    FILE *fPridat = fopen("pridat", "r");
    FILE *fOdebrat = fopen("odebrat", "r");
    int hodnota;

    while (fscanf(fPridat, "%d", &hodnota) == 1) {
        Pridat(hodnota);
    }
    fclose(fPridat);

    while (fscanf(fOdebrat, "%d", &hodnota) == 1) {
        Odebrat(hodnota);
    }
    fclose(fOdebrat);

    Vypsat();

    return 0;
}