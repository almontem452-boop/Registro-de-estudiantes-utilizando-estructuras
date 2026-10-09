#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_ESTUDIANTES 5
struct Estudiante {
    char matricula[20];
    char nombre[50];
    char carrera[50];
    float promedio;
};
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
int esSoloNumeros(const char *cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!isdigit(cadena[i])) {
            return 0;
        }
    }
    return 1;
}
void formatearMatricula(const char *entrada, char *salida) {
    if (strlen(entrada) != 7) {
        strcpy(salida, entrada);
        return;
    }
    sprintf(salida, "%c-%c%c-%c%c%c%c", 
            entrada[0], 
            entrada[1], entrada[2], 
            entrada[3], entrada[4], entrada[5], entrada[6]);
}
int main() {
    struct Estudiante estudiantes[MAX_ESTUDIANTES];
    int i;
    char entradaMatricula[20];
    char matriculaBuscar[20];
    int encontrado = 0;
    int indiceMayor = 0;
    printf("=== REGISTRO DE ESTUDIANTES ===\n\n");
    for (i = 0; i < MAX_ESTUDIANTES; i++) {
        printf("--- Estudiante %d ---\n", i + 1);
        while (1) {
            printf("Ingrese la matricula (7 digitos, ej. 1137136): ");
            fgets(entradaMatricula, sizeof(entradaMatricula), stdin);
            entradaMatricula[strcspn(entradaMatricula, "\n")] = 0;

            if (strlen(entradaMatricula) == 7 && esSoloNumeros(entradaMatricula)) {
                break;
            }
            printf("Error: La matricula debe tener exactamente 7 numeros sin espacios ni guiones.\n");
        }
        formatearMatricula(entradaMatricula, estudiantes[i].matricula);
        printf("Ingrese el nombre: ");
        fgets(estudiantes[i].nombre, sizeof(estudiantes[i].nombre), stdin);
        estudiantes[i].nombre[strcspn(estudiantes[i].nombre, "\n")] = 0;
        printf("Ingrese la carrera: ");
        fgets(estudiantes[i].carrera, sizeof(estudiantes[i].carrera), stdin);
        estudiantes[i].carrera[strcspn(estudiantes[i].carrera, "\n")] = 0;
        printf("Ingrese el promedio: ");
        while (scanf("%f", &estudiantes[i].promedio) != 1) {
            printf("Entrada invalida. Ingrese un numero decimal para el promedio: ");
            limpiarBuffer();
        }
        limpiarBuffer();
        printf("\n");
    }
    printf("\n=== LISTADO DE ESTUDIANTES REGISTRADOS ===\n");
    for (i = 0; i < MAX_ESTUDIANTES; i++) {
        printf("- Matricula: %s\n", estudiantes[i].matricula);
        printf("- Nombre: %s\n", estudiantes[i].nombre);
        printf("- Carrera: %s\n", estudiantes[i].carrera);
        printf("- Promedio: %.2f\n\n", estudiantes[i].promedio);
    }
    printf("=== BUSCAR ESTUDIANTE ===\n");
    printf("Ingrese la matricula que desea buscar (7 digitos o formateada): ");
    fgets(entradaMatricula, sizeof(entradaMatricula), stdin);
    entradaMatricula[strcspn(entradaMatricula, "\n")] = 0;
    if (strlen(entradaMatricula) == 7 && esSoloNumeros(entradaMatricula)) {
        formatearMatricula(entradaMatricula, matriculaBuscar);
    } else {
        strcpy(matriculaBuscar, entradaMatricula);
    }
    for (i = 0; i < MAX_ESTUDIANTES; i++) {
        if (strcmp(estudiantes[i].matricula, matriculaBuscar) == 0) {
            printf("\nESTUDIANTE ENCONTRADO\n");
            printf("- Matricula: %s\n", estudiantes[i].matricula);
            printf("- Nombre: %s\n", estudiantes[i].nombre);
            printf("- Carrera: %s\n", estudiantes[i].carrera);
            printf("- Promedio: %.2f\n", estudiantes[i].promedio);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("\nEstudiante no encontrado.\n");
    }
    for (i = 1; i < MAX_ESTUDIANTES; i++) {
        if (estudiantes[i].promedio > estudiantes[indiceMayor].promedio) {
            indiceMayor = i;
        }
    }
    printf("\nESTUDIANTE CON MAYOR PROMEDIO\n");
    printf("- Nombre: %s\n", estudiantes[indiceMayor].nombre);
    printf("- Matricula: %s\n", estudiantes[indiceMayor].matricula);
    printf("- Carrera: %s\n", estudiantes[indiceMayor].carrera);
    printf("- Promedio: %.2f\n", estudiantes[indiceMayor].promedio);
    return 0;
}