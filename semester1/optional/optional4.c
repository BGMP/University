#include <stdio.h>

float f(float x) {
  if (x > 5) return 3 * (x * x) / (x - 5);
  if (x <= -1) return x * x * x * x;
  else return 10 * (x * x * x) / (x + 1);
}

// Grupo de Trabajo:
// - José Benavente
// - Ismael Cabrera
// - Yerko Cisternas
int main() {
  int a;
  int b;

  do {
    printf("Ingrese el intervalo [a,b] a evaluar en la funcion f(x), tal que a sea menor que b:\n");
    printf("Ingrese a:\n");
    scanf("%i", &a);

    printf("Ingrese b:\n");
    scanf("%i", &b);
  } while (a > b);

  while (a <= b) {
    printf("f(%i) = %f\n", a, f(a));
    a++;
  }
}
