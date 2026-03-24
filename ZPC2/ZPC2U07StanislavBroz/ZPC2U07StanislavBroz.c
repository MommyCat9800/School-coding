#include <stdio.h>
#include <string.h>

#define Y 30 // počet řádků souřadnice y=0..Y-1
#define X 80 // počet sloupců souřadnice x=0..X-1

void printCanva(char canva[30][80]) {
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            printf("%c", canva[y][x]);
        }
        printf("\n");
    }
}

void addToCanva(char canva[30][80], int x, int y) {

}

int main() {
    char plocha[Y][X];
    memset(plocha,' ',sizeof plocha);



    printCanva(plocha);
    return 1;
}