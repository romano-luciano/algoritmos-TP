#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Funciones.h"
#include "pilaDinamica.h"

void menuDif(FILE *informe)
{
    int dif;
    do
    {
        printf("[1]Facil\n[2]Medio\n[3]Dificil\n[0]Volver\nIngrese la dificultad: ");
        scanf("%d", &dif);
        switch (dif)
        {
        case 1:
            system("cls");
            printf("Modo facil elegido!\n");
            fprintf(informe, "Dificultad: Facil\n");
            partida(1, informe);
            dif = 0;
            break;
        case 2:
            system("cls");
            printf("Modo medio elegido!\n");
            fprintf(informe, "Dificultad: Medio\n");
            partida(2, informe);
            dif = 0;
            break;
        case 3:
            system("cls");
            printf("Modo dificil elegido!\n");
            fprintf(informe, "Dificultad: Dificil\n");
            partida(3, informe);
            dif = 0;
            break;
        case 0:
            system("cls");
            fprintf(informe, "Partida no iniciada");
            fclose(informe);
            break;
        default:
            system("cls");
            printf("Opcion no valida. Ingrese nuevamente\n");
            break;
        }
    } while (dif != 0);
}
