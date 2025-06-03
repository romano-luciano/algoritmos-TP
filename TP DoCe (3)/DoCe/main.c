#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Funciones.h"
#include "pilaDinamica.h"

void mainMenuBanner()
{
    system("cls || clear");
    setColor(14); // Amarillo
    printf("=====================================\n");
    printf("        BIENVENIDOS A DoCe        \n");
    printf("=====================================\n");
    setColor(15); // Blanco
    printf("Seleccione una opcion:\n\n");

    setColor(11); printf("[A]"); setColor(15); printf(" JUGAR\n");
    setColor(11); printf("[B]"); setColor(15); printf(" VER RANKING\n");
    setColor(11); printf("[C]"); setColor(15); printf(" SALIR\n");

    setColor(14);
    printf("\n=====================================\n");
    setColor(15);
    printf("Ingrese una opcion: ");
}

int main()
{
    char opc,nom[50],aux[MAX_LINES];
    char codigoGrupo[50];

    time_t tiempoAhora;   ///declaro la variable tiempo
    time(&tiempoAhora);  ///guardo el tiempo actual en la variable

    cargarCodigoGrupo(codigoGrupo, sizeof(codigoGrupo)); ///cargo el codigo del grupo en codigoGrupo

    struct tm*tiempo=localtime(&tiempoAhora);
    sprintf(aux,"informe-juego_%d-%02d-%02d-%02d-%02d.txt",tiempo->tm_year + 1900,tiempo->tm_mon + 1,tiempo->tm_mday,tiempo->tm_hour,tiempo->tm_min);
    FILE*informe;
    do{
        mainMenuBanner();
        fflush(stdin);
        scanf("%c",&opc);
        switch(opc){
            case 'A':
                informe = fopen(aux,"wt");
                if(!informe){
                printf("No se pudo abrir el archivo!");
                exit(ERR_ARCH);
                }
                system("cls || clear");
                printf("Ingrese nombre de jugador: ");
                fflush(stdin);
                gets(nom);
                system("cls");
                fprintf(informe,"Nombre de jugador: %s\n",nom);
                menuDif(informe, codigoGrupo, nom); //a la funcion menu se le pasa el nombre del archivo .txt
                fclose(informe);
                break;
            case 'B':
                system("cls");
                ranking(codigoGrupo);
                break;
            case 'C':
                printf("Saliendo...");
                break;
            default:
                system("cls");
                printf("Opcion no valida. Ingrese nuevamente\n");
                break;
        }
    }while(opc!='C');
}
