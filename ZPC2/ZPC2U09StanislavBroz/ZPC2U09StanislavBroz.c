#include <stdio.h>
#include <string.h>
#include "U09"

#define True 1
#define False 0

int jePrestupny(const unsigned rok) {
    return (rok % 4 == 0 && (rok % 100 != 0 || rok % 400 == 0));
}

int isin(const char string[], const char *arr[]) {
    for (int i = 0; i < 24; i++) {
        if (!strcmp(string, arr[i])) return True;
    } return False;
}

int main(void) {
    FILE* dates = fopen("Datum.txt", "r");
    char err[2][22] = {"chybny den nebo mesic","neni prestupny rok"};


    char date[20];
    while (fgets(date, sizeof(date), dates)) {
        date[strcspn(date, "\n")] = 0;
        if (strlen(date) == 0) continue;


        int stringForm = False;
        unsigned d, r, m;
        char mmm[10];

        if (sscanf(date, "%u. %u. %u", &d, &m, &r) == 3) {
            stringForm = False;
        }
        else if (sscanf(date, "%u. %s %u", &d, mmm, &r) == 3) {
           stringForm = True;
        }
        if (!stringForm) {
            // ak mesiac nieje z rozsahu <1,12>
            // ak den nieje v rozsahu <1,dny[m-1]>
            if (m < 1 || m > 12 || d < 1 || d > dny[m-1]) {
                printf("%d. %d. %d %s\n",d,m,r,err[0]);
            }
            else if ((d == 29 && m == 2) && !jePrestupny(r)) {
                printf("%d. %d. %d %s\n",d,m,r,err[1]);
            }
        } else {
            if (!isin(mmm, mesice)) {
                printf("%d. %s %d %s\n",d,mmm,r,err[0]);
            } else if ((!strcmp(mmm, "unor") || !strcmp(mmm, "unora")) && d == 29 && !jePrestupny(r)) {
                printf("%d. %s %d %s\n",d,mmm,r,err[1]);
            }
        }

    }



    return 0;
}