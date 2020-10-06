#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));

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
    int row = count;
    int column = i % columns;

    matrix[row][column] = rand() % 50;

    if (i % columns == columns - 1) {
      count++;
    }
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
