#include <stdio.h>

float f(float x) {
  if (x > 10) return ((x * x * x) + 2 * x - 5) / ((x - 10) * (x - 10));
  if (x <= 5) return ((x * x * x) - 10 * x) / ((x * x) + 1);
  else return (2 * (x * x) - 5 * x) / (x - 5);
}

int main() {
  int n;

  do {
    printf("Ingrese la cantidad de numeros que desea evaluar en la funcion:\n");
    scanf("%i", &n);
  } while (n < 1);

  while (n > 0) {
    float x;

    printf("Ingrese el valor de x:\n");
    scanf("%f", &x);

    printf("f(%f) = %f\n", x, f(x));

    n--;
  }

  return 0;
}