#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#pragma ide diagnostic ignored "cert-msc32-c"
#pragma ide diagnostic ignored "cert-msc30-c"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BUFFER 1024

/**
 * A word hidden in the soup.
 */
typedef struct WordEntry {
    int row;
    int column;
    char *word;
} WordEntry;

/**
 * The soup itself.
 */
typedef struct Soup {
    int size;
    int totalWords;
    char matrix[MAX_BUFFER][MAX_BUFFER];
    WordEntry *entries[MAX_BUFFER];
} Soup;

/** Foundation **/
void readWords(Soup *soup);

void hyphenateSoup(Soup *soup);

void placeWords(Soup *soup);

void placeRandomChars(Soup *soup);

int placeWord(Soup *soup, WordEntry *entry, int row, int column);

int tryVerticalWordPlacement(Soup *soup, WordEntry *entry, int row, int column);

int tryHorizontalWordPlacement(Soup *soup, WordEntry *entry, int row, int column);

/** Rendering **/
void renderSoup(Soup *soup);

void renderSpacer(int length);

/** Utils **/
int readInt(int min, int max);

void readAlphaString(char *string, int min, int max);

int stringIsAlpha(char *string);

int randomInRange(int min, int max);

char randomUppercase();

void toUppercaseStr(char *word);

int main() {
  srand(time(NULL));

  Soup *soup = malloc(sizeof(Soup));
  for (int i = 0; i < MAX_BUFFER; i++) {
    soup->entries[i] = NULL;
  }

  printf("[INFO]: Ingresa el porte de la sopa de letras (n), para asi crear una sopa de (n x n):\n");
  soup->size = readInt(1, MAX_BUFFER);

  printf("[INFO]: Ingresa la cantidad de palabras que tendra la sopa de letras (ej: 2, 3, 4, etc):\n");
  soup->totalWords = readInt(2, soup->size);

  readWords(soup);

  printf("\n");
  printf("[INFO]: Generando sopa de letras...\n");
  printf("\n");

  hyphenateSoup(soup);
  placeWords(soup);
  placeRandomChars(soup);

  renderSoup(soup);

  printf("\n");
  printf("[INFO]: Puedes equivocarte hasta 3 veces.\n");
  printf("[INFO]: Ingresa una palabra encontrada:\n");

  int foundWords = 0;
  int mistakes = 0;
  int exists;
  clock_t start = clock();

  char *guess = malloc(MAX_BUFFER);
  while (foundWords != soup->totalWords) {
    if (mistakes > 3) {
      printf("\n");
      printf("!!!!!\n");
      printf("[INFO]: Perdiste! Cometiste mas de 3 errores :(\n");
      printf("!!!!!\n");

      break;
    }

    readAlphaString(guess, 0, MAX_BUFFER);

    exists = 0;
    for (int i = 0; i < soup->totalWords; i++) {
      if (strcmp(guess, soup->entries[i]->word) == 0) {
        exists = 1;
        foundWords++;
        printf("[INFO]: Has encontrado una palabra de la sopa! Origen: [%i, %i] (%i/%i)\n",
               soup->entries[i]->row,
               soup->entries[i]->column,
               foundWords,
               soup->totalWords
        );

        break;
      }
    }

    if (!exists) {
      int lives = 3 - mistakes;
      printf("[INFO]: Esa palabra no esta en la sopa! Sigue intentando! Te %s %i %s!\n",
             lives == 1 ? "queda" : "quedan",
             lives,
             lives == 1 ? "vida" : "vidas"
      );
      mistakes++;
    }
  }

  if (foundWords == soup->totalWords) {
    clock_t end = clock();
    float seconds = (float) (end - start) / CLOCKS_PER_SEC;

    printf("\n");
    printf("!!!!!\n");
    printf("[INFO]: Has encontrado todas las palabras! Gracias por jugar!\n");
    printf("[INFO]: Tiempo transcurrido: %.2f segundos.\n", seconds);
    printf("!!!!!\n");
  }

  for (int i = 0; i < soup->totalWords; i++) {
    free(soup->entries[i]->word);
    free(soup->entries[i]);
  }

  free(soup);

  return 0;
}

