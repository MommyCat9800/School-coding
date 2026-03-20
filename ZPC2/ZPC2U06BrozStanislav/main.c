#include <stdio.h>


// funkcie na vytvorenie tabulky
void addLine(FILE *file) {
    for (int i = 1; i <= 89; i++) {
        fprintf(file, "-");
    }
    fprintf(file, "\n");
}
void addRow(FILE *file, int start) {
    for (int i = start; i < start + 8; i++) {
        if (i != 127) {
            fprintf(file,"|%4d %2X %c ",i,i,i);
        } else {
            fprintf(file,"|%4d %2X   ",i,i);
        }
    }
    fprintf(file,"|\n");
}

void buildTable(FILE *file) {
    addLine(file);
    for (int i = 32; i < 127; i += 8) {
        addRow(file, i);
    }
    addLine(file);
}

// funkcie na vypis tabulky do terminalu
void printTable(FILE *file) {
    char c;
    while ((c = fgetc(file)) != EOF) {
        printf("%c",c);
    }

}


int main(void) {
    // otvorenie suboru na pisanie a ulozenie ukazatela
    const char *filename = "ascii.txt";
    FILE *file = fopen(filename, "w");

    // vytvorenie tabulky a zapisanie do suboru
    buildTable(file);


    // otvorenie suboru na pisanie a ulozenie ukazatela
    fclose(file);
    file = fopen(filename, "r");

    // vypis tabulky do terminalu
    printTable(file);

    fclose(file);
}