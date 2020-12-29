#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 1024
#define MAX_STUDENTS 80

typedef struct Student {
    char * name;
    int age;
    double average;
} Student;

typedef struct Class {
    char * name;
    int code;
    int studentCount;
    Student * students[MAX_STUDENTS];
} Class;

typedef struct University {
    int classCount;
    Class * classes[MAX_BUFFER];
} University;

University * university;

int readInt(double min, double max);
double calcClassAverage(Class * class);
Student * findMaxAverageStudent(Class * class);

// José Benavente
// 20.779.165-2
int main() {
    university = malloc(sizeof(University));

    printf("Ingrese la cantidad de asignaturas:\n");
    int classesAmount = readInt(1, -1);

    int i = 0;
    for (; i < classesAmount; i++) {
        Class * class = malloc(sizeof(Class));

        printf("Ingrese el nombre de la clase %i:\n", i + 1);
        char * className = malloc(sizeof(char) * MAX_BUFFER);
        scanf(" %s", className);
        class->name = className;

        printf("Ingrese el codigo de la clase %i:\n", i + 1);
        int classCode = readInt(-1, -1);
        class->code = classCode;

        printf("Ingrese la cantidad de alumnos (Maximo 80):\n");
        int studentCount = readInt(1, MAX_STUDENTS);
        class->studentCount = studentCount;

        int j = 0;
        for (; j < studentCount; j++) {
            Student * student = malloc(sizeof(Student));
            printf("Ingrese el nombre del estudiante %i:\n", j + 1);
            char * studentName = malloc(sizeof(char) * MAX_BUFFER);
            scanf(" %s", studentName);
            student->name = studentName;

            printf("Ingrese la edad del estudiante %i:\n", j + 1);
            int studentAge = readInt(0, -1);
            student->age = studentAge;

            printf("Ingrese el promedio del estudiante %i:\n", j + 1);
            int studentAverage = readInt(0.0, 7.0);
            student->average = studentAverage;

            class->students[j] = student;
        }

        university->classCount = classesAmount;
        university->classes[i] = class;
    }

    int j = 0;
    for (; j < university->classCount; j++) {
        Class * class = university->classes[j];
        printf("========================\n");
        printf("Asignatura: %s\n", class->name);
        printf("Promedio general: %f\n", calcClassAverage(class));
        printf("========================\n");
    }

    int k = 0;
    for (; k < university->classCount; k++) {
        Class * class = university->classes[k];
        printf("========================\n");
        printf("Asignatura: %s\n", class->name);
        printf("Alumno con mejor Promedio: %s\n", findMaxAverageStudent(class)->name);
        printf("========================\n");
    }
}

double calcClassAverage(Class * class) {
    int i = 0;
    double sum = 0;
    for (; i < class->studentCount; i++) {
        Student * student = class->students[i];
        sum += student->average;
    }

    return sum / class->studentCount;
}

Student * findMaxAverageStudent(Class * class) {
    int i = 0;
    double maxAverage = 0;
    Student * match;
    for (; i < class->studentCount; i++) {
        Student * student = class->students[i];
        if (maxAverage < student->average) {
            match = student;
            maxAverage = student->average;
        }
    }

    return match;
}

int readInt(double min, double max) {
    float input;
    int status = scanf("%f", &input);
    int garbage;

    while (status != 1 || (input < min && min != -1) || (input > max && max != -1)) {
        while ((garbage = getchar()) != EOF && garbage != '\n');

        if (min == -1) printf("[ERROR]: Numero invalido! Este debe ser a lo mas %i.\n", max);
        else if (max == -1) printf("[ERROR]: Numero invalido! Este debe ser a lo menos %i.\n", min);
        else printf("[ERROR]: Cantidad invalida!");

        status = scanf("%f", &input);
    }

    return input;
}
