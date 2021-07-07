#include <stdio.h>

#define MAX_BUFFER 1024

void ingresarCantidadDeNotas();
void leerNotas();
void imprimirNotas();

int n;
double notas[MAX_BUFFER];

int main() {
    ingresarCantidadDeNotas();
    leerNotas();
    imprimirNotas();
}

void ingresarCantidadDeNotas() {
    do {
        printf("Ingresa la cantidad de notas:\n");
        scanf("%i", &n);
    } while (n < 1 || n > MAX_BUFFER);
}

void leerNotas() {
    int i = 0;
    for (; i < n; i++) {
        double nota;

        do {
            printf("Ingresa una nota (%i/%i):\n", i + 1, n);
            scanf("%lf", &nota);
        } while (nota < 1.0 || nota > 7.0);

        notas[i] = nota;
    }
}

void imprimirNotas() {
    int j = 0;
    for (; j < n; j++) {
        printf("Nota %i: %.2f\n", j + 1, notas[j]);
    }
}
