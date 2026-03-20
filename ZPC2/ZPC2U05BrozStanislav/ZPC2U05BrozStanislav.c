#include <stdio.h>
#include <stdarg.h>
#include <math.h>

double kalkulator(const char* vyraz, ...) {
    double zasobnik[20];
    int top = 0;

    va_list args;
    va_start(args, vyraz);

    for (int i = 0; vyraz[i] != '\0'; i++) {
        switch (vyraz[i]) {
            case 'i':
                zasobnik[top++] = (double)va_arg(args, int);
                break;
            case 'd':
                zasobnik[top++] = va_arg(args, double);
                break;
            case '+':
                top -= 2;
                zasobnik[top] = zasobnik[top] + zasobnik[top + 1];
                top++;
                break;
            case '-':
                top -= 2;
                zasobnik[top] = zasobnik[top] - zasobnik[top + 1];
                top++;
                break;
            case '*':
                top -= 2;
                zasobnik[top] = zasobnik[top] * zasobnik[top + 1];
                top++;
                break;
            case '/':
                top -= 2;
                zasobnik[top] = zasobnik[top] / zasobnik[top + 1];
                top++;
                break;
            case 's':
                top--;
                zasobnik[top] = zasobnik[top] * zasobnik[top];
                top++;
                break;
            case 'r':
                top--;
                zasobnik[top] = sqrt(zasobnik[top]);
                top++;
                break;
        }
    }
    va_end(args);
    return zasobnik[top - 1];
}


void main() {
    const char *E="ii+rdsis-*i/";
    double vysledok = kalkulator(E,7,2,2.5,4,5);
    printf("%g\n",vysledok);
}