#include <stdio.h>
#include <string.h>

int esDigito(char c) {
    return c >= '0' && c <= '9';
}

int esNombreValido(char *nombre) {
    if (strlen(nombre) == 0) return 0;
    for (int i = 0; nombre[i] != '\0'; i++) {
        if (esDigito(nombre[i])) return 0;
    }
    return 1;
}

int leerEnteroPositivo(char *mensaje) {
    int valor;
    do {
        printf("%s", mensaje);
        scanf("%d", &valor);
        if (valor < 0) {
            printf("Ingrese un numero mayor o igual a cero.\n");
        }
    } while (valor < 0);
    return valor;
}

int buscarProducto(char nombres[][30], int total, char *nombreBuscado) {
    for (int i = 0; i < total; i++) {
        if (strcmp(nombres[i], nombreBuscado) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    char nombres[5][30];
    int cantidades[5];
    int tiempos[5];
    int recursos[5][4];
    int recursosDisponibles[4];
    char nombreRecursos[4][30] = { "Pantallas", "Altavoces", "Procesadores", "Placas" };
    int totalProductos = 0;
    int opcion;
    int tiempoDisponible;

    tiempoDisponible = leerEnteroPositivo("Ingrese tiempo total disponible (minutos): ");

    printf("Ingrese recursos disponibles:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s: ", nombreRecursos[i]);
        recursosDisponibles[i] = leerEnteroPositivo("");
    }

    do {
        printf("\n--- Menu ---\n");
        printf("1. Agregar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Mostrar productos\n");
        printf("5. Calcular produccion\n");
        printf("6. Modificar recursos disponibles\n");
        printf("7. Modificar tiempo disponible\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            if (totalProductos >= 5) {
                printf("Maximo de productos alcanzado.\n");
                continue;
            }

            char tempNombre[30];
            do {
                printf("Nombre del producto: ");
                scanf(" %[^\n]", tempNombre);
                if (!esNombreValido(tempNombre)) {
                    printf("Nombre invalido. No debe tener numeros ni estar vacio.\n");
                }
            } while (!esNombreValido(tempNombre));

            strcpy(nombres[totalProductos], tempNombre);
            cantidades[totalProductos] = leerEnteroPositivo("Cantidad demandada: ");
            tiempos[totalProductos] = leerEnteroPositivo("Tiempo por unidad (minutos): ");

            for (int j = 0; j < 4; j++) {
                printf("Unidades de %s por unidad: ", nombreRecursos[j]);
                recursos[totalProductos][j] = leerEnteroPositivo("");
            }

            totalProductos++;
        }

        else if (opcion == 2) {
            char buscar[30];
            printf("Nombre del producto a editar: ");
            scanf(" %[^\n]", buscar);
            int pos = buscarProducto(nombres, totalProductos, buscar);

            if (pos == -1) {
                printf("Producto no encontrado.\n");
                continue;
            }

            char nuevoNombre[30];
            do {
                printf("Nuevo nombre: ");
                scanf(" %[^\n]", nuevoNombre);
                if (!esNombreValido(nuevoNombre)) {
                    printf("Nombre invalido.\n");
                }
            } while (!esNombreValido(nuevoNombre));
            strcpy(nombres[pos], nuevoNombre);

            cantidades[pos] = leerEnteroPositivo("Nueva cantidad: ");
            tiempos[pos] = leerEnteroPositivo("Nuevo tiempo por unidad: ");
            for (int j = 0; j < 4; j++) {
                printf("Unidades de %s por unidad: ", nombreRecursos[j]);
                recursos[pos][j] = leerEnteroPositivo("");
            }
            printf("Producto editado.\n");
        }

        else if (opcion == 3) {
            char buscar[30];
            printf("Nombre del producto a eliminar: ");
            scanf(" %[^\n]", buscar);
            int pos = buscarProducto(nombres, totalProductos, buscar);

            if (pos == -1) {
                printf("Producto no encontrado.\n");
                continue;
            }

            for (int i = pos; i < totalProductos - 1; i++) {
                strcpy(nombres[i], nombres[i+1]);
                cantidades[i] = cantidades[i+1];
                tiempos[i] = tiempos[i+1];
                for (int j = 0; j < 4; j++) {
                    recursos[i][j] = recursos[i+1][j];
                }
            }
            totalProductos--;
            printf("Producto eliminado.\n");
        }

        else if (opcion == 4) {
            printf("\nProductos:\n");
            for (int i = 0; i < totalProductos; i++) {
                printf("- %s | Cantidad: %d | Tiempo/u: %d\n", nombres[i], cantidades[i], tiempos[i]);
                for (int j = 0; j < 4; j++) {
                    printf("  %s/u: %d\n", nombreRecursos[j], recursos[i][j]);
                }
            }
        }

        else if (opcion == 5)
        {
            int tiempoRestante = tiempoDisponible;
            int recursosRestantes[4];
            for (int j = 0; j < 4; j++)
            {
                recursosRestantes[j] = recursosDisponibles[j];
            }

            printf("\nEvaluando produccion secuencial:\n");

            int alMenosUno = 0;
            for (int i = 0; i < totalProductos; i++)
            {
                int tiempoNecesario = cantidades[i] * tiempos[i];
                int recursosNecesarios[4];
                int recursosSuficientes = 1;
                
                printf("\nAnalizando producto: %s\n", nombres[i]);
                printf("Tiempo necesario: %d minutos (disponible: %d)\n", tiempoNecesario, tiempoRestante);
                
                if (tiempoNecesario > tiempoRestante) {
                    printf("-> No hay suficiente tiempo. Faltan %d minutos\n", tiempoNecesario - tiempoRestante);
                    printf("   Para modificar el tiempo disponible, dirijase a la opcion 7 del menu.\n");
                    recursosSuficientes = 0;
                }

                for (int j = 0; j < 4; j++)
                {
                    recursosNecesarios[j] = cantidades[i] * recursos[i][j];
                    printf("%s necesarios: %d (disponible: %d)\n", 
                           nombreRecursos[j], recursosNecesarios[j], recursosRestantes[j]);
                    
                    if (recursosNecesarios[j] > recursosRestantes[j])
                    {
                        printf("-> Faltan %d unidades de %s\n", 
                               recursosNecesarios[j] - recursosRestantes[j], nombreRecursos[j]);
                        if (!recursosSuficientes) {
                            printf(" Para modificar los recursos disponibles, dirijase a la opcion 6 del menu.\n");
                            break;
                        }
                        recursosSuficientes = 0;
                    }
                }

                if (recursosSuficientes)
                {
                    printf("\n✓ Se puede producir: %s\n", nombres[i]);
                    tiempoRestante -= tiempoNecesario;
                    for (int j = 0; j < 4; j++)
                    {
                        recursosRestantes[j] -= recursosNecesarios[j];
                    }
                    alMenosUno = 1;
                }
                else
                {
                    printf("\n✗ No se puede producir: %s\n", nombres[i]);
                }
            }

            if (!alMenosUno)
            {
                printf("\nNo se puede producir ningun producto completamente.\n");
            }

            printf("\nResumen final:\n");
            printf("Tiempo restante: %d minutos\n", tiempoRestante);
            for (int j = 0; j < 4; j++)
            {
                printf("%s restante: %d\n", nombreRecursos[j], recursosRestantes[j]);
            }
        }

        else if (opcion == 6)
        {
            printf("\n--- Modificar Recursos Disponibles ---\n");
            printf("Recursos actuales:\n");
            for (int i = 0; i < 4; i++) {
                printf("%s: %d\n", nombreRecursos[i], recursosDisponibles[i]);
            }

            printf("\nIngrese nuevas cantidades:\n");
            for (int i = 0; i < 4; i++) {
                printf("%s: ", nombreRecursos[i]);
                recursosDisponibles[i] = leerEnteroPositivo("");
            }
            
            printf("\nRecursos actualizados exitosamente!\n");
            printf("Nuevas cantidades:\n");
            for (int i = 0; i < 4; i++) {
                printf("%s: %d\n", nombreRecursos[i], recursosDisponibles[i]);
            }
        }

        else if (opcion == 7)
        {
            printf("\n--- Modificar Tiempo Disponible ---\n");
            printf("Tiempo actual disponible: %d minutos\n", tiempoDisponible);
            
            printf("\nIngrese nuevo tiempo disponible:\n");
            tiempoDisponible = leerEnteroPositivo("Minutos: ");
            
            printf("\nTiempo actualizado exitosamente!\n");
            printf("Nuevo tiempo disponible: %d minutos\n", tiempoDisponible);
        }

        else if (opcion == 0) {
            printf("Saliendo del programa...\n");
        }

        else {
            printf("Opcion invalida.\n");
        }

    } while (opcion != 0);

    return 0;
}