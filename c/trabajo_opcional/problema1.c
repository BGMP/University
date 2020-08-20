#include <stdio.h>

// Grupo de Trabajo:
// - José Benavente
// - Ismael Cabrera
// - Yerko Cisternas
int main() {
  int a;
  int b;

  do {
    printf("Ingrese dos numeros (a y b), ambos disntintos de 0 y con a mayor que b.\n");
    printf("Imprimir los numeros primos entre el:\n");
    scanf("%i", &a);

    printf("y el:\n");
    scanf("%i", &b);
  } while (a <= 0 || b <= 0 || a > b);

  for (int i = a; i < b; i++) {
    if (i == 1) continue;
    int prime = 1;

    for (int j = 2; j < i; j++) {
      if (i % j == 0) prime = 0;
    }

    if (prime) printf("%i\n", i);
  }
}
