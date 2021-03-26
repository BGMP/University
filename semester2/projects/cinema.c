#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_ROOMS 9                                     // Cantidad máxima de salas
#define MAX_ROOM_ROWS 12                                // Cantidad máxima de filas de asientos por sala
#define MAX_ROOM_COLUMNS 15                             // Cantidad máxima de columnas de asientos por sala
#define MIN_ROOM_PRICE 1000                             // Precio de entrada mínimo asignable a una sala
#define MAX_ROOM_PRICE -1                               // Precio de entrada máximo asignable a una sala (-1 = infinito)

typedef struct Seat {
    int free;
    char letter;
    int number;
} Seat;

typedef struct Room {
    int price;
    int rows;
    int columns;
    int totalProfit;
    int seatsSold;
    Seat *seats[MAX_ROOM_ROWS * MAX_ROOM_COLUMNS];      // Puntero al array de asientos de la sala (Room)
} Room;

typedef struct Cinema {
    int roomCount;
    Room *rooms[MAX_ROOMS];                             // Puntero al array de salas del cine (Cinema)
} Cinema;

void fillCinema();

void fillRoom(Room *room);

void configureRoom(Room *room);

void renderMenu();

void renderPartialMenu();

void renderSpacer(int length);

int evaluateMenuOption(int option);

void sellTickets(Room *room, int amount);

void printRoomDistribution(Room *room, char row1Letter, char row2Letter);

void freeMemory();

Seat *findSeat(Room *room, char letter, int number);

void textcolor(int color);

int charDigitToInt(char digit);

int readInt(int min, int max);

Cinema *cinema;                                         // El cine, declarado de manera global.

/*
 * A lo largo de este programa, preferimos el uso del operador "->" por sobre la sintáxis tradicional (*puntero).campo,
 * ya que estimamos que es mucho más legible y fácil de manipular en la práctica.
 *
 * Ya que utilizamos con frecuencia esta sintáxis, omitiremos el explicar en cada linea qué
 * es lo que hace y lo aclararemos aquí: Nos permite, a partir de un puntero a una estructura, acceder a uno de sus
 * campos o miembros.
 *
 * Ejemplo:
 *
 * Room * room = malloc(sizeof(Room));
 * room->totalProfit = 0;
 *
*/
int main() {
    cinema = malloc(sizeof(Cinema));                    // Alojamos la memoria necesaria para el puntero cinema

    fillCinema(cinema);

    int finished = 0;
    int option;
    while (!finished) {
        renderMenu();
        option = readInt(1, 4);
        finished = evaluateMenuOption(option);
    }

    printf("Saliendo del sistema...");

    freeMemory();                                       // Liberamos toda la memoria alojada mediante malloc

    return 0;
}

void fillCinema() {
    printf("Ingrese el numero de salas con las que contara el cine (1-%i):\n", MAX_ROOMS);
    int rooms = readInt(1, MAX_ROOMS);
    cinema->roomCount = rooms;

    int i = 0;
    for (; i < rooms; i++) {
        printf("========== Configuracion Sala %i ==========\n", i + 1);

        Room *room = malloc(sizeof(Room));
        configureRoom(room);

        cinema->rooms[i] = room;
    }
}

void configureRoom(Room *room) {
    printf("Ingrese el valor de la entrada:\n");
    int price = readInt(MIN_ROOM_PRICE, MAX_ROOM_PRICE);
    room->price = price;

    printf("Ingrese el numero de filas de la sala:\n");
    int rows = readInt(2, MAX_ROOM_ROWS);
    room->rows = rows;

    printf("Ingrese el numero de columnas de la sala:\n");
    int columns = readInt(2, MAX_ROOM_COLUMNS);
    room->columns = columns;

    room->totalProfit = 0;
    room->seatsSold = 0;

    fillRoom(room);
}

void renderMenu() {
    printf("==================== Menu ====================\n");
    printf("1. Vender entradas\n");
    printf("2. Ver ocupacion de sala\n");
    printf("3. Ver total recaudado\n");
    printf("4. Salir del programa\n");
    printf("==============================================\n");
    printf("=> Elija una opcion:\n");
}

void renderPartialMenu() {
    printf("============== Ocupacion de Sala =============\n");
    printf("1. Ocupacion de una sala completa\n");
    printf("2. Ocupacion de una sala por rango de filas\n");
    printf("==============================================\n");
    printf("=> Elija una opcion:\n");
}

void renderSpacer(int length) {
    printf("======");
    for (int i = 0; i < length; i++) printf("=====");
    printf("======");
    printf("\n");
}

void sellTickets(Room *room, int amountToSell) {
    int i = 0;
    for (; i < amountToSell; i++) {
        int valid = 0;

        do {
            printRoomDistribution(room, 1, room->rows);

            char seatCode[3];                           // El código del asiento, en el formato A1, B2, etc.
            printf("Ingrese el asiento que desea vender (e.g A1):\n");
            scanf("%s", seatCode);

            char seatLetter = seatCode[0];
            int seatNumber = strlen(seatCode) == 3 ? charDigitToInt(seatCode[1]) * 10 + charDigitToInt(seatCode[2])
                                                   : charDigitToInt(seatCode[1]);

            Seat *seat = findSeat(room, seatLetter, seatNumber);
            if (seat == NULL) {
                printf("El asiento ingresado no existe en esta sala!\n");
                continue;
            }

            if (!seat->free) {
                printf("El asiento ingresado esta ocupado!\n");
                continue;
            }

            seat->free = 0;
            room->totalProfit = room->totalProfit + room->price;
            room->seatsSold++;

            printf("Asiento %c%i vendido exitosamente!\n", seatLetter, seatNumber);

            valid = 1;
        } while (!valid);
    }
}