void readWords(Soup *soup) {
  for (int i = 0; i < soup->totalWords; i++) {
    printf("[INFO]: Ingresa una palabra (%i/%i):\n", i + 1, soup->totalWords);

    WordEntry *entry = malloc(sizeof(entry));
    entry->word = malloc(sizeof(char) * MAX_BUFFER);

    readAlphaString(entry->word, 2, soup->size);
    soup->entries[i] = entry;
  }
}

void hyphenateSoup(Soup *soup) {
  for (int i = 0; i < soup->size; i++) {
    for (int j = 0; j < soup->size; j++) {
      soup->matrix[i][j] = '-';
    }
  }
}

void placeRandomChars(Soup *soup) {
  for (int i = 0; i < soup->size; i++) {
    for (int j = 0; j < soup->size; j++) {
      if (soup->matrix[i][j] == '-') {
        soup->matrix[i][j] = randomUppercase();
      }
    }
  }
}

void placeWords(Soup *soup) {
  for (int i = 0; i < soup->totalWords; i++) {
    int placed = 0;
    WordEntry *entry = soup->entries[i];

    int row = 0;
    int column = 0;
    while (!placed) {
      row = randomInRange(0, soup->size);
      column = randomInRange(0, soup->size);

      placed = placeWord(soup, entry, row, column);
    }

    entry->row = row;
    entry->column = column;
  }
}

int placeWord(Soup *soup, WordEntry *entry, int row, int column) {
  if (randomInRange(0, 1)) return tryVerticalWordPlacement(soup, entry, row, column);
  else return tryHorizontalWordPlacement(soup, entry, row, column);
}

int tryVerticalWordPlacement(Soup *soup, WordEntry *entry, int row, int column) {
  int canPlace = 1;
  int canPlaceReverse = 1;
  int overlap = 0;

  if (row + 1 < strlen(entry->word)) { // Word doesn't fit from the random position vertically.
    return 0;
  } else {
    int i = row;
    for (int j = strlen(entry->word) - 1; j >= 0; j--) {
      if (soup->matrix[i][column] != '-') {
        if (soup->matrix[i][column] == entry->word[j]) {
          overlap++;
          if (overlap > 1) {
            canPlace = 0;
            break;
          }
        } else canPlace = 0;
      }

      i--;
    }

    if (canPlace) canPlaceReverse = 0;
    else {
      i = row;
      for (int j = 0; j <= strlen(entry->word) - 1; j++) {
        if (soup->matrix[i][column] != '-') {
          if (soup->matrix[i][column] == entry->word[j]) {
            overlap++;
            if (overlap > 1) {
              canPlaceReverse = 0;
            } else {
            }
          } else canPlaceReverse = 0;
        }

        i--;
      }
    }
  }

  if (canPlace) {
    int i = row;
    for (int j = strlen(entry->word) - 1; j >= 0; j--) {
      soup->matrix[i][column] = entry->word[j];
      i--;
    }
  }

  if (canPlaceReverse) {
    int i = row;
    for (int j = 0; j <= strlen(entry->word) - 1; j++) {
      soup->matrix[i][column] = entry->word[j];
      i--;
    }
  }

  return canPlace || canPlaceReverse;
}

int tryHorizontalWordPlacement(Soup *soup, WordEntry *entry, int row, int column) {
  int canPlace = 1;
  int canPlaceReverse = 1;
  int overlap = 0;

  if (column + 1 < strlen(entry->word)) { // Word doesn't fit from the random position, horizontally.
    return 0;
  } else {
    int i = column;
    for (int j = strlen(entry->word) - 1; j >= 0; j--) {
      if (soup->matrix[row][i] != '-') {
        if (soup->matrix[row][i] == entry->word[j]) {
          overlap++;
          if (overlap > 1) {
            canPlace = 0;
            break;
          }
        } else canPlace = 0;
      }

      i--;
    }

    if (canPlace) canPlaceReverse = 0;
    else {
      i = column;
      for (int j = 0; j <= strlen(entry->word) - 1; j++) {
        if (soup->matrix[row][i] != '-') {
          if (soup->matrix[row][i] == entry->word[j]) {
            overlap++;
            if (overlap > 1) {
              canPlaceReverse = 0;
            } else {
            }
          } else canPlaceReverse = 0;
        }

        i--;
      }
    }
  }

  if (canPlace) {
    int i = column;
    for (int j = strlen(entry->word) - 1; j >= 0; j--) {
      soup->matrix[row][i] = entry->word[j];
      i--;
    }
  }

  if (canPlaceReverse) {
    int i = column;
    for (int j = 0; j <= strlen(entry->word) - 1; j++) {
      soup->matrix[row][i] = entry->word[j];
      i--;
    }
  }

  return canPlace || canPlaceReverse;
}

