#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 1024

typedef struct Persona {
    char *nombre;
    char *segundoNombre;
    char *apellidoPaterno;
    char *apellidoMaterno;
    int edad;
} Persona;


void ingresarDatos(Persona * persona);
void imprimirDatosDelMasJoven();
void imprimirDatosDe(Persona * persona);

Persona * persona1;
Persona * persona2;

int i = 0;

int main() {
    persona1 = malloc(sizeof(Persona));
    persona2 = malloc(sizeof(Persona));

    ingresarDatos(persona1);
    ingresarDatos(persona2);

    imprimirDatosDelMasJoven();
}

void ingresarDatos(Persona * persona) {
    printf("Ingrese el nombre de la persona %i:\n", i + 1);
    char * nombre = malloc(sizeof(char) * MAX_BUFFER);
    scanf(" %s", nombre);

    printf("Ingrese el segundo nombre de la persona %i:\n", i + 1);
    char * segundoNombre = malloc(sizeof(char) * MAX_BUFFER);
    scanf(" %s", segundoNombre);

    printf("Ingrese el apellido paterno de la persona %i:\n", i + 1);
    char * apellidoPaterno = malloc(sizeof(char) * MAX_BUFFER);
    scanf(" %s", apellidoPaterno);


    printf("Ingrese el apellido materno de la persona %i:\n", i + 1);
    char * apellidoMaterno = malloc(sizeof(char) * MAX_BUFFER);
    scanf(" %s", apellidoMaterno);

    printf("Ingrese la edad de la persona %i:\n", i + 1);
    scanf("%i", &persona->edad);

    persona->nombre = nombre;
    persona->segundoNombre = segundoNombre;
    persona->apellidoPaterno = apellidoPaterno;
    persona->apellidoMaterno = apellidoMaterno;

    i++;
}

void imprimirDatosDelMasJoven() {
    Persona * masJoven;

    if (persona1->edad > persona2->edad) {
        masJoven = persona2;
    } else {
        masJoven = persona1;
    }

    imprimirDatosDe(masJoven);
}

void imprimirDatosDe(Persona * persona) {
    printf("========== Datos del menor ==========\n");
    printf("Nombre: %s\n", persona->nombre);
    printf("Segundo nombre: %s\n", persona->segundoNombre);
    printf("Apellido paterno: %s\n", persona->apellidoPaterno);
    printf("Apellido materno: %s\n", persona->apellidoMaterno);
    printf("Edad: %i\n", persona->edad);
}