void printRoomDistribution(Room *room, char row1Letter, char row2Letter) {
    renderSpacer(room->columns);
    int row1 = row1Letter - 64;
    int row2 = row2Letter - 64;

    int i = row1 - 1;
    int position = room->columns * i;
    for (; i < row2; i++) {

        int j = 0;
        for (; j < room->columns; j++) {
            char letter = room->seats[position]->letter;
            int number = room->seats[position]->number;

            if (!room->seats[position]->free) {
                textcolor(4);
                printf("%3c%i", letter, number);
            } else {
                textcolor(2);
                printf("%3c%i", letter, number);
            }

            textcolor(7);

            position++;
        }

        printf("\n");
    }

    renderSpacer(room->columns);
}

void printEarningsReport() {
    int cinemaProfit = 0;

    printf("=========== Informe de Ventas ===========\n");

    int i = 0;
    for (; i < cinema->roomCount; i++) {
        printf("Sala %i: $%i\n", i + 1, cinema->rooms[i]->totalProfit);
        cinemaProfit = cinemaProfit + cinema->rooms[i]->totalProfit;
    }

    printf("Total Recaudado: $%i\n", cinemaProfit);
}

int evaluateMenuOption(int option) {
    int exit = 1;

    switch (option) {
        case 1: { // Vender entradas

            printf("Ingrese el numero de la sala (Salas: %i):\n", cinema->roomCount);
            int roomNumber = readInt(1, cinema->roomCount);
            Room *room = cinema->rooms[roomNumber - 1];

            int toSell;
            do {
                printf("Ingrese la cantidad de entradas que desee vender (Libres: %i):\n", room->rows * room->columns - room->seatsSold);
                toSell = readInt(1, room->rows * room->columns);
            } while (room->seatsSold + toSell > room->rows * room->columns);

            sellTickets(room, toSell);

            return !exit;
        }

        case 2: { // Ver la ocupación de una sala

            renderPartialMenu();

            int subOption = readInt(1, 2);
            switch (subOption) {
                case 1: {
                    printf("Ingrese el numero de la sala (Salas: %i):\n", cinema->roomCount);
                    int roomNumber = readInt(1, cinema->roomCount);
                    Room *room = cinema->rooms[roomNumber - 1];

                    printRoomDistribution(room, 'A', (char) (64 + room->rows));

                    return !exit;
                }

                case 2: {
                    printf("Ingrese el numero de la sala (Salas: %i):\n", cinema->roomCount);
                    int roomNumber = readInt(1, cinema->roomCount);
                    Room *room = cinema->rooms[roomNumber - 1];

                    char letter1;
                    printf("Ingrese la letra de la fila inicial:\n");
                    scanf(" %c", &letter1);

                    char letter2;
                    printf("Ingrese la letra de la fila final:\n");
                    scanf(" %c", &letter2);

                    if (letter1 - 65 >= letter2 - 65) {
                        printf("Rango de filas invalido! [%c, %c]\n", letter1, letter2);
                    } else {
                        printRoomDistribution(room, letter1, letter2);
                    }

                    return !exit;
                }

                default:
                    break;
            }

            return !exit;
        }

        case 3: { // Ver total recaudado
            printEarningsReport();
            return !exit;
        }

        case 4: // Salir
            return exit;

        default:
            return !exit;
    }
}

Seat *findSeat(Room *room, char letter, int number) {
    int i = 0;
    for (; i < room->rows * room->columns; i++) {
        Seat *seat = room->seats[i];

        if (seat->letter == letter && seat->number == number) {
            return seat;
        }
    }

    return NULL;
}

void fillRoom(Room *room) {
    int dimension = room->rows * room->columns;
    int letter = 0;
    int number = 1;

    int position = 0;
    for (; position < dimension; position++) {
        Seat *seat = malloc(sizeof(Seat));

        seat->free = 1;
        seat->letter = (char) (65 + letter);
        seat->number = number;

        if (number == room->columns) {
            letter++;
            number = 1;
        } else {
            number++;
        }

        room->seats[position] = seat;
    }
}

void freeMemory() {
    int i = 0;
    for (; i < cinema->roomCount; i++) {
        Room *room = cinema->rooms[i];

        int j = 0;
        for (; j < room->rows * room->columns; j++) {
            Seat *seat = room->seats[j];
            free(seat);
        }

        free(room);
    }

    free(cinema);
}


/**
 * Source https://stackoverflow.com/a/51014962
 */
void textcolor(int color) {
    static int __BACKGROUND;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            color + (__BACKGROUND << 4));
}

int charDigitToInt(char digit) {
    return digit - '0';
}

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