void renderSoup(Soup *soup) {
  renderSpacer(soup->size);

  for (int i = 0; i < soup->size; i++) {
    printf("|| ");

    for (int j = 0; j < soup->size; j++) {
      printf("%3c", soup->matrix[i][j]);
    }

    printf("   ||");
    printf("\n");
  }

  renderSpacer(soup->size);
}

void renderSpacer(int length) {
  printf("=|==");
  for (int i = 0; i < length; i++) printf("===");
  printf("==|=");
  printf("\n");
}

/**
 * Asks for an integer to be input, filtering until it receives a valid one.
 *
 * @param min The minimum number this function will return from reading. -1 for unlimited.
 * @param max The maximum number this function will return from reading. -1 for unlimited.
 *
 * @return The integer read from input.
 */
int readInt(int min, int max) {
  float input;
  int status = scanf("%f", &input);
  int garbage;

  while (status != 1 || (input < min && min != -1) || (input > max && max != -1)) {
    while ((garbage = getchar()) != EOF && garbage != '\n');

    if (min == -1) printf("[ERROR]: Numero invalido! Este debe ser a lo mas %i.\n", max);
    else if (max == -1) printf("[ERROR]: Numero invalido! Este debe ser a lo menos %i.\n", min);
    else printf("[ERROR]: Numero invalido! Este debe ser a lo menos %i, y a lo mas %i.\n", min, max);

    status = scanf("%f", &input);
  }

  if (input != (int) input) printf("[WARNING] El decimal %.1f ha sido truncado a %i.\n", input, (int) input);

  return (int) input;
}

/**
 * Asks for a string to be input, filtering until it receives a valid, alpha-only one.
 *
 * @param string The pointer to where the array read from input will statically be copied to.
 * @param min The minimum number of characters this function will return from reading. -1 for unlimited.
 * @param max The maximum number of characters this function will return from reading. -1 for unlimited.
 *
 * @return The integer read from input.
 */
void readAlphaString(char *string, int min, int max) {
  char *word = malloc(sizeof(char) * max);
  scanf("%s", word);

  while (!stringIsAlpha(word)) {
    printf("[ERROR]: Palabra invalida: %s\n", word);
    scanf("%s", word);
  }

  while (strlen(word) > max) {
    printf("[ERROR]: Palabra demasiado larga: %s\n", word);
    printf("[ERROR]: La cantidad maxima de caracteres es de %i.\n", max);
    scanf("%s", word);
  }

  while (strlen(word) < min) {
    printf("[ERROR]: Palabra demasiado corta: %s\n", word);
    printf("[ERROR]: La cantidad minima de caracteres es de %i.\n", min);
    scanf("%s", word);
  }

  toUppercaseStr(word); // All words should be uppercase.

  strcpy(string, word);
}

int stringIsAlpha(char *string) {
  int valid = 1;

  for (int i = 0; i < strlen(string); i++) {
    if (!isalpha(string[i]) && string[i] != '\0') {
      valid = 0;
    }
  }

  return valid;
}

int randomInRange(int min, int max) {
  return (rand() % (max - min + 1)) + min;
}

char randomUppercase() {
  return 65 + rand() % 26;
}

void toUppercaseStr(char *word) {
  for (int i = 0; i < strlen(word); i++) {
    word[i] = toupper(word[i]);
  }
}

#pragma clang diagnostic pop
