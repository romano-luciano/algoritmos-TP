#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funciones.h"


void menuDif(FILE *informe)
{
    int dif;
    do
    {
        system("cls || clear");
        setColor(14); // Amarillo
        printf("=====================================\n");
        printf("          MODO DE DIFICULTAD        \n");
        printf("=====================================\n");
        setColor(15); // Blanco
        printf("Seleccione un modo para jugar:\n\n");

        setColor(11); printf("[1]"); setColor(15); printf(" Facil     - Juega al azar\n");
        setColor(11); printf("[2]"); setColor(15); printf(" Medio     - Evita jugadas inefectivas\n");
        setColor(11); printf("[3]"); setColor(15); printf(" Dificil   - Juega estrategicamente\n");
        setColor(11); printf("[0]"); setColor(15); printf(" Volver al menu anterior\n");

        setColor(14);
        printf("\n=====================================\n");
        setColor(15);
        printf("Ingrese la dificultad: ");
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
            setColor(1); //azul oscuro
            printf("Modo medio elegido!\n");
            fprintf(informe, "Dificultad: Medio\n");
            partida(2, informe);
            dif = 0;
            break;
        case 3:
            system("cls");
            setColor(4); //rojo oscuro
            printf("Modo dificil elegido!\n");
            fprintf(informe, "Dificultad: Dificil\n");
            partida(3, informe);
            dif = 0;
            break;
        case 0:
            system("cls");
            setColor(6); //amarillo oscuro
            fprintf(informe, "Partida no iniciada");
            fclose(informe);
            break;
        default:
            system("cls");
            setColor(14); //amarillo claro
            printf("Opcion no valida. Ingrese nuevamente\n");
            break;
        }
    } while (dif != 0);
    setColor(15);   
}
