#include <stdio.h>
#include <stdlib.h>

int main() {

  printf("Generar una matriz con elementos aleatorios...\n\n");

  int rows;
  do {
    printf("Ingresa el numero de filas:\n");
    scanf("%i", &rows);
  } while (rows <= 0);

  int columns;
  do {
    printf("Ingresa el numero de columnas:\n");
    scanf("%i", &columns);
  } while (columns <= 0);


  int matrix[rows][columns];
  int dimension = rows * columns;

  int count = 0;
  for (int i = 0; i < dimension; i++) {
    matrix[i % columns == columns - 1 ? count++ : count][i % columns] = rand() % 50;
  }

  printf("\nMatriz de orden (%ix%i) generada:\n\n", rows, columns);

  count = 0;
  for (int i = 0; i < dimension; i++) {
    printf("%3i ", matrix[count][i % columns]);

    if (i % columns == columns - 1) {
      count++;
      printf("\n");
    }
  }
}
