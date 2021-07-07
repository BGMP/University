#include <stdio.h>

void f(int a, int n) {
    int resultado = 0;

    while (a <= n) {
        resultado = resultado + ((a + 3) / (2 * a - 1));
        a++;
    }

    printf("El resultado es: %i\n", resultado);
}

int main() {
    int a;

    do {
        printf("Ingrese a:\n");
        scanf("%i", &a);
    } while (a < 0);

    int n;
    do {
        printf("Ingrese n (debe ser mayor que %i): \n", a);
        scanf("%i", &n);
    } while (n <= a);

    f(a, n);
}
