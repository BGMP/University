#include <stdio.h>

// Grupo de Trabajo:
// - José Benavente
// - Ismael Cabrera
// - Yerko Cisternas
int main() {
  int n;

  do {
    printf("Ingrese un numero positivo n:\n");
    scanf("%i", &n);
  } while (n < 0);

  int result = 0;
  for (int i = n; i > 0; i /= 10) {
    result += i % 10;
  }

  printf("La suma de los digitos es: %i", result);
}
