#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int inArray(const int board[], int size, int value);
double pow(double base, double exponent);
int randomInRange(int min, int max);

int calculateAdvancedPositions(int currentPosition, int diceNumber, int *specialPositions);
void drawBoard(int board[], int size);
int handleDiceThrow(int bonus);

void printHeader();
void printDeathScreen();
void printWinScreen();
void renderBoard(int playerPosition);

// Integrantes del Grupo:
// - José Benavente
// - Yerko Cisternas
// - Ismael Cabrera
int main() {
  srand(time(NULL));

  int playerPosition = 0;
  int board[50] = {};
  int specialPositions[5] = {2, 4, 8, 16, 32};

  drawBoard(board, 50);

  printHeader();
  renderBoard(playerPosition);

  do {
    int diceNumber = handleDiceThrow(0);
    int advancedPositions = calculateAdvancedPositions(playerPosition, diceNumber, specialPositions);

    playerPosition += advancedPositions;
    renderBoard(playerPosition);

    printf("[SAPO] OBTUVISTE UN %i.\n", diceNumber);
    if (advancedPositions < 0) printf("[SAPO] RETROCEDES %i, HAS TENIDO MALA SUERTE.\n", advancedPositions * -1);
    else printf("[SAPO] AVANZAS %i, HAS TENIDO SUERTE.\n", advancedPositions);

    if (playerPosition == 50) {
      printWinScreen();
      return 0;
    }

    printf("[SAPO] QUEDASTE EN LA POSICION %i.\n\n", playerPosition);

  } while (inArray(board, 50, playerPosition));

  printDeathScreen();

  return 0;
}

void printHeader() {
  printf("======================================== EL JUEGO DEL SAPO ========================================\n");
  printf("- Reglas del juego:\n");
  printf("  1. Si tu casilla es par, avanzas lo que diga el dado.\n");
  printf("  2. Si tu casilla es impar, retrocedes lo que diga el dado.\n");
  printf("  3. Si tu casilla es una potencia de 2, y 2 elevado al numero obtenido en el dado es\n");
  printf("     igual al numero de tu casilla, lanzas otra vez y se suma al primer lanzamiento.\n");
  printf("===================================================================================================\n");
}

void printWinScreen() {
  printf("===================================================================================================\n");
  printf("[SAPO] HAS LLEGADO A LA CASILLA 50!!!!!\n");
  printf("[SAPO] GANASTE EL JUEGO DEL SAPO!!!!\n");
  printf("[SAPO] GRACIAS POR JUGAR!!!!!!!!!!!!!!!!!!!!!!!!!");
  printf("===================================================================================================\n");
}

void printDeathScreen() {
  printf("===================================================================================================\n");
  printf("[SAPO] Te has salido del tablero :(.\n");
  printf("[SAPO] PERDISTE!!!\n");
  printf("[SAPO] F por el sapo.\n");
  printf("===================================================================================================\n");
}

int handleDiceThrow(int bonus) {
  if (bonus) {
    printf("[SAPO] => LANZAS DE NUEVO! HAS OBTENIDO UNA BONIFICACION.\n");
    printf(">>> Presiona ENTER para lanzar el BONUS <<<\n");
  } else printf(">> Presiona ENTER para lanzar el dado <<\n");

  getchar();
  int number = randomInRange(1, 6);
  return number;
}

int calculateAdvancedPositions(int currentPosition, int diceNumber, int *specialPositions) {
  if (currentPosition % 2 == 0) {
    if (inArray(specialPositions, 5, currentPosition) && pow(2, diceNumber) == currentPosition) {
      return diceNumber + handleDiceThrow(1);
    } else return diceNumber;
  } else {
    return -diceNumber;
  }
}

int randomInRange(int min, int max) {
  return (rand() % (max - min + 1)) + min;
}

int inArray(const int board[], int size, int value) {
  for (int i = 0; i <= size; i++) {
    if (board[i] == value) return 1;
  }
  return 0;
}

void drawBoard(int board[], int size) {
  for (int i = 0; i <= size; i++) {
    board[i] = i;
  }
}

double pow(double base, double exponent) {
  double result = 1;
  for (int i = 0; i < exponent; i++) {
    result *= base;
  }
  return result;
}

void renderBoard(int playerPosition) {
  // Experimental
  int boardSquares = 53;
  int boardRows = 3;
  int squaresPerRow = boardSquares / boardRows;

  int topIndex = 0;
  int numberIndex = 0;
  int bottomIndex = 0;

  for (int i = 0; i != boardRows; i++) {
    int tile = 0;

    for (int j = 0; j != 3; j++) {
      for (int k = 0; k != squaresPerRow; k++) {

        switch (tile) {
          case 0:
          case 2:
            if (tile == 0) {
              if (topIndex == playerPosition) printf("|<><>");
              else printf("|****");
              topIndex++;
            } else {
              if (bottomIndex == playerPosition) printf("|<><>");
              else printf("|****");
              bottomIndex++;
            }

            break;
          case 1:
            if (numberIndex == playerPosition) printf("| %s ", "TU");
            else {
              if (numberIndex > 9) printf("| %i ", numberIndex);
              else printf("| 0%i ", numberIndex);
            }
            numberIndex++;

            break;
          default:
            break;
        }
      }

      printf("|\n");
      tile++;
    }
  }
}
