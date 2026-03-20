#include <stdio.h>
#include "U23"

#define TRUE 1
#define FALSE 0

void Vyber(const int *input[], int len, Typ type, int output[]) {
    int pocet = 0;
    for (int i = 0; i < len; i++) {
        int rowLen = input[i][0];
        for (int y = 1; y <= rowLen; y++) {
            int vyhovuje = FALSE;
            if (type == VSECHNA) vyhovuje = TRUE;
            else if (type == KLADNA && input[i][y] > 0) vyhovuje = TRUE;
            else if (type == NEZAPORNA && input[i][y] >= 0) vyhovuje = TRUE;
            else if (type == ZAPORNA && input[i][y] < 0) vyhovuje = TRUE

            if (vyhovuje) {
                for (int x = 1; x <= pocet; x++) {
                    if (output[x] == input[i][y]) {
                        vyhovuje = FALSE;
                    }
                }
                if (vyhovuje) {
                    pocet++;
                    output[pocet] = input[i][y];
                }
            }
        }
    }
    output[0] = pocet;
}
void Vypis(int input[]) {
    int n = input[0];
    for (int i = 1; i <= n; i++) {
        printf("%d ", input[i]);
        if (i % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

#include "U23T"

int main(void) {
    T();
}