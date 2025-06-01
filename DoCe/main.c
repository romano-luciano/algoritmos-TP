#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Funciones.h"
#include "pilaDinamica.h"

int main()
{
    char opc,nom[50],aux[MAX_LINES];
    time_t tiempoAhora;   ///declaro la variable tiempo
    time(&tiempoAhora);  ///guardo el tiempo actual en la variable
    struct tm*tiempo=localtime(&tiempoAhora);
    sprintf(aux,"informe-juego_%d-%02d-%02d-%02d-%02d.txt",tiempo->tm_year + 1900,tiempo->tm_mon + 1,tiempo->tm_mday,tiempo->tm_hour,tiempo->tm_min);
    FILE*informe;
    do{
        printf("--------BIENVENIDOS A DoCe!!!--------\n");
        printf("[A]JUGAR\n[B]VER RANKING\n[C]SALIR\n[D]PRUEBA IA\nIngrese una opcion: \n");
        fflush(stdin);
        scanf("%c",&opc);
        switch(opc){
            case 'A':
                informe = fopen(aux,"wt");
                if(!informe){
                printf("No se pudo abrir el archivo!");
                exit(ERR_ARCH);
                }
                system("cls");
                printf("Ingrese nombre de jugador: ");
                fflush(stdin);
                gets(nom);
                system("cls");
                fprintf(informe,"Nombre de jugador: %s\n",nom);
                menuDif(informe);
                fclose(informe);
                break;
            case 'B':
                system("cls");
                ranking();
                break;
            case 'C':
                printf("Saliendo...");
                break;
            case 'D':
                pruebaIA();
                break;
            default:
                system("cls");
                printf("Opcion no valida. Ingrese nuevamente\n");
                break;
        }
    }while(opc!='C');
}
