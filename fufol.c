#include <stdio.h>
#include <string.h>

int leerGoles() {
    int goles;
    char c;
    while (1) {
        if (scanf("%d", &goles) != 1) {
            printf("Entrada inválida. Ingrese un número entero no negativo: ");
            while ((c = getchar()) != '\n' && c != EOF);
        } else if (goles < 0) {
            printf("No se permiten goles negativos. Ingrese de nuevo: ");
            while ((c = getchar()) != '\n' && c != EOF);
        } else {
            while ((c = getchar()) != '\n' && c != EOF);
            return goles;
        }
    }
}

int main() {
    char equipos[4][31];
    int puntos[4] = {0, 0, 0, 0};
    int golesFavor[4] = {0, 0, 0, 0};
    int golesContra[4] = {0, 0, 0, 0};
    int golDiferencia[4] = {0, 0, 0, 0};
    int i, j;

    printf("Ingrese los nombres de los 4 equipos:\n");
    for (i = 0; i < 4; i++) {
        printf("Equipo %d: ", i + 1);
        fgets(equipos[i], 31, stdin);
        if (equipos[i][strlen(equipos[i]) - 1] == '\n') {
            equipos[i][strlen(equipos[i]) - 1] = '\0';
        }
        while (strlen(equipos[i]) == 0) {
            printf("Nombre no válido. Ingrese de nuevo: ");
            fgets(equipos[i], 31, stdin);
            if (equipos[i][strlen(equipos[i]) - 1] == '\n') {
                equipos[i][strlen(equipos[i]) - 1] = '\0';
            }
        }
    }

    printf("\nIngrese los resultados de los partidos:\n");
    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            int golesA = 0, golesB = 0;
            printf("\n%s vs %s\n", equipos[i], equipos[j]);
            printf("Goles de %s: ", equipos[i]);
            golesA = leerGoles();
            printf("Goles de %s: ", equipos[j]);
            golesB = leerGoles();

            golesFavor[i] += golesA;
            golesContra[i] += golesB;
            golesFavor[j] += golesB;
            golesContra[j] += golesA;

            if (golesA > golesB) {
                puntos[i] += 3;
            } else if (golesA < golesB) {
                puntos[j] += 3;
            } else {
                puntos[i] += 1;
                puntos[j] += 1;
            }
        }
    }

    for (i = 0; i < 4; i++) {
        golDiferencia[i] = golesFavor[i] - golesContra[i];
    }

    printf("\nTabla de posiciones:\n");
    printf("%-20s %-10s %-10s\n", "Equipo", "Puntos", "Gol Dif");
    for (i = 0; i < 4; i++) {
        printf("%-20s %-10d %-10d\n", equipos[i], puntos[i], golDiferencia[i]);
    }


    int primero = 0, segundo = 1;
    if (puntos[1] > puntos[0] || (puntos[1] == puntos[0] && golDiferencia[1] > golDiferencia[0])) {
        primero = 1;
        segundo = 0;
    }

    for (i = 2; i < 4; i++) {
        if (puntos[i] > puntos[primero] || (puntos[i] == puntos[primero] && golDiferencia[i] > golDiferencia[primero])) {
            segundo = primero;
            primero = i;
        } else if (puntos[i] > puntos[segundo] || (puntos[i] == puntos[segundo] && golDiferencia[i] > golDiferencia[segundo])) {
            segundo = i;
        }
    }

    printf("\nLos equipos que jugaran la final son:\n");
    printf("%s y %s\n", equipos[primero], equipos[segundo]);

    return 0;
}
