#include <stdio.h>
#include <string.h>

#define Y 30 // počet řádků souřadnice y=0..Y-1
#define X 80 // počet sloupců souřadnice x=0..X-1

typedef struct crds {
    short x;
    short y;
} Crds;

void printCanva(char canva[30][80]) {
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            printf("%c", canva[y][x]);
        }
        printf("\n");
    }
}

void incCoords(FILE* instrucFile, Crds* CurrCrds) {
    short dx;
    short dy;
    fread(&dx,sizeof(short),1,instrucFile);
    fread(&dy,sizeof(short),1,instrucFile);
    CurrCrds->x = dx;
    CurrCrds->y = dy;
}

void drawLine(Crds* CurrCrds,char canva[30][80] ,FILE* instrucFile) {
    char Char;
    short arr[3];

    fread(&Char,sizeof(char),1,instrucFile);
    fread(&arr,sizeof(short),3,instrucFile);

    short dx = arr[0];
    short dy = arr[1];
    short len = arr[2];
    for (int i = 0; i < len; i++) {
        canva[CurrCrds->y][CurrCrds->x] = Char;
        CurrCrds->x += dx;
        CurrCrds->y += dy;
    }
}

void addToCanva(char canva[30][80]) {
    FILE* instrucFile = fopen("Kresba", "rb");
    char instrucCode;
    Crds CurrCrds;

    while (!feof(instrucFile)) {
        fread(&instrucCode,sizeof(char),1,instrucFile);
        switch (instrucCode) {
            case '1':
                fread(&CurrCrds.x,sizeof(short),1,instrucFile);
                fread(&CurrCrds.y,sizeof(short),1,instrucFile);
                break;
            case '2':
                incCoords(instrucFile,&CurrCrds);
                break;
            case '3':
                drawLine(&CurrCrds,canva,instrucFile);
                break;
            case '4':

        }
    }
}

int main() {
    char plocha[Y][X];
    memset(plocha,' ',sizeof plocha);



    printCanva(plocha);
    return 1;
}