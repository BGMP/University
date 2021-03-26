#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SHEETS 100
#define MAX_BUFFER 1024

typedef struct Person {
    char *name;
    char *fatherLastName;
    char *motherLastName;
    int rutNumber;
    char rutVerifier;
    char *gender;
    int birthYear;
} Person;

typedef struct Sheet {
    int number;
    Person *person;
} Sheet;

typedef struct SheetRecord {
    int sheetCount;
    Sheet *sheets[];
} SheetRecord;

SheetRecord *sheetRecord;

void printSheets();
int readInt(int min, int max);
int isValidRUT(int rutNumber, char rutVerifier);

int main() {
    sheetRecord = malloc(sizeof(SheetRecord));

    printf("Numero de fichas que desea ingresar:\n");
    sheetRecord->sheetCount = readInt(1, MAX_SHEETS);

    int i;
    for (i = 0; i < sheetRecord->sheetCount; i++) {
        printf("Ingrese los datos de la persona (%i/%i):\n", i + 1, sheetRecord->sheetCount);

        Sheet *sheet = malloc(sizeof(Sheet));
        Person *person = malloc(sizeof(Person));

        printf("Ingrese Nombre:\n");
        char *name = malloc(sizeof(char) * MAX_BUFFER);
        scanf(" %s", name);
        person->name = name;

        printf("Ingrese apellido paterno:\n");
        char *fatherLastName = malloc(sizeof(char) * MAX_BUFFER);
        scanf(" %s", fatherLastName);
        person->fatherLastName = fatherLastName;

        printf("Ingrese apellido materno:\n");
        char *motherLastName = malloc(sizeof(char) * MAX_BUFFER);
        scanf(" %s", motherLastName);
        person->motherLastName = motherLastName;

        printf("Ingrese RUT SIN puntos y SIN digito verificador:\n");
        int rutNumber = readInt(-1, -1);

        char rutVerifier;
        printf("Ingrese el digito verificador del RUT:\n");
        scanf(" %c", &rutVerifier);
        if (rutVerifier >= 9) rutVerifier = toupper(rutVerifier);


        while (!isValidRUT(rutNumber, rutVerifier)) {
            printf("El RUT ingresado es invalido!\n");
            printf("Ingrese RUT SIN puntos y SIN digito verificador:\n");
            rutNumber = readInt(-1, -1);

            printf("Digito verificador del RUT:\n");
            scanf(" %c", &rutVerifier);
        }

        person->rutNumber = rutNumber;
        person->rutVerifier = rutVerifier;

        printf("Ingrese genero:\n");
        char *gender = malloc(sizeof(char) * MAX_BUFFER);
        scanf(" %s", gender);
        person->gender = gender;

        printf("Ingrese a%co de nacimiento:\n", 164);
        int birthYear = readInt(1899, 2021);
        person->birthYear = birthYear;

        sheet->person = person;
        sheet->number = i + 1;
        sheetRecord->sheets[i] = sheet;
    }

    printSheets();

    return 0;
}

void printSheets() {
    int i;
    for (i = 0; i < sheetRecord->sheetCount; i++) {
        Sheet * sheet = sheetRecord->sheets[i];
        Person * person = sheet->person;

        printf("======= Ficha %i =======\n", sheet->number);
        printf(" - Nombre: %s %s %s\n", person->name, person->fatherLastName, person->motherLastName);
        printf(" - RUT: %i-%c\n", person->rutNumber, person->rutVerifier);
        printf(" - Genero: %s\n", person->gender);
        printf(" - A%co de Nacimiento: %i\n", 164, person->birthYear);
    }
}

int isValidRUT(int number, char verifier) {
    int valid = 0;
    int m = 0, s = 1;
    for (; number != 0; number /= 10) {
        s = (s + number % 10 * (9 - m++ % 6)) % 11;
    }
    if (verifier == (s != 0 ? s + 47 : 75)) {
        valid = 1;
    }
    return valid;
}

int readInt(int min, int max) {
    int input;
    int status = scanf("%i", &input);
    int garbage;

    while (status != 1 || (input < min && min != -1) || (input > max && max != -1)) {
        while ((garbage = getchar()) != EOF && garbage != '\n');

        if (min == -1) printf("[ERROR]: Numero invalido! Este debe ser a lo mas %i.\n", max);
        else if (max == -1) printf("[ERROR]: Numero invalido! Este debe ser a lo menos %i.\n", min);
        else printf("[ERROR]: Numero invalido! Este debe ser a lo menos %i, y a lo mas %i.\n", min, max);

        status = scanf("%i", &input);
    }

    return (int) input;
}
