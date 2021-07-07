#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Dificultad
 *      1: Fácil (4x4 casillas)
 *      2: Media (4x6 casillas)
 */
typedef struct Juego {
    int dificultad;
    int filas;
    int columnas;
    int intentos;
} Juego;

Juego * juego;

void escribirMenu();
int numeroAleatorioEntre(int min, int max);

int main() {
    srand(time(NULL));

    juego = malloc(sizeof(Juego));

    escribirMenu();

    int opcion;
    do {
        printf("Ingrese una opcion:\n");
        scanf("%i", &opcion);
    } while (opcion < 1 || opcion > 3);

    switch (opcion) {
        case 1:
            juego->filas = 4;
            juego->columnas = 4;
            juego->intentos = 8;
            break;
        case 2:
            juego->filas = 4;
            juego->columnas = 6;
            juego->intentos = 12;
            break;
        case 3:
            return 0;
        default:
            return 1;
    }

    int cantidadDeNumerosEscondidos = (juego->filas * juego->columnas) / 2;
    int tablero[juego->filas][juego->columnas];
    int numerosEscondidos[cantidadDeNumerosEscondidos];

    int i = 0;
    int j = 0;
    for (; i < juego->filas; i++) {
        for (; j < juego->columnas; j++) {
            tablero[i][j] = 0;
        }

        j = 0;
    }

    int k = 0;
    for (; k < cantidadDeNumerosEscondidos; k++) {
        int random = numeroAleatorioEntre(1, 99);

        int l = 0;
        for (; l < k; l++) {
            while (numerosEscondidos[k] == random) {
                random = numeroAleatorioEntre(1, 99);
            }
        }

        numerosEscondidos[k] = random;
    }

    int m = 0;
    for (; m < cantidadDeNumerosEscondidos; m++) {
        int fila = numeroAleatorioEntre(0, juego->filas - 1);
        int columna = numeroAleatorioEntre(0, juego->columnas - 1);
        int colocado = 0;

        while (!colocado) {
            if (tablero[fila][columna] != 0) {
                fila = numeroAleatorioEntre(0, juego->filas - 1);
                columna = numeroAleatorioEntre(0, juego->columnas - 1);
                continue;
            } else {
                tablero[fila][columna] = numerosEscondidos[m];
                colocado = 1;
            }
        }
    }

    m = 0;
    for (; m < cantidadDeNumerosEscondidos; m++) {
        int fila = numeroAleatorioEntre(0, juego->filas - 1);
        int columna = numeroAleatorioEntre(0, juego->columnas - 1);
        int colocado = 0;

        while (!colocado) {
            if (tablero[fila][columna] != 0) {
                fila = numeroAleatorioEntre(0, juego->filas - 1);
                columna = numeroAleatorioEntre(0, juego->columnas - 1);
                continue;
            } else {
                tablero[fila][columna] = numerosEscondidos[m];
                colocado = 1;
            }
        }
    }

    int numerosEncontrados[cantidadDeNumerosEscondidos];

    i = 0;
    for (; i < cantidadDeNumerosEscondidos; i++) {
        numerosEncontrados[i] = 0;
    }

    int intentos = 1;
    int puntaje = 0;
    do {
        i = 0;
        j = 0;
        printf("======= TABLERO =======\n");
        for (; i < juego->filas; i++) {
            for (; j < juego->columnas; j++) {
                int mostrar = 0;
                int u = 0;
                for (; u < cantidadDeNumerosEscondidos; u++) {
                    if (tablero[i][j] == numerosEncontrados[u]) {
                        mostrar = 1;
                    }
                }

                if (mostrar) {
                    printf("%3i ", tablero[i][j]);
                } else {
                    printf(" ?? ");
                }
            }

            printf("\n");
            j = 0;
        }
        printf("=======================\n");
        printf("Jugando intento %i de %i\n", intentos, juego->intentos);
        printf("Ingrese coordenadas:\n");

        printf("Fila del primer elemento:\n");
        int fila1;
        scanf("%i", &fila1);

        int columna1;
        printf("Columna del primer elemento:\n");
        scanf("%i", &columna1);

        int n1 = tablero[fila1 - 1][columna1 - 1];
        printf("...:::Elemento seleccionado: %i :::...\n", n1);

        printf("Fila del segundo elemento:\n");
        int fila2;
        scanf("%i", &fila2);

        int columna2;
        printf("Columna del segundo elemento:\n");
        scanf("%i", &columna2);


        int n2 = tablero[fila2 - 1][columna2 - 1];
        printf("...:::Elemento seleccionado: %i :::...\n", n2);

        if (fila1 == fila2 && columna1 == columna2) {
            printf("...:::Seleccionaste dos coordenadas iguales:::...\n");
            continue;
        }

        if (n1 == n2) {
            printf("---> Has encontrado una pareja <---\n");
            puntaje = puntaje + 10;
            numerosEncontrados[intentos] = n1;
        } else {
            printf("---> No son una pareja, sigue intentando <---\n");
        }

        intentos++;
    } while (intentos <= juego->intentos);

    printf("FELICIDADES: Tiene %i puntos acomulados.\n", puntaje);
    printf("Juego terminado. Puntaje obtenido : %i con un %f por ciento de aciertos", puntaje, (((double) puntaje / 10) / intentos) * 100);

    free(juego);
}

void escribirMenu() {
    printf("===== JUEGO =====\n");
    printf("1. Nivel basico\n");
    printf("2. Nivel medio\n");
    printf("3. Salir\n");
}

int numeroAleatorioEntre(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}
