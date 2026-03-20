#include <stdbool.h>
#include <stdio.h>
#include "U24"

#define True 1
#define False 0
typedef int Bool;

char vetsi(Datum a,Datum b) {
    return a.den + a.mesic * 100 + a.rok * 10000 > b.den + b.mesic * 100 + b.rok * 10000;
}
char mensi(Datum a,Datum b) {
    return a.den + a.mesic * 100 + a.rok * 10000 < b.den + b.mesic * 100 + b.rok * 10000;
}

void Tridit(Datum arr[],int numD,char (*cmp)(Datum,Datum)) {
    Bool swapped = True;
    while (swapped) {
        swapped = False;
        Datum prev = arr[0];
        for (int i = 1; i < numD; i++) {
            if (!cmp(prev,arr[i])==0) {
                swapped = True;
                arr[i - 1] = arr[i];
                arr[i] = prev;
            }
            prev = arr[i];
        }
    }
}

void Vypsat(const Datum arr[],int numD) {
    for (int i = 0; i < numD; i++) {
        printf("%d.%d.%d",arr[i].den, arr[i].mesic, arr[i].rok);
        if ((i + 1) % 5 == 0) {
            printf("\n");
        } else {
            printf("  ");
        }
    }
    printf("\n");
}

int main(void) {
    Tridit(D,POCET,vetsi);
    Vypsat(D,POCET);
    printf("\n");
    Tridit(D,POCET,mensi);
    Vypsat(D,POCET);
}

