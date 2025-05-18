#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    char nombre[5][30];
    int puntos[5][4];
    float promedios[5];
    int mejorJugador = 0;
    float mayorPromedio = 0;
    int len, esValido, num;
    char entrada[30];

    for (int i = 0; i < 5; i++) {
        do {
            esValido = 1;
            printf("Ingrese el nombre del jugador %d: ", i + 1);
            fflush(stdin);
            fgets(nombre[i], 30, stdin);
            len = strlen(nombre[i]);
            if (nombre[i][len - 1] == '\n') {

                
                nombre[i][len - 1] = '\0';
            }

            if (strlen(nombre[i]) == 0) {
                esValido = 0;
            }

            for (int j = 0; j < strlen(nombre[i]); j++) {
                if (nombre[i][j] >= '0' && nombre[i][j] <= '9') {
                    esValido = 0;
                }
            }

            if (esValido == 0) {
                printf("Nombre invalido. No puede contener numeros ni estar vacio.\n");
            }

        } while (esValido == 0);

        for (int j = 0; j < 4; j++) {
            do {
                esValido = 1;
                printf("Ingrese los puntos del jugador %s en el partido %d: ", nombre[i], j + 1);
                fflush(stdin);
                fgets(entrada, 30, stdin);
                len = strlen(entrada);
                if (entrada[len - 1] == '\n') {
                    entrada[len - 1] = '\0';
                }

                if (strlen(entrada) == 0) {
                    esValido = 0;
                }

                for (int k = 0; k < strlen(entrada); k++) {
                    if (entrada[k] < '0' || entrada[k] > '9') {
                        esValido = 0;
                    }
                }

                if (esValido == 0) {
                    printf("Puntos invalidos. Ingrese solo numeros positivos sin letras.\n");
                }

            } while (esValido == 0);

            
            num = 0;
            for (int k = 0; k < strlen(entrada); k++) {
                num = num * 10 + (entrada[k] - '0');
            }

            puntos[i][j] = num;
        }
    }

    for (int i = 0; i < 5; i++) {
        int suma = 0;
        for (int j = 0; j < 4; j++) {
            suma += puntos[i][j];
        }
        promedios[i] = suma / 4.0;

        if (promedios[i] > mayorPromedio) {
            mayorPromedio = promedios[i];
            mejorJugador = i;
        }
    }

    printf("\n--- Promedios de los jugadores ---\n");
    for (int i = 0; i < 5; i++) {
        printf("Jugador: %s - Promedio: %.2f\n", nombre[i], promedios[i]);
    }

    printf("\nEl mejor jugador fue: %s con un promedio de %.2f puntos\n", nombre[mejorJugador], mayorPromedio);

    return 0;
}