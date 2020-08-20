#include <stdio.h>

// Grupo de Trabajo:
// - José Benavente
// - Ismael Cabrera
// - Yerko Cisternas
int main() {
  int n;

  do {
    printf("Ingresa la cantidad positiva n de numeros Fibonacci que quieres recibir:\n");
    scanf("%i", &n);
  } while (n < 0);

  int i = 0;
  int j = 1;

  for (int k = 1; k <= n; k++) {
    printf("%i\n", i);
    int l = i + j;
    i = j;
    j = l;
  }
}
