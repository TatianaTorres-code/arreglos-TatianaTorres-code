#include <stdio.h>

int main() {
    int estudiantes = 5;
    int asignaturas = 3;
    float calificaciones[5][3] = {0};
    int i, j, opcion;

    char estudiantes_nombres[5][30];
    char materias[3][20];
    int nombres_ingresados = 0;
    int materias_ingresadas = 0;

    do {
        printf("\n--- MENU DE OPCIONES ---\n");
        printf("1. Ingresar los nombres de los estudiantes y calificaciones\n");
        printf("2. Calcular el promedio por estudiante\n");
        printf("3. Calcular el promedio por asignatura\n");
        printf("4. Mostrar la calificacion maxima y minima por estudiante\n");
        printf("5. Mostrar la calificacion maxima y minima por asignatura\n");
        printf("6. Mostrar la cantidad de aprobados y reprobados por asignatura\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese los nombres de las materias a calificar:\n");
                for (j = 0; j < asignaturas; j++) {
                    printf("Nombre de la materia %d: ", j + 1);
                    scanf("%s", materias[j]);
                }
                materias_ingresadas = 1;

                for (i = 0; i < estudiantes; i++) {
                    printf("Ingrese el nombre del estudiante %d: ", i + 1);
                    scanf("%s", estudiantes_nombres[i]);
                }
                nombres_ingresados = 1;

                for (i = 0; i < estudiantes; i++) {
                    printf("Estudiante: %s\n", estudiantes_nombres[i]);
                    for (j = 0; j < asignaturas; j++) {
                        do {
                            printf("  Ingrese calificacion para %s (0 a 10): ", materias[j]);
                            scanf("%f", &calificaciones[i][j]);
                            if (calificaciones[i][j] < 0 || calificaciones[i][j] > 10)
                                printf("  Valor incorrecto! Debe ingresar un valor entre 0 y 10.\n");
                        } while (calificaciones[i][j] < 0 || calificaciones[i][j] > 10);
                    }
                }
                break;

            case 2:
                if (!nombres_ingresados || !materias_ingresadas) {
                    printf("Por favor ingrese los nombres de estudiantes y materias.");
                    break;
                }
                printf("\nPromedio por estudiante:\n");
                for (i = 0; i < estudiantes; i++) {
                    float suma = 0;
                    for (j = 0; j < asignaturas; j++) {
                        suma += calificaciones[i][j];
                    }
                    printf("  %s: %.2f\n", estudiantes_nombres[i], suma / asignaturas);
                }
                break;

            case 3:
                if (!nombres_ingresados || !materias_ingresadas) {
                    printf("Por favor ingrese los nombres de estudiantes y materias.");
                    break;
                }
                printf("\nPromedio por asignatura:\n");
                for (j = 0; j < asignaturas; j++) {
                    float suma = 0;
                    for (i = 0; i < estudiantes; i++) {
                        suma += calificaciones[i][j];
                    }
                    printf("  %s: %.2f\n", materias[j], suma / estudiantes);
                }
                break;

            case 4:
                if (!nombres_ingresados || !materias_ingresadas) {
                    printf("Por favor ingrese los nombres de estudiantes y materias.");
                    break;
                }
                printf("\nCalificaciones mas alta y mas baja por estudiante:\n");
                for (i = 0; i < estudiantes; i++) {
                    float max = calificaciones[i][0], min = calificaciones[i][0];
                    for (j = 1; j < asignaturas; j++) {
                        if (calificaciones[i][j] > max) max = calificaciones[i][j];
                        if (calificaciones[i][j] < min) min = calificaciones[i][j];
                    }
                    printf("  %s: Maxima = %.2f, Minima = %.2f\n", estudiantes_nombres[i], max, min);
                }
                break;

            case 5:
                if (!nombres_ingresados) {
                    printf("Por favor ingrese los nombres de estudiantes y materias.\n");
                    break;
                }
                printf("\nCalificaciones mas alta y mas baja por asignatura:\n");
                for (j = 0; j < asignaturas; j++) {
                    float max = calificaciones[0][j], min = calificaciones[0][j];
                    for (i = 1; i < estudiantes; i++) {
                        if (calificaciones[i][j] > max) max = calificaciones[i][j];
                        if (calificaciones[i][j] < min) min = calificaciones[i][j];
                    }
                    printf("  %s: Maxima = %.2f, Minima = %.2f\n", materias[j], max, min);
                }
                break;

            case 6:
                if (!nombres_ingresados) {
                    printf("Por favor ingrese los nombres de estudiantes y materias.\n");
                    break;
                }
                printf("\nAprobados y reprobados por asignatura:\n");
                for (j = 0; j < asignaturas; j++) {
                    int aprobados = 0, reprobados = 0;
                    for (i = 0; i < estudiantes; i++) {
                        if (calificaciones[i][j] >= 6)
                            aprobados++;
                        else
                            reprobados++;
                    }
                    printf("  %s: Aprobados = %d, Reprobados = %d\n", materias[j], aprobados, reprobados);
                }
                break;

            case 7:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion invalida. Por favor intente de nuevo.\n");
        }

    } while (opcion != 7);

    return 0;
}