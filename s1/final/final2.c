#include <stdio.h>

int main() {
  int n;

  do {
    printf("Ingresa la cantidad positiva n de numeros Fibonacci que quieres sumar:\n");
    scanf("%i", &n);
  } while (n < 0);

  int i = 0;
  int j = 1;

  int result = 0;
  for (int k = 1; k <= n; k++) {
    result += i;
    int l = i + j;
    i = j;
    j = l;
  }

  printf("El resultado es: %i", result);
  return 0;
}