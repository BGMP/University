#include <stdio.h>

int factorialOf(int target) {
  if (target < 0) return -1;

  int factorial = 1;
  for (int i = 1; i <= target; i++) {
    factorial *= i;
  }

  return factorial;
}

int main() {
  int index = 0;
  int limit;

  do {
    printf("Valores a ingresar en el array (Maximo 10):\n");
    scanf("%i", &limit);
  } while (limit <= 0 || limit > 10);

  int numbers[limit];

  do {
    int i;
    printf("Ingresa un valor entero positivo en el array:\n");
    scanf("%i", &i);

    if (i < 0) {
      printf("Valor invalido.\n");
      continue;
    }

    numbers[index] = i;

    index++;
  } while (index < limit);

  int result = 0;
  for (int i = 0; i < limit; i++) {
    result += factorialOf(numbers[i]);
  }

  printf("El resultado de la suma de los %i factoriales es: %i", limit, result);

  return 0;
}